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

#include <boost/thread.hpp>

#include "HttpServer.h"

class InvestigoSingleton;

//
// A higher level class that manages the HTTP server on behalf of the Proxy DX DLL.
//
class DXHttpServer
{
public:

	DXHttpServer();
	~DXHttpServer();

private:

	//
	// Callback from the generic HTTP server when '/set_breakpoint' is hit.
	//
	void SetBreakpointUrlCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

    //
    // Callback from the generic HTTP server when '/get_breakpoints' is hit.
    //
    void GetBreakpointsCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// Callback when /get_pages is hit.
	//
	void GetPagesCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// Callback to get history of a particular variable.
	//
	void GetVariableHistoryCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// Callback to get the state of DirectX.
	//
	void GetStateCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// Callback to get the status of the inspector system.
	//
	void GetInspectorStatusCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// Callbacks to suspend, step and resume.
	//
	void SuspendCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);
	void ResumeCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);
	void StepCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// Trigger a breakpoint now, only valid from suspension.
	//
	void GetTriggerBreakpointCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// Callbacks to retrieve a screenie of the backbuffer.
	//
	void GetBackBufferScreenshotCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// Callbacks to retrieve a screenie of the render target.
	//
	void GetRenderTargetScreenshotCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// Callbacks to retrieve a bound texture.
	//
	void GetBoundTextureCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// Retreive device configuration.
	//
	void GetConfigCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

    /*todo: screenshots.
	//
	// Take a screenshot.
	//
	void TakeScreenshotCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);;
    */

	//
	// Retrieve queued messages as JSON.
	//
	void GetMessagesCallback(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

    //
    // Toggle the state of performance logging between enabled and disabled.
    //
    void TogglePerformanceLogging(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

    //
    // Toggle draw calls on and off.
    //
    void ToggleDrawCalls(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

    //
    // Get the current state of Investigo.
    //
    void GetStatus(const char* url, const HttpServer::StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& data);

	//
	// The generic HTTP server.
	//
	HttpServer httpServer;

	//
	// Mutex used to lock access to the DX interfaces.
	//
	boost::mutex directXMutex;
};

