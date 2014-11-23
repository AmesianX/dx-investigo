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

#include <string>

class InvestigoSingleton;
class ProxyIDirect3DDevice9;

//
// A base class for proxy DirectX resources.
//
class InvestigoResource 
{
public:

	InvestigoResource(ProxyIDirect3DDevice9* _proxyDevice, const std::string& resourceName);
	virtual ~InvestigoResource();

	//
	// Retrieve the proxy DX device.
	//
	ProxyIDirect3DDevice9* GetProxyDevice() const { return proxyDevice; }

    //
    // Get the resource's unique ID.
    //
    virtual int GetId() const { return id; }

    //
    // Get the human readable name of the resource.
    //
    virtual const std::string& GetName() const { return name; }

protected:

	//
	// Reference to the proxy device.
	//
	ProxyIDirect3DDevice9* proxyDevice;

	//
	// Unique ID for the resource.
	//
    int id;

    //
    // Name of the resource.
    //
    std::string name;
};

