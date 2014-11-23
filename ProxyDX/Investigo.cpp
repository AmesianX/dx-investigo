//Copyright (C) 2012 Ashley Davis
//
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
//documentation files (the "Software"), to deal in the Software without restriction, including without limitation 
//the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
//and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
//WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
//HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#include "Investigo.h"
#include "ProxyIDirect3DDevice9.h"
#include "ProxyIDirect3D9.h"
#include "VariablePage.h"
#include "PerformanceLog.h"
#include "jsonstream.h"
#include "ConfigFile.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <psapi.h>

using namespace boost::algorithm;
using namespace boost::filesystem3;
using std::map;
using std::string;

/*todo: screenshots.
const char* SCREENSHOT_OUTPUT_DIR = "investigo-data"; 
D3DXIMAGE_FILEFORMAT SCREENSHOT_FILE_FORMAT = D3DXIFF_JPG;
const char* SCREENSHOT_FILE_EXT = "jpg";
*/

//
// The default path to the real DirectX DLL.
//
const char* DEFAULT_DIRECTX_DLL_PATH = "c:\\Windows\\System32\\d3d9.dll";

//
// Enum used to reference memory usage variables.
//
const char* memoryVariableNames[MemVar_Max] =
{
    "PageFaultCount", 
    "PeakWorkingSetSize",
    "WorkingSetSize",
    "QuotaPeakPagedPoolUsage",
    "QuotaPagedPoolUsage",
    "QuotaPeakNonPagedPoolUsage", 
    "QuotaNonPagedPoolUsage", 
    "PagefileUsage",
    "PeakPagefileUsage", 
    "PrivateUsage",
};

//
// The singleton instance of Investigo.
//
InvestigoSingleton* InvestigoSingleton::instance = NULL;

//
// Get the singleton instance of Investigo.
//
InvestigoSingleton* InvestigoSingleton::Instance()
{
    assert(instance != NULL);

    return instance;
}

void InvestigoSingleton::Init()
{
    assert(instance == NULL);

    PerformanceLog::Init();
    VariableManager::Init();

    instance = new InvestigoSingleton();
}

void InvestigoSingleton::Deinit()
{
    assert(instance != NULL);

    VariableManager::Deinit();
    PerformanceLog::Deinit();

    delete instance;
    instance = NULL;
}

InvestigoSingleton::InvestigoSingleton() :
    dxDllPath(DEFAULT_DIRECTX_DLL_PATH),
    outputDirectory(".\\"),
	enableDrawCalls(true),
	frameNumber(1),
	frameStartTime(0),
	prevFrameFPS(0),
	prevFrameTime(0),
	hudInitialized(false),
    pSprite(NULL),
    pFont(NULL),
    pLargeFont(NULL),
    inspectorState(IS_Running),
    suspendLocation("n/a"),
    stepCount(1),
    drawCallNumber(0),
	device(NULL),
    firstFrameDone(false),
    performanceLoggingWasEnabledThisFrame(false),
    performanceLoggingWasEndedThisFrame(false),
    performanceLoggingStartFrame(0),
    performanceLoggingNumFrames(0),
    exitWhenPerformanceLoggingFinished(false)
{
    VariablePage* rootPage = VariableManager::Instance()->GetRootPage();
    VariablePage* overviewPage = rootPage->GetSubPage("Overview");

    VariableGroup* overviewGroup = VariableManager::Instance()->GetGroup("Overview");
    fpsVariable = overviewPage->GetVariable("FPS", Investigo::VariableType_Double, overviewGroup);
    frameTimeVariable = overviewPage->GetVariable("frameTime", Investigo::VariableType_Milliseconds, overviewGroup);

    VariablePage* memoryPage = rootPage->GetSubPage("Memory");
    VariableGroup* memoryGroup = VariableManager::Instance()->GetGroup("Memory");

    for (int i = 0; i < MemVar_Max; ++i)
    {
        memoryUsage[i] = memoryPage->GetVariable(memoryVariableNames[i], Investigo::VariableType_Memory, memoryGroup);
    }

    LoadConfig();
}

InvestigoSingleton::~InvestigoSingleton() 
{
}

//todo: move to utils.
BOOL DirectoryExists(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

//todo: move to utils.
BOOL FileExists(LPCTSTR szPath)
{
    DWORD dwAttrib = GetFileAttributes(szPath);

    return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
        !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}
//
// Load the configuration file.
//
void InvestigoSingleton::LoadConfig()
{
    ConfigFile config("Investigo.cfg");
    dxDllPath = config.GetValue("DirectXPath", dxDllPath);
    outputDirectory = config.GetValue("OutputDirectory", outputDirectory);

    performanceLoggingStartFrame = config.GetValue("PerformanceLoggingStartFrame", performanceLoggingStartFrame);
    performanceLoggingNumFrames = config.GetValue("PerformanceLoggingDuration", performanceLoggingNumFrames);
    exitWhenPerformanceLoggingFinished = config.GetValue("ExitAfterPerformanceLogging", exitWhenPerformanceLoggingFinished);

    int historyBufferSize = config.GetValue("HistoryBufferSize", VariableManager::Instance()->GetHistoryBufferSize());
    VariableManager::Instance()->SetHistoryBufferSize(historyBufferSize);

	if (!DirectoryExists(outputDirectory.c_str()))	
	{
		if (CreateDirectoryA(outputDirectory.c_str(), NULL))
		{
			AddClientMessage((boost::format("Created output directory: %s") % outputDirectory).str());
		}
		else
		{
			AddClientMessage((boost::format("Failed to create output directory: %s") % outputDirectory).str());
		}
	}
	else
	{
		AddClientMessage((boost::format("OutputDirectory: %s") % outputDirectory).str());
	}

    const path logFilePath = path(outputDirectory) / "Investigo.log";
    errorLog.open(logFilePath.string());
}

//
// Retrieve a variable from the page.
// Variable is created if it doesn't already exists.
//
Investigo::IVariable* InvestigoSingleton::GetVariable(const char* pageName, const char* variableName, Investigo::VariableType variableType)
{
    boost::unique_lock<boost::mutex> lock(VariableManager::Instance()->GetVariableMutex());

    VariablePage* appPage = VariableManager::Instance()->GetRootPage()->GetSubPage("Application");
    VariablePage* page = appPage->GetSubPage(pageName);
    return page->GetVariable(variableName, variableType, VariableManager::Instance()->GetGroup("Application"));
}

//
// Returns true if performance logging is currently enabled, or queued to start next frame.
//
bool InvestigoSingleton::IsPerformanceLoggingEnabled()
{
    return PerformanceLog::Instance()->IsEnabled() || performanceLoggingWasEnabledThisFrame;
}

//
// Start performance logging.
//
void InvestigoSingleton::StartPerformanceLogging()
{
    if (PerformanceLog::Instance()->IsEnabled())
    {
        // Performance logging is already active.        
        // Cancel any request to stop performance logging.
        performanceLoggingWasEndedThisFrame = false; 
    }
    else
    {
        // Performance logging not active.
        // Queue performance logging to start at end of frame.
        performanceLoggingWasEnabledThisFrame = true;
    }
}

//
// Stop performance logging.
//
void InvestigoSingleton::StopPerformanceLogging()
{
    if (PerformanceLog::Instance()->IsEnabled())
    {
        // Performance logging active.
        // Queue performance logging to end at end of current frame.
        performanceLoggingWasEndedThisFrame = true;
    }
    else
    {
        // Performance logging not active.
        // Ensure there is no request to start performance logging.
        performanceLoggingWasEnabledThisFrame = false;
    }
}

//
// Get the current frame number (starts at 1).
//
int InvestigoSingleton::GetCurrentFrameNumber() const
{
    return frameNumber;
}

//
// Start performance logging at the specified frame number.
// Has no effect if the specified frame has already passed.
//
void InvestigoSingleton::StartPerformanceLoggingAt(int frameNumber)
{
    performanceLoggingStartFrame = frameNumber;
}

//
// Stop performance logging after it has been going for X frames.
//
void InvestigoSingleton::StopPerformanceLoggingAfter(int numFrames)
{
    performanceLoggingNumFrames = numFrames;
}

//
// Causes the application to be forcefully exited when performance logging has finished.
//
void InvestigoSingleton::ExitWhenPerformanceLoggingFinished()
{
    exitWhenPerformanceLoggingFinished = true;
}

//
// Render the Investigo HUD that overlays the DirectX render window.
//
void InvestigoSingleton::RenderHUD(IDirect3DDevice9* device)
{
	if (!hudInitialized)
	{
		hudInitialized = true;

		D3DXCreateFont(device, 15, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pFont);
        D3DXCreateFont(device, 20, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pLargeFont);
		D3DXCreateSprite(device, &pSprite);
	}

	device->BeginScene();

	D3DRECT rec = {4,4,215,55};
	device->Clear(1, &rec, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255,255,255,255),0 ,0); //todo: make the rect cover the entire area.

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

    RECT rc;

    if (IsPerformanceLoggingEnabled())
    {
        RECT rc;
        SetRect(&rc, 10, 5, 0, 0);
        pFont->DrawTextA(pSprite, "Investigo - Logging", -1, &rc, DT_NOCLIP, D3DXCOLOR(0, 0, 0, 1));
    }
    else
    {
        SetRect(&rc, 10, 5, 0, 0);
        pFont->DrawTextA(pSprite, "Investigo", -1, &rc, DT_NOCLIP, D3DXCOLOR(0, 0, 0, 1));
    }

    char buf[1024];

    SetRect(&rc, 10, 23, 0, 0);
    sprintf(buf, "%3.2f", prevFrameFPS);
    pLargeFont->DrawTextA(pSprite, buf, -1, &rc, DT_NOCLIP, D3DXCOLOR(0, 0, 0, 1));

    SetRect(&rc, 100, 23, 0, 0);
    sprintf(buf, "%3.1f", prevFrameTime);
    pLargeFont->DrawTextA(pSprite, buf, -1, &rc, DT_NOCLIP, D3DXCOLOR(0, 0, 0, 1));

    SetRect(&rc, 170, 23, 0, 0);
    sprintf(buf, "%d", frameNumber);
    pLargeFont->DrawTextA(pSprite, buf, -1, &rc, DT_NOCLIP, D3DXCOLOR(0, 0, 0, 1));

    SetRect(&rc, 13, 38, 0, 0);
    pFont->DrawTextA(pSprite, "fps", -1, &rc, DT_NOCLIP, D3DXCOLOR(0, 0, 0, 1));

    SetRect(&rc, 103, 38, 0, 0);
    pFont->DrawTextA(pSprite, "time", -1, &rc, DT_NOCLIP, D3DXCOLOR(0, 0, 0, 1));

    SetRect(&rc, 173, 38, 0, 0);
    pFont->DrawTextA(pSprite, "frame", -1, &rc, DT_NOCLIP, D3DXCOLOR(0, 0, 0, 1));

	pSprite->End();

	device->EndScene();
}

//
// The D3D device notifies that a frame has ended.
//
void InvestigoSingleton::NotifyFrameEnd()
{
    UpdatePerFrameVariables();

    UpdatePerformanceLog();

    //
    // Reset for the next frame.
    //
	++frameNumber;
    drawCallNumber = 0;
}

//
// Update FPS and frame time.
//
void InvestigoSingleton::UpdatePerFrameVariables() 
{
    if (firstFrameDone)
    {
        //
        // Only do these computations after the second frame has finished.
        // We can't know when the first frame starts (there is no 'frame started' function in DX).
        // So we must wait until the end of the second frame before starting to compute these values.
        //

        const double frameEndTime = frameTimeElapsed.GetElapsedTime();
        const double frameTimeSeconds = frameEndTime - frameStartTime;
        const double frameTimeMS = frameTimeSeconds * 1000.0;
        const double fps = 1000.0 / frameTimeMS;

        fpsVariable->SetValue(fps);
        frameTimeVariable->SetValue(frameTimeMS);

        UpdateMemoryVariables();

        VariableManager::Instance()->NotifyFrameEnd(frameNumber);

        prevFrameFPS = fps;
        prevFrameTime = frameTimeMS;

        //
        // Reset frame start time for the next frame.
        //
        frameStartTime = frameEndTime;
    }
    else
    {
        firstFrameDone = true;
        frameTimeElapsed.Start();
        frameStartTime = 0.0;
    }
}

//
// Update the performance logging system.
//
void InvestigoSingleton::UpdatePerformanceLog() 
{
    if (PerformanceLog::Instance()->IsEnabled())
    {
        // Performance logging is currently enabled.

        if (performanceLoggingNumFrames > 0)
        {
            if (--performanceLoggingNumFrames == 0)
            {
                // When enabled, performance logging automatically ends after X frames have elapsed.
                performanceLoggingWasEndedThisFrame = true;
            }
        }

        if (performanceLoggingWasEndedThisFrame)
        {
            // Performance logging is due to end.

            performanceLoggingWasEndedThisFrame = false;
            PerformanceLog::Instance()->Stop();

            if (exitWhenPerformanceLoggingFinished)
            {
                // If enabled, abort the application once performance logging has completed.
                exit(1);
            }
        }
    }
    else if (performanceLoggingWasEnabledThisFrame || 
             frameNumber == performanceLoggingStartFrame-1)
    {
        // Performance logging has just started.
        performanceLoggingWasEnabledThisFrame = false;
        PerformanceLog::Instance()->Start();
    }
}

//
// Update memory usage variables.
//
void InvestigoSingleton::UpdateMemoryVariables() 
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(),  (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
    {
        memoryUsage[MemVar_PageFaultCount]->SetValue((int)pmc.PageFaultCount);
        memoryUsage[MemVar_PeakWorkingSetSize]->SetValue((int)pmc.PeakWorkingSetSize);
        memoryUsage[MemVar_WorkingSetSize]->SetValue((int)pmc.WorkingSetSize);
        memoryUsage[MemVar_QuotaPeakPagedPoolUsage]->SetValue((int)pmc.QuotaPeakPagedPoolUsage);
        memoryUsage[MemVar_QuotaPagedPoolUsage]->SetValue((int)pmc.QuotaPagedPoolUsage);
        memoryUsage[MemVar_QuotaPeakNonPagedPoolUsage]->SetValue((int)pmc.QuotaPeakNonPagedPoolUsage);
        memoryUsage[MemVar_QuotaNonPagedPoolUsage]->SetValue((int)pmc.QuotaNonPagedPoolUsage);
        memoryUsage[MemVar_PagefileUsage]->SetValue((int)pmc.PagefileUsage);
        memoryUsage[MemVar_PeakPagefileUsage]->SetValue((int)pmc.PeakPagefileUsage);
        memoryUsage[MemVar_PrivateUsage]->SetValue((int)pmc.PrivateUsage);
    }
}

//
// Format the current DirectX state as JSON.
//
std::string InvestigoSingleton::FormatDirectXStateAsJSON() const
{
	if (device == NULL)
	{
		return "";
	}

	jsonstream output;
	output	<< jsonstream::openObject 
			<< "render_state" << jsonstream::openArray;

	device->FormatStateAsJSON(output);

	output	<< jsonstream::closeArray
			<< jsonstream::closeObject;

	return output.str();
}

//
// Format the status of the inspector as JSON.
// 
std::string InvestigoSingleton::FormatInspectorStatusAsJSON() const
{
	jsonstream output;
	output	<< jsonstream::openObject
			<< "inspector_status";

	if (inspectorState == IS_Running)
	{
		output << "running";
	}
	else if (inspectorState == IS_Suspended)
	{
		output << "suspended";
	}
	else if (inspectorState == IS_SuspendRequested)
	{
		output << "suspend_requested";
	}
	else if (inspectorState == IS_ResumeRequested)
	{
		output << "resume_requested";
	}
	else if (inspectorState == IS_StepRequested)
	{
		output << "step_requested";
	}
	else if (inspectorState == IS_TriggerBreakpoint)
	{
		output << "trigger_breakpoint";
	}
	else
	{
		assert(false);
	}

	output	<< "suspend_location" << suspendLocation;

	if (inspectorState == IS_Suspended)
	{
		output	<< "draw_calls_last_frame" << device->GetDrawCallsLastFrame()
				<< "max_bound_texture_index" << device->GetMaxTextureIndexBound()
				<< "render_state" << jsonstream::openArray;

		device->FormatStateAsJSON(output);
			
		output << jsonstream::closeArray;
	}

	output << jsonstream::closeObject;

	return output.str();
}

//
// Request that the main thread be suspended at the next suspend point.
//
void InvestigoSingleton::RequestSuspend()
{
	if (inspectorState != IS_Suspended)
	{
		inspectorState = IS_SuspendRequested;
	}
}

//
// Suspend execution of the main thread until resumed or stepped by another thread.
//
bool InvestigoSingleton::Suspend(const std::string& _suspendLocation)
{
	assert(inspectorState != IS_Suspended);

	inspectorState = IS_Suspended;
	suspendLocation = _suspendLocation;

	if (inspectorState)

	while (inspectorState == IS_Suspended)
	{
		Sleep(100);
	}

	if (inspectorState == IS_TriggerBreakpoint)
	{
		inspectorState = IS_Running;
		return true;
	}

	if (inspectorState != IS_StepRequested)
	{
		inspectorState = IS_Running;
	}

	return false;
}

//
// Allow a suspended thread to be resumed.
//
void InvestigoSingleton::Resume()
{
	if (inspectorState == IS_Suspended)
	{
		inspectorState = IS_ResumeRequested;
		suspendLocation = "n/a";
	}
}

//
// Allow a suspended thread to resume until the next suspend point.
//
void InvestigoSingleton::Step(int count)
{
	if (inspectorState == IS_Suspended)
	{
		inspectorState = IS_StepRequested;
		suspendLocation = "n/a";
		stepCount = count;
	}
}

//
// Trigger a breakpoint now, only valid from suspension.
//
void InvestigoSingleton::TriggerBreakpoint()
{
	if (inspectorState == IS_Suspended)
	{
		inspectorState = IS_TriggerBreakpoint;
	}
}

//
// Returns true if one string contains another, case insensitive.
//
static bool StringContains(const char* s, const char* toMatch)
{
    const char* toMatchWorking = toMatch;
    while (*s && *toMatchWorking)
    {
        if (tolower(*s) == tolower(*toMatchWorking))
        {
            ++toMatchWorking; // Found a match, advance.
        }
        else
        {
            toMatchWorking = toMatch; // No match, reset.
        }

        ++s;
    }

    return !*toMatchWorking; // Reached the nul terminator, yes then there is a match.
}

//
// Potentially invoke a breakpoint.
// Return 'true' to notify that a break point should be triggered.
//
bool InvestigoSingleton::InvokeBreakpoint(const char* breakPoint)
{
    if (nextBreakPoint.size() == 0)
    {
        return false; // Don't trigger breakpoint.
    }

    if (StringContains(breakPoint, nextBreakPoint.c_str()))
    {
        ClearBreakPoint();
        return true; // Trigger breakpoint.
    } 

    return false; // Don't trigger breakpoint.
}

//
// Register a breakpoint, so that client has a list of known breakpoints.
//
void InvestigoSingleton::RegisterBreakpoint(const std::string& fullApiName)
{
    breakPoints.insert(fullApiName);
}

//
// Format breakpoints as JSON and return the string.
//
std::string InvestigoSingleton::FormatBreakPointsAsJSON() const
{    
    jsonstream output;
    output << jsonstream::openArray;

    

    for (std::set<std::string>::const_iterator it = breakPoints.begin(); it != breakPoints.end(); ++it)
    {
        output << jsonstream::openObject;
        output << "name" << *it;
        output << jsonstream::closeObject;
    }

    output << jsonstream::closeArray;

    return output.str();
}

//
// Mark a suspend point and potentially invoke appliation suspension.
// Return 'true' to notify that a break point should be triggered.
//
bool InvestigoSingleton::SuspendPoint(const char* location)
{
  if (inspectorState == IS_SuspendRequested || 
      inspectorState == IS_StepRequested) 
  { 
    stepCount = 1;
    if (Suspend(location))
    { 
      return true; // Trigger breakpoint.
    } 
  }

  return false; // Don't trigger breakpoint.
}

//
// Mark a suspend point and potentially invoke appliation suspension.
// Return 'true' to notify that a break point should be triggered.
//
bool InvestigoSingleton::DrawCallSuspendPoint(const char* location)
{
  ++drawCallNumber;

  if (inspectorState  == IS_StepRequested)
  {
    --stepCount;
    if (stepCount <= 0)
    {
      stepCount = 1;
      std::string suspendLocation = (boost::format("%s [%d]") % location % drawCallNumber).str(); 
      if (Suspend(suspendLocation)) 
      {
        return true; // Trigger breakpoint.
      }
    }
  }

  return false; // Don't trigger breakpoint.
}

//
// Get a screenshot of the current backbuffer.
//
void InvestigoSingleton::GetBackbufferScreenshot(std::vector<unsigned char>& data)
{
	if (device != NULL)
	{
		device->GetBackbufferScreenshot(data);
	}
}

//
// Get a screenshot of the render target.
//
void InvestigoSingleton::GetRenderTargetScreenshot(std::vector<unsigned char>& data)
{
	if (device != NULL)
	{
		device->GetRenderTargetScreenshot(data);
	}
}

//
// Retreive the data for a currently bound texture.
//
void InvestigoSingleton::GetBoundTexture(int index, std::vector<unsigned char>& data)
{
	if (device != NULL)
	{
		device->GetBoundTexture(index, data);
	}
}

/*todo: screenshots.
//
// Determine an appropriate filename for a screenshot.
//
bool InvestigoSingleton::DetermineScreenshotFileName(std::string& screenshotFilePath, std::string& screenshotFileName) const
{
	for (unsigned int screenshotIndex = 0; screenshotIndex < 5000; ++screenshotIndex)
	{
		screenshotFileName = (boost::format("Screenshot%d.%s") % screenshotIndex % SCREENSHOT_FILE_EXT).str();
		screenshotFilePath = (boost::format("%s\\%s") % SCREENSHOT_OUTPUT_DIR % screenshotFileName).str();
		if (!exists(screenshotFilePath))
		{
			// This is the one!
			return true;
		}
	}

	return false;
}

//
// Determine an appropriate filename, dump a screenshot, retreive the path to the screenshot.
//
bool InvestigoSingleton::DumpScreenshot(std::string& filePath, std::string& fileName)
{
	create_directory(SCREENSHOT_OUTPUT_DIR);

	//
	// Determine a filename.
	//
	string screenshotFileName;
	string screenshotFilePath;
	if (!DetermineScreenshotFileName(screenshotFilePath, screenshotFileName))
	{
		return false;
	}

	if (TakeScreenshot(screenshotFilePath, SCREENSHOT_FILE_FORMAT))
	{
		filePath = (boost::format("%s\\%s") % current_path().string() % screenshotFilePath).str();
		fileName = screenshotFileName;
		return true;
	}

	return false;	
}

//
// Dump a screenshot to the specified file.
//
bool InvestigoSingleton::TakeScreenshot(const std::string& filePath, D3DXIMAGE_FILEFORMAT fileFormat)
{
	if (device != NULL)
	{
		return device->TakeScreenshot(filePath, fileFormat);
	}

	return false;
}
*/

//
// Format device configuration as JSON.
//
std::string InvestigoSingleton::FormatConfigAsJSON() const
{
	jsonstream output;
	output  << jsonstream::openArray
			<< jsonstream::openObject
			<< "name" << "device"
			<< "value" << jsonstream::openArray;

	if (device != NULL)
	{
		device->FormatConfigAsJSON(output);

	}

	output	<< jsonstream::closeArray
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "d3d"
			<< "value" << jsonstream::openArray;

	if (d3d != NULL)
	{
		d3d->FormatConfigAsJSON(output);
	}

	output  << jsonstream::closeArray
			<< jsonstream::closeObject
			<< jsonstream::closeArray;

	return output.str();
}

//
// Pull queued client messages as JSON.
//
std::string InvestigoSingleton::PullClientMessagesAsJSON()
{
	jsonstream output;
	output << jsonstream::openArray;

	string msg;
	bool firstOne = true;
	while (clientMessageQueue.try_pop(msg))
	{
		if (firstOne)
		{
			firstOne = false;
		}

		output << msg;
	}

	output << jsonstream::closeArray;

	return output.str();
}

//
// Format the current resource stack as a name.
// The name is cached until the resource stack changes.
//
std::string InvestigoSingleton::FormatCurrentResourceName(const char* defaultName)
{
    if (formattedResourceName.size() == 0)
    {
        if (resourceStack.size() > 0)
        {
            std::stringstream working;

            for (unsigned int i = 0; i < resourceStack.size(); ++i)
            {
                if (i > 0)
                {
                    working << "/";
                }

                working << resourceStack[i];
            }

            formattedResourceName = working.str();
        }
        else
        {
            return defaultName;
        }
    }

    return formattedResourceName;
}

//
// Log an info message.
//
void InvestigoSingleton::InfoMessage(const std::string& msg)
{
    AddClientMessage("Info: " + msg);
}

//
// Log an error message.
//
void InvestigoSingleton::ErrorMessage(const std::string& msg)
{
    AddClientMessage("Error: " + msg);
}

