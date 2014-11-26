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
#pragma once

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <boost/thread.hpp>
#include <boost/format.hpp>
#include <concurrent_queue.h>

#include "InvestigoApplicationInterface.h"
#include "DXHttpServer.h"
#include "VariableManager.h"
#include "VariablePage.h"
#include "Variable.h"
#include "Timer.h"

class Variable;
class ProxyIDirect3DDevice9;
class ProxyIDirect3D9;

//
// Specifies the state of the inspector system.
//
enum InspectorState
{
  IS_Running,
  IS_SuspendRequested,
  IS_Suspended,
  IS_ResumeRequested,
  IS_StepRequested,
  IS_TriggerBreakpoint
};

//
// Enum used to reference memory usage variables.
//
enum MemoryVariable
{
    MemVar_PageFaultCount, 
    MemVar_PeakWorkingSetSize,
    MemVar_WorkingSetSize, 
    MemVar_QuotaPeakPagedPoolUsage,
    MemVar_QuotaPagedPoolUsage, 
    MemVar_QuotaPeakNonPagedPoolUsage, 
    MemVar_QuotaNonPagedPoolUsage, 
    MemVar_PagefileUsage,
    MemVar_PeakPagefileUsage, 
    MemVar_PrivateUsage,
    MemVar_Max,
};

//
// Singleton for Investigo.
// Implements the Investigo application interface.
// Initialized when the DLL is loaded, deinitalized when the DLL is unloaded.
//
class InvestigoSingleton : public Investigo::Interface
{
public:

    //
    // Get the singleton instance of Investigo.
    //
	static InvestigoSingleton* Instance();

	static std::ostream& Log() { return Instance()->GetLog(); }

    //
    // Init Investigo.
    //
	static void Init();

    // 
    // Deinit Investigo.
    //
	static void Deinit();

    //
    // Get the path of the real DirectX DLL.
    //
    const std::string& GetDirectXDllPath() const { return dxDllPath; }   

    //
    // Get the current frame number, starting at 1.
    //
    virtual int GetFrameNumber() const { return frameNumber; }

    //
    // Get current time in seconds as measured by investigo.
    //
    virtual double GetTime() const { return frameTimeElapsed.GetElapsedTime(); }

	//
	// Set the directory that Investigo outputs log files to.
	// This must be set before performance logging is started.
	//
	virtual void SetOutputDirectory(const char* outputDirectory)
	{
		this->outputDirectory = outputDirectory;
	}

    //
    // Get the output directory for log files.
    //
    const std::string& GetOutputDirectory() const { return outputDirectory; }

    //
    // Enable / disable draw calls.
    //
	virtual void EnableDrawCalls(bool enable) { enableDrawCalls = enable; }

    //
    // Returns true if draw calls are enabled.
    //
    bool DrawCallsEnabled() const { return enableDrawCalls; }

    virtual void BeginResource(const char* name)
	{
        resourceStack.push_back(name);
        formattedResourceName.clear();
	}

	virtual void EndResource()
	{
        assert(resourceStack.size() > 0);

        if (resourceStack.size() > 0)
        {
            resourceStack.pop_back();
            formattedResourceName.clear();
        }
	}

	virtual void BeginTechnique(const char* name)
	{
		techniqueStack.push_back(name);
	}

	virtual void EndTechnique()
	{
        assert(techniqueStack.size() > 0);

        if (techniqueStack.size() > 0)
        {
		    techniqueStack.pop_back();
        }
	}

    //
    // Retrieve an variable from a page.
    // Variable is created if it doesn't already exists.
    //
    virtual Investigo::IVariable* GetVariable(const char* pageName, const char* variableName, Investigo::VariableType variableType);

    //
    // Returns true if performance logging is currently enabled, or queued to start next frame.
    //
    virtual bool IsPerformanceLoggingEnabled();

    //
    // Start performance logging.
    //
    virtual void StartPerformanceLogging();

    //
    // Stop performance logging.
    //
    virtual void StopPerformanceLogging();

    //
    // Get the current frame number (starts at 1).
    //
    virtual int GetCurrentFrameNumber() const;

    //
    // Start performance logging at the specified frame number.
    // Has no effect if the specified frame has already passed.
    //
    virtual void StartPerformanceLoggingAt(int frameNumber);

    //
    // Stop performance logging after it has been going for X frames.
    //
    virtual void StopPerformanceLoggingAfter(int numFrames);

    //
    // Causes the application to be forcefully exited when performance logging has finished.
    //
    virtual void ExitWhenPerformanceLoggingFinished();

    //
    // Render the Investigo HUD that overlays the DirectX render window.
    //
	void RenderHUD(IDirect3DDevice9* device);

	void ResetHUD();

    //
    // The D3D device notifies that a frame has ended.
    //
	void NotifyFrameEnd();

    //
    // Set the D3D and device ptrs.
    //
	void SetD3D(ProxyIDirect3D9* _d3d) { d3d = _d3d; }
	void SetDevice(ProxyIDirect3DDevice9* _device) { device = _device; }

	//
	// Format the current DirectX state as JSON.
	//
	std::string FormatDirectXStateAsJSON() const;

	//
	// Format the status of the inspector as JSON.
	//
	std::string FormatInspectorStatusAsJSON() const;

	//
	// Request that the main thread be suspended at the next suspend point.
	//
	void RequestSuspend();

	//
	// Suspend execution of the main thread until resumed or stepped by another thread.
	//
	bool Suspend(const std::string& _suspendLocation);

	//
	// Allow a suspended thread to be resumed.
	//
	void Resume();

	//
	// Allow a suspended thread to resume until the next suspend point.
	//
	void Step(int count);

	//
	// Trigger a breakpoint now, only valid from suspension.
	//
	void TriggerBreakpoint();

    //
    // Potentially invoke a breakpoint.
    // Return 'true' to notify that a break point should be triggered.
    //
    bool InvokeBreakpoint(const char* breakPoint);

    //
    // Retrieve details for the next break point.
    //
    const char* GetNextBreakPoint() const { return nextBreakPoint.c_str(); }

    //
    // Clear the breakpoint.
    //
    void ClearBreakPoint() { nextBreakPoint.clear(); }

    //
    // Set the next breakpoint.
    //
    void SetNextBreakPoint(const char* _nextBreakPoint) { nextBreakPoint = _nextBreakPoint; }

    //
    // Register a breakpoint, so that client has a list of known breakpoints.
    //
    void RegisterBreakpoint(const std::string& fullApiName);

    //
    // Format breakpoints as JSON and return the string.
    //
    std::string FormatBreakPointsAsJSON() const;

    //
    // Mark a suspend point and potentially invoke appliation suspension.
    // Return 'true' to notify that a break point should be triggered.
    //
    bool SuspendPoint(const char* location);

    //
    // Mark a suspend point and potentially invoke appliation suspension.
    // Return 'true' to notify that a break point should be triggered.
    //
    bool DrawCallSuspendPoint(const char* location);

	//
	// Get a screenshot of the current backbuffer.
	//
	void GetBackbufferScreenshot(std::vector<unsigned char>& data);

	//
	// Get a screenshot of the render target.
	//
	void GetRenderTargetScreenshot(std::vector<unsigned char>& data);

	//
	// Retreive the data for a currently bound texture.
	//
	void GetBoundTexture(int index, std::vector<unsigned char>& data);

    /*todo: screenshots
	//
	// Determine an appropriate filename, dump a screenshot, retreive the path to the screenshot.
	//
	bool DumpScreenshot(std::string& filePath, std::string& fileName);

	//
	// Dump a screenshot to the specified file.
	//
	bool TakeScreenshot(const std::string& filePath, D3DXIMAGE_FILEFORMAT fileFormat);
    */

	//
	// Format device configuration as JSON.
	//
	std::string FormatConfigAsJSON() const;

	//
	// Pull queued client messages as JSON.
	//
	std::string PullClientMessagesAsJSON();

    //
    // Log an info message.
    //
    void InfoMessage(const std::string& msg);

    //
    // Log an error message.
    //
    void ErrorMessage(const std::string& msg);

    //
    // Add a message to be sent to the client.
    //
    void AddClientMessage(const std::string& msg) { clientMessageQueue.push(msg); }

    //
    // Format the current resource stack as a name.
    // The name is cached until the resource stack changes.
    //
    std::string FormatCurrentResourceName(const char* defaultName = "");

    //
    // Retreive the error log for writing output.
    //
	std::ostream& ErrorLog() { return errorLog; }

	//
	// Retreive the error log for writing output.
	//
	std::ostream& GetLog() { return logStream; }

private:

    //
    // Private constructor/destructor.
    // Only a singleton instance is allowed.
    //
    InvestigoSingleton();
    ~InvestigoSingleton();

    //
    // The singleton instance of Investigo.
    //
    static InvestigoSingleton* instance;

	//
	// Load the configuration file.
	//
	void LoadConfig();

    /*todo: screenshots
    //
    // Determine an appropriate filename for a screenshot.
    //
    bool DetermineScreenshotFileName(std::string& screenshotFilePath, std::string& screenshotFileName) const; //todo: needed?
    */

    //
    // Update FPS and frame time.
    //
    void UpdatePerFrameVariables();

    //
    // Update the performance logging system.
    //
    void UpdatePerformanceLog();

    //
    // Update memory usage variables.
    //
    void UpdateMemoryVariables();

    //
    // DirectX device that is currently loaded.
    //
    ProxyIDirect3D9* d3d;
    ProxyIDirect3DDevice9* device;

    //
    // The path of the real DirectX DLL.
    //
    std::string dxDllPath;

    //
    // The output directory for log files.
    //
    std::string outputDirectory;

    //
    // Set to 'true' when draw calls are enabled, which is the default.
    //
    bool enableDrawCalls;
    
    //
    // Stack of resource names.
    //
	std::vector<std::string> resourceStack;

    //
    // Caches the current resource stack.
    // Invalidated whenever the resource stack changes.
    //
    std::string formattedResourceName;

    //
    // Stack of technique names.
    //
	std::vector<std::string> techniqueStack;

    //
    // Set to 'true' to mark when the first frame is done.
    // We can't know when the first frame starts, we can only know
    // when it ends.  So this is set to 'true' when that happens.
    //
    bool firstFrameDone;

    //
    // Set to true when performance logging is due to be started in the current frame.
    //
    bool performanceLoggingWasEnabledThisFrame;

    //
    // Set to true when performance logging is due to be ended in the current frame.
    //
    bool performanceLoggingWasEndedThisFrame;

    //
    // When greater than 0 this specifies the frame where performance logging should start.
    //
    int performanceLoggingStartFrame;

    //
    // When greater than 0 this specifies the number of frames that performance logging should run for.
    //
    int performanceLoggingNumFrames;

    //
    // Set to true to abort/exit the app when performance logging has finished.
    //
    bool exitWhenPerformanceLoggingFinished;

    //
    // Serves Investigo's HTTP webUI.
    //
	DXHttpServer dxHttpServer;

	//
	// The current frame number.
	//
	int frameNumber; 

	//
	// Records how much time has elapsed.
	//
	Timer frameTimeElapsed; 

	//
	// Time that the previous frame started.
	//
	double frameStartTime; 

	//
	// Frame rate and time stored from the previous frame.
	//
	double prevFrameFPS;
	double prevFrameTime;

	//
	// Variables used to record fps and frame time.
	//
	Variable* fpsVariable;
	Variable* frameTimeVariable;

    //
    // Variables used to record memory usage.
    //
    Variable* memoryUsage[MemVar_Max];

    //
    // Set to 'true' when the HUD has been initialized.
    //
	IDirect3DDevice9* hudDeviceInitialized;

    //
    // Resources for HUD rendering.
    //
	ID3DXSprite* pSprite;
	ID3DXFont* pFont;
    ID3DXFont* pLargeFont;

	//
	// Queued messages to be delivered to client.
	//
	Concurrency::concurrent_queue<std::string> clientMessageQueue;

    //
    // Defines where the next break point will occur.
    //
    std::string nextBreakPoint;

    //
    // A collection of all breakpoints, so they can be set to the client
    // and displayed to the user.
    //
    std::set<std::string> breakPoints;

    //
    // The current state of the inspector system.
    //
    InspectorState inspectorState;

    //
    // The location where the application is suspended.
    //
    std::string suspendLocation;

    //
    // The number of draw calls to step before the next suspend point.
    //
    int stepCount;

    //
    // Used to number draw calls.
    //
    int drawCallNumber;

    //
    // Log file for error messages.
    //
    std::ofstream errorLog;

	std::ofstream logStream;
};

class __TimingID
{
public:

	__TimingID(const char* className, const char* apiName)
	{
		boost::unique_lock<boost::mutex> lock(VariableManager::Instance()->GetVariableMutex());

		char pageName[1024];
		sprintf(pageName, "%s::%s", className, apiName);
		VariablePage* dxPage = VariableManager::Instance()->GetRootPage()->GetSubPage("DirectX");
        VariablePage* subPage = dxPage->GetSubPage(pageName);

        char variableName[1024];
        sprintf(variableName, "%s-Time", pageName);
        variable = subPage->GetVariable(variableName, Investigo::VariableType_Milliseconds, VariableManager::Instance()->GetGroup("DirectX-Timing"));
	}

	Variable* variable;
};

class __TimingBlock
{
public:

	__TimingBlock(Variable* _variable) :
	  variable(_variable)
	{
		startTime = InvestigoSingleton::Instance()->GetTime();
	}

	~__TimingBlock()
	{
		double endTime = InvestigoSingleton::Instance()->GetTime();
		double elapsedTime = endTime - startTime;
		variable->SetValue(elapsedTime);
	}

	double startTime;
	Variable* variable;
};

#define DX_API_TIMING(className, apiName) \
	static __TimingID __timingID##className##apiName(#className, #apiName); \
	__TimingBlock __timing##className##apiName(__timingID##className##apiName.variable); 

struct APICallEventRecorder
{
	APICallEventRecorder(const char* className, const char* apiName)
	{
		boost::unique_lock<boost::mutex> lock(VariableManager::Instance()->GetVariableMutex());

		sprintf(fullApiName, "%s::%s", className, apiName);
		VariablePage* dxPage = VariableManager::Instance()->GetRootPage()->GetSubPage("DirectX");
        VariablePage* subPage = dxPage->GetSubPage(fullApiName);

        char variableName[1024];
        sprintf(variableName, "%s-Count", fullApiName);
        variable = subPage->GetVariable(variableName, Investigo::VariableType_Int, VariableManager::Instance()->GetGroup("DirectX-Counts"));

        InvestigoSingleton::Instance()->RegisterBreakpoint(fullApiName);
	}

	void log() {

		//FILE * pFile = NULL;
		//fopen_s(&pFile, "d3dapi.log", "a");
		//if (pFile != NULL) {
		//	fputs(fullApiName, pFile);
		//	fputs("\n", pFile);
		//	fclose(pFile);
		//}
	}

	char fullApiName[1024];
	Variable* variable;
};

#define DX_RECORD_API_CALL(className, apiName) \
	{ \
		static APICallEventRecorder eventRecorder(#className, #apiName); \
		eventRecorder.log(); \
		eventRecorder.variable->Increment(); \
        if (InvestigoSingleton::Instance()->InvokeBreakpoint(#className "::" #apiName)) \
        { \
            DebugBreak(); \
        } \
	} \
	DX_API_TIMING(className, apiName)

struct DrawCallEventRecorder
{
	DrawCallEventRecorder(const char* className, const char* apiName)
	{
		boost::unique_lock<boost::mutex> lock(VariableManager::Instance()->GetVariableMutex());

		char fullApiName[1024];
		sprintf(fullApiName, "%s::%s", className, apiName);
        VariablePage* rootPage = VariableManager::Instance()->GetRootPage();
		VariablePage* dxPage = rootPage->GetSubPage("DirectX");
        VariablePage* subPage = dxPage->GetSubPage(fullApiName);

        char variableName[1024];
        sprintf(variableName, "%s-Count", fullApiName);
        variable = subPage->GetVariable(variableName, Investigo::VariableType_Int, VariableManager::Instance()->GetGroup("DirectX-Counts"));

        VariablePage* overviewPage = rootPage->GetSubPage("Overview");
        allDrawCalls = overviewPage->GetVariable("Draw Calls", Investigo::VariableType_Int, VariableManager::Instance()->GetGroup("Overview")); //todo: factor out these magnums.

        InvestigoSingleton::Instance()->RegisterBreakpoint(fullApiName);
	}

	Variable* variable;
	Variable* allDrawCalls;
};

#define DX_RECORD_DRAW_CALL(className, apiName) \
	{ \
		static DrawCallEventRecorder eventRecorder(#className, #apiName); \
		eventRecorder.variable->Increment(); \
		eventRecorder.allDrawCalls->Increment(); \
        if (InvestigoSingleton::Instance()->InvokeBreakpoint(#className "::" #apiName)) \
        { \
            DebugBreak(); \
        } \
	} \
	DX_API_TIMING(className, apiName)

#define DX_INSPECTOR_SUSPEND_POINT(className, apiName) \
    if (InvestigoSingleton::Instance()->SuspendPoint(#className "::" #apiName)) \
    { \
        DebugBreak(); \
    }

#define DX_DRAW_CALL_SUSPEND_POINT(className, apiName) \
    if (InvestigoSingleton::Instance()->DrawCallSuspendPoint(#className "::" #apiName)) \
    { \
        DebugBreak(); \
    }
