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
#include "DXHttpServer.h"
#include "VariablePage.h"
#include "Investigo.h"
#include "jsonstream.h"

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>

using std::string;
using std::vector;
using std::stringstream;

//
// Convert a string to data that can be returned by the HTTP server.
//
static vector<unsigned char> StringToData(const string& str) //todo: can't i just cast it instead of copying?
{
    vector<unsigned char> data;
    data.resize(str.size());

    memcpy(&data[0], &str[0], str.size());

    return data;
}

DXHttpServer::DXHttpServer()
{
    httpServer.AddUrlCallback("/set_breakpoint", boost::bind(&DXHttpServer::SetBreakpointUrlCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_breakpoints", boost::bind(&DXHttpServer::GetBreakpointsCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_pages", boost::bind(&DXHttpServer::GetPagesCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_variable_history", boost::bind(&DXHttpServer::GetVariableHistoryCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_state", boost::bind(&DXHttpServer::GetStateCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_inspector_status", boost::bind(&DXHttpServer::GetInspectorStatusCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/suspend", boost::bind(&DXHttpServer::SuspendCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/resume", boost::bind(&DXHttpServer::ResumeCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/step", boost::bind(&DXHttpServer::StepCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_backbuffer", boost::bind(&DXHttpServer::GetBackBufferScreenshotCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_rendertarget", boost::bind(&DXHttpServer::GetRenderTargetScreenshotCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/trigger_breakpoint_now", boost::bind(&DXHttpServer::GetTriggerBreakpointCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_config", boost::bind(&DXHttpServer::GetConfigCallback, this, _1, _2, _3, _4));
    //todo: screenshots: httpServer.AddUrlCallback("/take_screenshot", boost::bind(&DXHttpServer::TakeScreenshotCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_messages", boost::bind(&DXHttpServer::GetMessagesCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_bound_texture", boost::bind(&DXHttpServer::GetBoundTextureCallback, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/toggle_performance_logging", boost::bind(&DXHttpServer::TogglePerformanceLogging, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/toggle_draw_calls", boost::bind(&DXHttpServer::ToggleDrawCalls, this, _1, _2, _3, _4));
    httpServer.AddUrlCallback("/get_status", boost::bind(&DXHttpServer::GetStatus, this, _1, _2, _3, _4));
}

DXHttpServer::~DXHttpServer()
{
}

//
// Callback from the generic HTTP server when '/set_breakpoint' is hit.
//
void DXHttpServer::SetBreakpointUrlCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	mimeType = "application/text";

	HttpServer::StringMap::const_iterator found = queryString.find("break_point_location");
	if (found == queryString.end())
	{
		return;
	}

    const char* breakPointLocation = found->second.c_str();
    InvestigoSingleton::Instance()->SetNextBreakPoint(breakPointLocation);
}

//
// Callback from the generic HTTP server when '/get_breakpoints' is hit.
//
void DXHttpServer::GetBreakpointsCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
    mimeType = "application/json";
    data = StringToData(InvestigoSingleton::Instance()->FormatBreakPointsAsJSON());
}

//
// Callback when /get_pages is hit.
//
void DXHttpServer::GetPagesCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	OutputDebugStringA("DXHttpServer::GetPagesCallback: Acquiring lock...\n");

	boost::unique_lock<boost::mutex> lock(VariableManager::Instance()->GetVariableMutex());

	OutputDebugStringA("DXHttpServer::GetPagesCallback: Got lock...\n");

	mimeType = "application/json";
	data = StringToData(VariableManager::Instance()->FormatPagesAsJSON());

	OutputDebugStringA("DXHttpServer::GetPagesCallback: releasing lock\n");
}

//
// Callback to get history of a particular variable.
//
void DXHttpServer::GetVariableHistoryCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	OutputDebugStringA("DXHttpServer::GetVariableHistoryCallback: Acquiring lock...\n");

	boost::unique_lock<boost::mutex> lock(VariableManager::Instance()->GetVariableMutex());

	OutputDebugStringA("DXHttpServer::GetVariableHistoryCallback: Got lock...\n");

	mimeType = "application/json";

    HttpServer::StringMap::const_iterator found = queryString.find("variable_id");
    if (found == queryString.end())
    {
        OutputDebugStringA("DXHttpServer::GetVariableHistoryCallback: releasing lock\n");
        return;
    }

    boost::char_separator<char> sep(", ");
    boost::tokenizer<boost::char_separator<char>> tokens(found->second, sep);

    jsonstream output;
    output << jsonstream::openArray;
    
    BOOST_FOREACH (const string& token, tokens) 
    {
	    int variableID = atoi(token.c_str());
	    if (variableID < 1)
	    {
		    continue;
	    }

	    Variable* variable = VariableManager::Instance()->GetVariable(variableID);
	    if (variable != NULL)
	    {
            output << jsonstream::openObject;
            output << "id" << variableID;
            output << "data";

            variable->FormatHistoryAsJSON(output);

            output << jsonstream::closeObject;

            //
            // Clear history.
            //
            variable->ClearHistory();
	    }
    }

    output << jsonstream::closeArray;

    data = StringToData(output.str());

	OutputDebugStringA("DXHttpServer::GetVariableHistoryCallback: releasing lock\n");
}

//
// Callback to get the state of DirectX.
//
void DXHttpServer::GetStateCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	mimeType = "application/json";
	data = StringToData(InvestigoSingleton::Instance()->FormatDirectXStateAsJSON());
}

//
// Callback to get the status of the inspector system.
//
void DXHttpServer::GetInspectorStatusCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	mimeType = "application/json";
	data = StringToData(InvestigoSingleton::Instance()->FormatInspectorStatusAsJSON());
}

void DXHttpServer::SuspendCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	InvestigoSingleton::Instance()->RequestSuspend();
}

void DXHttpServer::ResumeCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	InvestigoSingleton::Instance()->Resume();
}

void DXHttpServer::StepCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	int count = 1;
	HttpServer::StringMap::const_iterator found = queryString.find("count");
	if (found != queryString.end())
	{
		count = boost::lexical_cast<int>(found->second);
	}
	InvestigoSingleton::Instance()->Step(count);
}

//
// Trigger a breakpoint now, only valid from suspension.
//
void DXHttpServer::GetTriggerBreakpointCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	InvestigoSingleton::Instance()->TriggerBreakpoint();
}

//
// Callbacks to retrieve a screenie of the backbuffer.
//
void DXHttpServer::GetBackBufferScreenshotCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	boost::unique_lock<boost::mutex> lock(directXMutex); // Lock so that only 1 HTTP server thread can access the DX interfaces at a time.

	mimeType = "image/jpeg";
	InvestigoSingleton::Instance()->GetBackbufferScreenshot(data);
}

//
// Callbacks to retrieve a screenie of the render target.
//
void DXHttpServer::GetRenderTargetScreenshotCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	boost::unique_lock<boost::mutex> lock(directXMutex); // Lock so that only 1 HTTP server thread can access the DX interfaces at a time.

	mimeType = "image/jpeg";
	InvestigoSingleton::Instance()->GetRenderTargetScreenshot(data);
}

//
// Callbacks to retrieve a bound texture.
//
void DXHttpServer::GetBoundTextureCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	boost::unique_lock<boost::mutex> lock(directXMutex); // Lock so that only 1 HTTP server thread can access the DX interfaces at a time.

	mimeType = "image/jpeg";

	int index = 0;
	HttpServer::StringMap::const_iterator found = queryString.find("index");
	if (found != queryString.end())
	{
		index = boost::lexical_cast<int>(found->second);
	}

	InvestigoSingleton::Instance()->GetBoundTexture(index, data);
}

//
// Retreive device configuration.
//
void DXHttpServer::GetConfigCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	mimeType = "application/json";

	// No need to lock on a mutex here at the moment, no data is retreived from the DX interfaces, all data is retreived from cached information.
	data = StringToData(InvestigoSingleton::Instance()->FormatConfigAsJSON());
}

/*todo: screenshots
//
// Take a screenshot.
//
void DXHttpServer::TakeScreenshotCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	boost::unique_lock<boost::mutex> lock(directXMutex); // Lock so that only 1 HTTP server thraed can access the DX interfaces at a time.

	mimeType = "application/json";

	string filePath;
	string fileName;
	if (!InvestigoSingleton::Instance()->DumpScreenshot(filePath, fileName))
	{
		data = StringToData("{ \"error\": \"Failed to take screenshot.\" }"); //todo: want a better way of passing up errors.
	}
	else
	{
		boost::replace_all(filePath, "\\", "\\\\");
		data = StringToData((boost::format("{ \"screenshot_filename\": \"/%s\", \"screenshot_filepath\": \"%s\" }") % fileName % filePath).str());
	}	
}
*/

//
// Retrieve queued messages as JSON.
//
void DXHttpServer::GetMessagesCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
	mimeType = "application/json";

	//
	// Don't need to lock on a mutex here, pulling data from a lock-free queue.
	//
	data = StringToData(InvestigoSingleton::Instance()->PullClientMessagesAsJSON());
}

//
// Toggle the state of performance logging between enabled and disabled.
//
void DXHttpServer::TogglePerformanceLogging(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
    mimeType = "application/json";

    if (InvestigoSingleton::Instance()->IsPerformanceLoggingEnabled())
    {
        InvestigoSingleton::Instance()->StopPerformanceLogging();
    }
    else
    {
        InvestigoSingleton::Instance()->StartPerformanceLogging();
    }
}

//
// Toggle draw calls on and off.
//
void DXHttpServer::ToggleDrawCalls(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
    mimeType = "application/json";

    if (InvestigoSingleton::Instance()->DrawCallsEnabled())
    {
        InvestigoSingleton::Instance()->EnableDrawCalls(false);
    }
    else
    {
        InvestigoSingleton::Instance()->EnableDrawCalls(true);
    }
}

//
// Get the current state of performance logging.
//
void DXHttpServer::GetStatus(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data)
{
    mimeType = "application/json";

    jsonstream output;
    output	<< jsonstream::openObject
            << "perf_logging_enabled" << InvestigoSingleton::Instance()->IsPerformanceLoggingEnabled()
            << "draw_calls_enabled" << InvestigoSingleton::Instance()->DrawCallsEnabled()
            << jsonstream::closeObject;

    data = StringToData(output.str());
}



