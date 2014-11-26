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
#include "ProxyIDirect3DSwapChain9.h"
#include "ProxyIDirect3DSurface9.h"
#include "ProxyIDirect3DDevice9.h"

/*** IUnknown methods ***/
HRESULT __stdcall ProxyIDirect3DSwapChain9::QueryInterface(REFIID riid, void** ppvObj)
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

ULONG __stdcall ProxyIDirect3DSwapChain9::AddRef()
{
	return original->AddRef();
}

ULONG __stdcall ProxyIDirect3DSwapChain9::Release()
{
	ULONG count = original->Release();
	if (count == 0)
	{
		original = NULL;
		delete this;
	}
	return count;
}


/*** IDirect3DSwapChain9 methods ***/
HRESULT __stdcall ProxyIDirect3DSwapChain9::Present(CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion,DWORD dwFlags)
{
	return original->Present(pSourceRect,pDestRect,hDestWindowOverride,pDirtyRegion,dwFlags);
}

HRESULT __stdcall ProxyIDirect3DSwapChain9::GetFrontBufferData(IDirect3DSurface9* pDestSurface)
{
	ProxyIDirect3DSurface9* pProxyDestSurface = dynamic_cast<ProxyIDirect3DSurface9*>(pDestSurface); 
	return original->GetFrontBufferData(pProxyDestSurface->GetOriginal()); 
}

HRESULT __stdcall ProxyIDirect3DSwapChain9::GetBackBuffer(UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
{
	IDirect3DSurface9* originalSurface = NULL;
	HRESULT result = original->GetBackBuffer(iBackBuffer,Type,&originalSurface);
	*ppBackBuffer = new ProxyIDirect3DSurface9(originalSurface, proxyDevice, (boost::format("%s_%d") % GetName() % iBackBuffer).str());
	return result;
}

HRESULT __stdcall ProxyIDirect3DSwapChain9::GetRasterStatus(D3DRASTER_STATUS* pRasterStatus)
{
	return original->GetRasterStatus(pRasterStatus);
}

HRESULT __stdcall ProxyIDirect3DSwapChain9::GetDisplayMode(D3DDISPLAYMODE* pMode)
{
	return original->GetDisplayMode(pMode);
}

HRESULT __stdcall ProxyIDirect3DSwapChain9::GetDevice(IDirect3DDevice9** ppDevice)
{
	proxyDevice->AddRef();
	*ppDevice = proxyDevice;
	return S_OK;
}

HRESULT __stdcall ProxyIDirect3DSwapChain9::GetPresentParameters(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return original->GetPresentParameters(pPresentationParameters);
}
