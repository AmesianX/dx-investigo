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

#include "Investigo.h"
#include "InvestigoResource.h"

class ProxyIDirect3DPixelShader9 : public IDirect3DPixelShader9, public Investigo::IResource, public InvestigoResource
{
public:
	ProxyIDirect3DPixelShader9(IDirect3DPixelShader9* _original, ProxyIDirect3DDevice9* proxyDevice, const std::string& resourceName);
	virtual ~ProxyIDirect3DPixelShader9();

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef)(THIS);
    STDMETHOD_(ULONG,Release)(THIS);

    /*** IDirect3DPixelShader9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice);
    STDMETHOD(GetFunction)(THIS_ void*,UINT* pSizeOfData);
	
    //
    // Get the resource's unique ID.
    //
    virtual int GetId() const { return InvestigoResource::GetId(); }

    //
    // Get the human readable name of the resource.
    //
    virtual const std::string& GetName() const { return InvestigoResource::GetName(); }

    IDirect3DPixelShader9* GetOriginal() const { return original; }

private:

	IDirect3DPixelShader9* original;
};


