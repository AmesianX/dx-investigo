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
#include "ProxyIDirect3DSurface9.h"
#include "ProxyIDirect3DDevice9.h"


ProxyIDirect3DSurface9::ProxyIDirect3DSurface9(IDirect3DSurface9* _original, ProxyIDirect3DDevice9* proxyDevice, const std::string& resourceName) :
	InvestigoResource(proxyDevice, resourceName),
	original(_original)
{
}

ProxyIDirect3DSurface9::~ProxyIDirect3DSurface9() 
{
	proxyDevice->ClearSurface(this);
}

/*** IUnknown methods ***/
HRESULT __stdcall ProxyIDirect3DSurface9::QueryInterface(REFIID riid, void** ppvObj)
{
	return original->QueryInterface(riid, ppvObj);
}


ULONG __stdcall ProxyIDirect3DSurface9::AddRef()
{
	ULONG count = original->AddRef();
	return count;
}

ULONG __stdcall ProxyIDirect3DSurface9::Release()
{
	ULONG count = original->Release();
	if (count == 0)
	{
		delete this;
	}
	return count;
}


/*** IDirect3DResource9 methods ***/
HRESULT __stdcall ProxyIDirect3DSurface9::GetDevice(IDirect3DDevice9** ppDevice)
{
	return original->GetDevice(ppDevice);
}

HRESULT __stdcall ProxyIDirect3DSurface9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	return original->SetPrivateData(refguid,pData,SizeOfData,Flags);
}

HRESULT __stdcall ProxyIDirect3DSurface9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return original->GetPrivateData(refguid,pData,pSizeOfData);
}

HRESULT __stdcall ProxyIDirect3DSurface9::FreePrivateData(REFGUID refguid)
{
	return original->FreePrivateData(refguid);
}

DWORD __stdcall ProxyIDirect3DSurface9::SetPriority(DWORD PriorityNew)
{
	return original->SetPriority(PriorityNew);
}

DWORD __stdcall ProxyIDirect3DSurface9::GetPriority()
{
	return original->GetPriority();
}

void __stdcall ProxyIDirect3DSurface9::PreLoad()
{
	original->PreLoad();
}

D3DRESOURCETYPE __stdcall ProxyIDirect3DSurface9::GetType()
{
	return original->GetType();
}

HRESULT __stdcall ProxyIDirect3DSurface9::GetContainer(REFIID riid,void** ppContainer)
{
	return original->GetContainer(riid,ppContainer);
}

HRESULT __stdcall ProxyIDirect3DSurface9::GetDesc(D3DSURFACE_DESC *pDesc)
{
	return original->GetDesc(pDesc);
}

HRESULT __stdcall ProxyIDirect3DSurface9::LockRect(D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags)
{
	DX_RECORD_API_CALL(IDirect3DSurface9, LockRect)
	return original->LockRect(pLockedRect,pRect,Flags);
}

HRESULT __stdcall ProxyIDirect3DSurface9::UnlockRect()
{
	DX_RECORD_API_CALL(IDirect3DSurface9, UnlockRect)
	return original->UnlockRect();
}

HRESULT __stdcall ProxyIDirect3DSurface9::GetDC(HDC *phdc)
{
	return original->GetDC(phdc);
}

HRESULT __stdcall ProxyIDirect3DSurface9::ReleaseDC(HDC hdc)
{
	return original->ReleaseDC(hdc);
}
