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

#include "DllResourceManager.h"

#include <boost/function.hpp>
#include <map>
#include <string>
#include <vector>

//
// This class manages a HTTP server that can serve up an applications embedded resources as web-pages.
//
class HttpServer
{
public:

	HttpServer();
	~HttpServer();

	typedef std::map<std::string, std::string> StringMap;
	typedef boost::function<void (const char* url, const StringMap& queryString, std::string& mimeType, std::vector<unsigned char>& output)> UrlCallback;

	//
	// Add a callback for an URL.  The callback generates the data returned by the HTTP server.
	//
	void AddUrlCallback(const char* url,  UrlCallback callback);

	//
	// Instance callback from the HTTP server to serve pages and data.
	//
	void* HttpServerCallback(enum mg_event event, struct mg_connection* conn, const struct mg_request_info* request_info);

private:

	// 
	// Used to retrieve embedded resources by name.
	//
	DLLResourceManager resourceManager;

	//
	// Reference to the Mongoose HTTP servers context.
	//
	struct mg_context *httpServerContext;

	//
	// List of URL callbacks added to the HTTP server.
	//
	typedef std::map<std::string, UrlCallback> UrlCallbackMap;
	UrlCallbackMap urlCallbacks;

	//
	// Parse a query string out to a map.
	//
	void ParseQueryString(const char* queryString, StringMap& queryStringMap);


};

