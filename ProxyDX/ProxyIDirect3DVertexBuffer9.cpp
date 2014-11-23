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
#include "ProxyIDirect3DVertexBuffer9.h"
#include "ProxyIDirect3DDevice9.h"

ProxyIDirect3DVertexBuffer9::ProxyIDirect3DVertexBuffer9(IDirect3DVertexBuffer9* _original, ProxyIDirect3DDevice9* proxyDevice, const std::string& resourceName) :
	InvestigoResource(proxyDevice, resourceName),
	original(_original) 
{
}

ProxyIDirect3DVertexBuffer9::~ProxyIDirect3DVertexBuffer9()
{
	GetProxyDevice()->ClearVertexBuffer(this);
}

/*** IUnknown methods ***/
HRESULT __stdcall ProxyIDirect3DVertexBuffer9::QueryInterface(REFIID riid, void** ppvObj)
{
	*ppvObj = NULL;

    if (riid == __uuidof(Investigo::IResource))
    {
        AddRef();
        *ppvObj = static_cast<Investigo::IResource*>(this);
        return S_OK;
    }

	HRESULT result = original->QueryInterface(riid, ppvObj);
	if (result == S_OK)
	{
		*ppvObj = this;
	}

	return result;
}

ULONG __stdcall ProxyIDirect3DVertexBuffer9::AddRef()
{
	return original->AddRef();
}

ULONG __stdcall ProxyIDirect3DVertexBuffer9::Release()
{
	ULONG count = original->Release();
	if (count == 0)
	{
		original = NULL;
		delete this;
	}
	return count;
}

/*** IDirect3DResource9 methods ***/
HRESULT __stdcall ProxyIDirect3DVertexBuffer9::GetDevice(IDirect3DDevice9** ppDevice)
{
	proxyDevice->AddRef();
	*ppDevice = proxyDevice;
	return S_OK;
}

HRESULT __stdcall ProxyIDirect3DVertexBuffer9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	return original->SetPrivateData(refguid,pData,SizeOfData,Flags);
}

HRESULT __stdcall ProxyIDirect3DVertexBuffer9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return original->GetPrivateData(refguid,pData,pSizeOfData);
}

HRESULT __stdcall ProxyIDirect3DVertexBuffer9::FreePrivateData(REFGUID refguid)
{
	return original->FreePrivateData(refguid);
}

DWORD __stdcall ProxyIDirect3DVertexBuffer9::SetPriority(DWORD PriorityNew)
{
	return original->SetPriority(PriorityNew);
}

DWORD __stdcall ProxyIDirect3DVertexBuffer9::GetPriority()
{
	return original->GetPriority();
}

void __stdcall ProxyIDirect3DVertexBuffer9::PreLoad()
{
	return original->PreLoad();
}

D3DRESOURCETYPE __stdcall ProxyIDirect3DVertexBuffer9::GetType()
{
	return original->GetType();
}

HRESULT __stdcall ProxyIDirect3DVertexBuffer9::Lock(UINT OffsetToLock,UINT SizeToLock,void** ppbData,DWORD Flags)
{
	DX_RECORD_API_CALL(IDirect3DVertexBuffer9, Lock)
	return original->Lock(OffsetToLock,SizeToLock,ppbData,Flags);
}

HRESULT __stdcall ProxyIDirect3DVertexBuffer9::Unlock()
{
	DX_RECORD_API_CALL(IDirect3DVertexBuffer9, Unlock)
	return original->Unlock();
}

HRESULT __stdcall ProxyIDirect3DVertexBuffer9::GetDesc(D3DVERTEXBUFFER_DESC *pDesc)
{
	return original->GetDesc(pDesc);
}

