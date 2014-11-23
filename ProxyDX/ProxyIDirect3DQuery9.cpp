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
#include "ProxyIDirect3DQuery9.h"
#include "ProxyIDirect3DDevice9.h"

HRESULT __stdcall  ProxyIDirect3DQuery9::QueryInterface(REFIID riid, void** ppvObj) 
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

ULONG __stdcall  ProxyIDirect3DQuery9::AddRef()
{
	return original->AddRef();
}

ULONG __stdcall  ProxyIDirect3DQuery9::Release()
{
	ULONG count = original->Release();
	if (count == 0)
	{
		original = NULL;
		delete this;
	}

	return count;
}

/*** IDirect3DQuery9 methods ***/
HRESULT __stdcall  ProxyIDirect3DQuery9::GetDevice(IDirect3DDevice9** ppDevice)
{
	proxyDevice->AddRef();
	*ppDevice = proxyDevice;
	return S_OK;
}

D3DQUERYTYPE __stdcall  ProxyIDirect3DQuery9::GetType()
{
	return original->GetType();
}

DWORD __stdcall  ProxyIDirect3DQuery9::GetDataSize()
{
	return original->GetDataSize();
}

HRESULT __stdcall  ProxyIDirect3DQuery9::Issue(DWORD dwIssueFlags)
{
	DX_RECORD_API_CALL(IDirect3DQuery9, Issue)
	return original->Issue(dwIssueFlags);
}

HRESULT __stdcall  ProxyIDirect3DQuery9::GetData(void* pData,DWORD dwSize,DWORD dwGetDataFlags)
{
	DX_RECORD_API_CALL(IDirect3DQuery9, GetData)
	return original->GetData(pData,dwSize,dwGetDataFlags);
}
