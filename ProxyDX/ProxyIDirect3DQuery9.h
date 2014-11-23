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

class ProxyIDirect3DQuery9 : public IDirect3DQuery9, public Investigo::IResource, public InvestigoResource
{
public:
    ProxyIDirect3DQuery9(IDirect3DQuery9* _original, ProxyIDirect3DDevice9* proxyDevice, const std::string& resourceName) :
		InvestigoResource(proxyDevice, resourceName),
		original(_original) {}

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef)(THIS);
    STDMETHOD_(ULONG,Release)(THIS);

    /*** IDirect3DQuery9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice);
    STDMETHOD_(D3DQUERYTYPE, GetType)(THIS);
    STDMETHOD_(DWORD, GetDataSize)(THIS);
    STDMETHOD(Issue)(THIS_ DWORD dwIssueFlags);
    STDMETHOD(GetData)(THIS_ void* pData,DWORD dwSize,DWORD dwGetDataFlags);

    //
    // Get the resource's unique ID.
    //
    virtual int GetId() const { return InvestigoResource::GetId(); }

    //
    // Get the human readable name of the resource.
    //
    virtual const std::string& GetName() const { return InvestigoResource::GetName(); }

private:

	IDirect3DQuery9* original;
};

