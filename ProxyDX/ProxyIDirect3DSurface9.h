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

class ProxyIDirect3DSurface9 : public IDirect3DSurface9, public Investigo::IResource, public InvestigoResource
{
public:
    ProxyIDirect3DSurface9(IDirect3DSurface9* _original, ProxyIDirect3DDevice9* proxyDevice, const std::string& resourceName);
	~ProxyIDirect3DSurface9();

    /*** IUnknown methods ***/
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj);
    STDMETHOD_(ULONG,AddRef)(THIS);
    STDMETHOD_(ULONG,Release)(THIS);

    /*** IDirect3DResource9 methods ***/
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice9** ppDevice);
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags);
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData);
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid);
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew);
    STDMETHOD_(DWORD, GetPriority)(THIS);
    STDMETHOD_(void, PreLoad)(THIS);
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS);
    STDMETHOD(GetContainer)(THIS_ REFIID riid,void** ppContainer);
    STDMETHOD(GetDesc)(THIS_ D3DSURFACE_DESC *pDesc);
    STDMETHOD(LockRect)(THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags);
    STDMETHOD(UnlockRect)(THIS);
    STDMETHOD(GetDC)(THIS_ HDC *phdc);
    STDMETHOD(ReleaseDC)(THIS_ HDC hdc);

    //
    // Get the resource's unique ID.
    //
    virtual int GetId() const { return InvestigoResource::GetId(); }

    //
    // Get the human readable name of the resource.
    //
    virtual const std::string& GetName() const { return InvestigoResource::GetName(); }

    IDirect3DSurface9* GetOriginal() const { return original; }

private:

	IDirect3DSurface9* original;
};
	
