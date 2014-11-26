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
#include "Investigo.h"
#include "ProxyIDirect3DDevice9.h"
#include "DXStateUtils.h"
#include "jsonstream.h"

#include <time.h>
#include <sstream>

using std::stringstream;

#undef assert

#define assert(x) if (!(x))  { char buf[1024]; sprintf(buf, "Assert failed: %s\n", #x); OutputDebugStringA(buf); }

const int MAX_RENDER_TARGETS = 20;
const int MAX_TEXTURES = 20;
const int MAX_STREAMS = 20;

ProxyIDirect3DDevice9::ProxyIDirect3DDevice9(IDirect3DDevice9* _original, UINT _adapter, D3DDEVTYPE _deviceType, HWND _focusWindow, DWORD _behaviorFlags, D3DPRESENT_PARAMETERS* _presentationParameters) :
	original(_original),
	curVertexDecl(NULL),
	curFvf(0),
	curVertexShader(NULL),
	curPixelShader(NULL),
	indexBuffer(NULL),
	backBuffer(NULL),
	depthStencilSurface(NULL),
	adapter(_adapter),
	deviceType(_deviceType),
	focusWindow(_focusWindow),
	behaviorFlags(_behaviorFlags),
	presentationParameters(*_presentationParameters),
	drawCallsLastFrame(0),
	drawCallsThisFrame(0),
	maxTextureIndexBound(0),
	pSprite(NULL)
{
	//char buf[1024];
	//sprintf(buf, "ProxyIDirect3DDevice9::ProxyIDirect3DDevice9: 0x%X\n", this);
	//OutputDebugStringA(buf); //fio:

	renderTargets.resize(MAX_RENDER_TARGETS, NULL);
	depthStencilSurface = NULL;
	textures.resize(MAX_TEXTURES, NULL);
	streams.resize(MAX_STREAMS, NULL);
	renderState.resize(RENDER_STATE_MAX, 0);

	InvestigoSingleton::Instance()->SetDevice(this);
}

ProxyIDirect3DDevice9::~ProxyIDirect3DDevice9()
{
	//char buf[1024];
	//sprintf(buf, "ProxyIDirect3DDevice9::~ProxyIDirect3DDevice9: 0x%X\n", this);
	//OutputDebugStringA(buf); //fio:

	InvestigoSingleton::Instance()->SetDevice(NULL);
}

HRESULT ProxyIDirect3DDevice9::QueryInterface (REFIID riid, void** ppvObj)
{
	*ppvObj = NULL;

	HRESULT result = original->QueryInterface(riid, ppvObj);
	if (result == S_OK)
	{
		ULONG count = original->AddRef()-1;
		original->Release();

		//char buf[1024];
		//sprintf(buf, "ProxyIDirect3DDevice9::QueryInterface[0x%X]: %d\n", this, count);
		//OutputDebugStringA(buf);

		*ppvObj = this;
	}

	return result;
}

ULONG ProxyIDirect3DDevice9::AddRef()
{
    ULONG count = original->AddRef();
	//fio:
	//char buf[1024];
	//sprintf(buf, "ProxyIDirect3DDevice9::AddRef[0x%X]: %d\n", this, count);
	//OutputDebugStringA(buf);

	return count;
}

ULONG ProxyIDirect3DDevice9::Release()
{
	ULONG count = original->Release();

	//fio:
	//char buf[1024];
	//sprintf(buf, "ProxyIDirect3DDevice9::Release[0x%X]: %d\n", this, count);
	//OutputDebugStringA(buf);

	if (count == 0)
	{		
		delete(this);
	}

	return count;
}

HRESULT ProxyIDirect3DDevice9::TestCooperativeLevel()
{
    return original->TestCooperativeLevel();
}

UINT ProxyIDirect3DDevice9::GetAvailableTextureMem()
{
    return original->GetAvailableTextureMem();
}

HRESULT ProxyIDirect3DDevice9::EvictManagedResources()
{
    return original->EvictManagedResources();
}

HRESULT ProxyIDirect3DDevice9::GetDirect3D(IDirect3D9** ppD3D9)
{
    return original->GetDirect3D(ppD3D9);
}

HRESULT ProxyIDirect3DDevice9::GetDeviceCaps(D3DCAPS9* pCaps)
{
    return original->GetDeviceCaps(pCaps);
}

HRESULT ProxyIDirect3DDevice9::GetDisplayMode(UINT iSwapChain,D3DDISPLAYMODE* pMode)
{
    return original->GetDisplayMode(iSwapChain, pMode);
}

HRESULT ProxyIDirect3DDevice9::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
    return original->GetCreationParameters(pParameters);
}

HRESULT ProxyIDirect3DDevice9::SetCursorProperties(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap)
{
	ProxyIDirect3DSurface9* proxySurface = dynamic_cast<ProxyIDirect3DSurface9*>(pCursorBitmap); 
	return original->SetCursorProperties(XHotSpot,YHotSpot,proxySurface->GetOriginal());
}

void ProxyIDirect3DDevice9::SetCursorPosition(int X,int Y,DWORD Flags)
{
    return original->SetCursorPosition(X,Y,Flags);
}

BOOL ProxyIDirect3DDevice9::ShowCursor(BOOL bShow)
{
    return original->ShowCursor(bShow);
}

HRESULT ProxyIDirect3DDevice9::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain)  
{
	IDirect3DSwapChain9* originalSwapChain = NULL;
	HRESULT result = original->CreateAdditionalSwapChain(pPresentationParameters,&originalSwapChain);
	if (!FAILED(result) && originalSwapChain != NULL)
	{
		if (pSwapChain != NULL)
		{
			*pSwapChain = new ProxyIDirect3DSwapChain9(originalSwapChain, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else if (pSwapChain != NULL)
	{
		*pSwapChain = NULL;
	}
	
	return result;
}

HRESULT ProxyIDirect3DDevice9::GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain)
{
	IDirect3DSwapChain9* originalSwapChain = NULL;
	HRESULT result = original->GetSwapChain(iSwapChain,&originalSwapChain);
	if (!FAILED(result) && originalSwapChain != NULL)
	{
		*pSwapChain = new ProxyIDirect3DSwapChain9(originalSwapChain, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
	}
	else
	{
		*pSwapChain = NULL;
	}
	
	return result;    
}

UINT ProxyIDirect3DDevice9::GetNumberOfSwapChains()
{
    return original->GetNumberOfSwapChains();
}

HRESULT ProxyIDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	//todo: need to release and restore all cached proxies.
	//todo: record updated presentation parameters.
	if (pSprite != NULL) {
		pSprite->Release();
		pSprite = NULL;
	}

	InvestigoSingleton::Instance()->ResetHUD();
    return original->Reset(pPresentationParameters);
}

void log(const char* x) {
	FILE * pFile = NULL;
	fopen_s(&pFile, "d3device.log", "a");
	if (pFile != NULL) {
		fputs(x, pFile);
		fputs("\n", pFile);
		fclose(pFile);
	}
}
//
//struct PixelShaderInput
//{
//	float3 color : COLOR;
//};
//
//struct PixelShaderOutput
//{
//	float4 color : SV_TARGET0;
//};
//
//PixelShaderOutput main(PixelShaderInput input)
//{
//	PixelShaderOutput output;
//	output.color.rgba = float4(input.color, 1.0f); // input.color is 0.5, 0.5, 0.5; output is black
//	// output.color.rgba = float4(0.5f, 0.5f, 0.5f, 1); // output is gray
//	return output;
//}

STDMETHODIMP ProxyIDirect3DDevice9::Present(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, Present)
	

	InvestigoSingleton::Instance()->RenderHUD(original);
	//{
	//	boost::unique_lock<boost::mutex> lock(screenshotMutex);

	//	LPDIRECT3DSURFACE9 backBuf;
	//	if (!FAILED(original->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuf)))
	//	{
	//		LPD3DXBUFFER buffer = NULL;
	//		RECT rc;
	//		POINT pt;
	//		//SetRect(&rc, 14, 806, 464, 1038);
	//		SetRect(&rc, 14, 6, 464, 238);
	//		pt.x = 0;
	//		pt.y = 0;
	//		RECT rcDest;
	//		SetRect(&rcDest, 0, 0, rc.right - rc.left, rc.bottom - rc.top);
	//		IDirect3DSurface9* tempsurf;

	//		D3DSURFACE_DESC desc;
	//		backBuf->GetDesc(&desc);
	//		
	//		if (!FAILED(original->CreateOffscreenPlainSurface(rc.right - rc.left, rc.bottom - rc.top, desc.Format, D3DPOOL_DEFAULT, &tempsurf, NULL)))
	//		{
	//			if (pSprite == NULL) {
	//				D3DXCreateSprite(original, &pSprite);
	//			}
	//			original->BeginScene();
	//			pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	//			if (!FAILED(original->StretchRect(backBuf, &rc, tempsurf, &rcDest, D3DTEXF_POINT))) {
	//			//if (!FAILED(original->UpdateSurface(backBuf, &rc, tempsurf, &pt))) {

	//				//if (!FAILED(D3DXSaveSurfaceToFileInMemory(&buffer, D3DXIFF_DDS, backBuf, NULL, &rc)))
	//				if (!FAILED(D3DXSaveSurfaceToFileInMemory(&buffer, D3DXIFF_PNG, tempsurf, NULL, NULL)))
	//				{
	//					int size = buffer->GetBufferSize();
	//					screenshotData.resize(size);
	//					memcpy(&screenshotData[0], buffer->GetBufferPointer(), size);

	//					buffer->Release();
	//					log("Success");
	//				}
	//				else {
	//					log("failed D3DXSaveSurfaceToFileInMemory");
	//				}
	//			}
	//			else {
	//				log("failed StretchRect");
	//			}
	//			pSprite->End();
	//			original->EndScene();
	//			tempsurf->Release();
	//		}
	//		else {
	//			log("failed CreateOffscreenPlainSurface 2");
	//		}
	//		backBuf->Release();
	//	}
	//}

	HRESULT hres = original->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	//Sleep(50);
	InvestigoSingleton::Instance()->NotifyFrameEnd();

	drawCallsLastFrame = drawCallsThisFrame;
	drawCallsThisFrame = 0;

	DX_INSPECTOR_SUSPEND_POINT(IDirect3DDevice9, Present)

	return hres;
}

HRESULT ProxyIDirect3DDevice9::GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetBackBuffer);

	if (backBuffer != NULL)
	{
		if (ppBackBuffer != NULL)
		{
			backBuffer->AddRef();
			*ppBackBuffer = backBuffer;
		}

		return S_OK;
	}
 
	IDirect3DSurface9* originalSurface = NULL;
	HRESULT result = original->GetBackBuffer(iSwapChain,iBackBuffer,Type,&originalSurface);
	if (!FAILED(result) && originalSurface != NULL)
	{
		if (ppBackBuffer != NULL)
		{
			backBuffer = new ProxyIDirect3DSurface9(originalSurface, this, "BackBuffer");
			*ppBackBuffer = backBuffer;
		}
	}
	else if (ppBackBuffer != NULL)
	{
		*ppBackBuffer = NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus)
{
    return original->GetRasterStatus(iSwapChain,pRasterStatus);
}

HRESULT ProxyIDirect3DDevice9::SetDialogBoxMode(BOOL bEnableDialogs)
{
    return original->SetDialogBoxMode(bEnableDialogs);
}

void ProxyIDirect3DDevice9::SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp)
{
    return original->SetGammaRamp(iSwapChain,Flags,pRamp);
}

void ProxyIDirect3DDevice9::GetGammaRamp(UINT iSwapChain,D3DGAMMARAMP* pRamp)
{
    return original->GetGammaRamp(iSwapChain,pRamp);
}

HRESULT ProxyIDirect3DDevice9::CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateTexture);

	IDirect3DTexture9* originalTexture = NULL;
	HRESULT result = original->CreateTexture(Width,Height,Levels,Usage,Format,Pool,&originalTexture,pSharedHandle);
	if (!FAILED(result) && originalTexture != NULL)
	{
		if (ppTexture != NULL)
		{
			*ppTexture = new ProxyIDirect3DTexture9(originalTexture, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else if (ppTexture != NULL)
	{
		*ppTexture =  NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateVolumeTexture);

	IDirect3DVolumeTexture9* originalTexture = NULL;
	HRESULT result = original->CreateVolumeTexture(Width,Height,Depth,Levels,Usage,Format,Pool,&originalTexture,pSharedHandle);
	if (!FAILED(result) && originalTexture != NULL)
	{
		if (ppVolumeTexture != NULL)
		{
			*ppVolumeTexture = new ProxyIDirect3DVolumeTexture9(originalTexture, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else if (ppVolumeTexture != NULL)
	{
		*ppVolumeTexture = NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateCubeTexture);

	IDirect3DCubeTexture9* originalTexture = NULL;
	HRESULT result = original->CreateCubeTexture(EdgeLength,Levels,Usage,Format,Pool,&originalTexture,pSharedHandle);
	if (!FAILED(result) && originalTexture != NULL)
	{
		if (ppCubeTexture != NULL)
		{
			*ppCubeTexture = new ProxyIDirect3DCubeTexture9(originalTexture, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else if (ppCubeTexture != NULL)
	{
		*ppCubeTexture = NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateVertexBuffer);

	IDirect3DVertexBuffer9* originalVertexBuffer = NULL;
    HRESULT result = original->CreateVertexBuffer(Length,Usage,FVF,Pool,&originalVertexBuffer,pSharedHandle);
	if (!FAILED(result) && originalVertexBuffer != NULL)
	{
		if (ppVertexBuffer != NULL)
		{
            *ppVertexBuffer = new ProxyIDirect3DVertexBuffer9(originalVertexBuffer, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else if (ppVertexBuffer != NULL)
	{
		*ppVertexBuffer = NULL;
	}
	
	return result;
}

HRESULT ProxyIDirect3DDevice9::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateIndexBuffer);

	IDirect3DIndexBuffer9* originalIndexBuffer = NULL;
    HRESULT result = original->CreateIndexBuffer(Length,Usage,Format,Pool,&originalIndexBuffer,pSharedHandle);
	if (!FAILED(result) && originalIndexBuffer != NULL)
	{
		if (ppIndexBuffer != NULL)
		{
            *ppIndexBuffer = new ProxyIDirect3DIndexBuffer9(originalIndexBuffer, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else if (ppIndexBuffer != NULL)
	{
		*ppIndexBuffer = NULL;
	}
	
	return result;
}

HRESULT ProxyIDirect3DDevice9::CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateRenderTarget);

	IDirect3DSurface9* originalRenderTarget = NULL;
	HRESULT result = original->CreateRenderTarget(Width,Height,Format,MultiSample,MultisampleQuality,Lockable,&originalRenderTarget,pSharedHandle);
	if (!FAILED(result) && originalRenderTarget != NULL)
	{
		if (ppSurface != NULL)
		{
			*ppSurface = new ProxyIDirect3DSurface9(originalRenderTarget, this, InvestigoSingleton::Instance()->FormatCurrentResourceName("RenderTarget"));
		}
	}
	else if (ppSurface != NULL)
	{
		*ppSurface = NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateDepthStencilSurface);

	IDirect3DSurface9* originalSurface = NULL;
	HRESULT result = original->CreateDepthStencilSurface(Width,Height,Format,MultiSample,MultisampleQuality,Discard,&originalSurface,pSharedHandle);
	if (!FAILED(result) && originalSurface != NULL)
	{
		if (ppSurface != NULL)
		{
            *ppSurface = new ProxyIDirect3DSurface9(originalSurface, this, InvestigoSingleton::Instance()->FormatCurrentResourceName("DepthStencil"));
		}
	}
	else if (ppSurface != NULL)
	{
		*ppSurface = NULL;
	}
	return result;
}

HRESULT ProxyIDirect3DDevice9::UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, UpdateSurface);

	ProxyIDirect3DSurface9* sourceProxy = dynamic_cast<ProxyIDirect3DSurface9*>(pSourceSurface); 
	ProxyIDirect3DSurface9* destProxy = dynamic_cast<ProxyIDirect3DSurface9*>(pDestinationSurface); 
	return original->UpdateSurface(sourceProxy->GetOriginal(),pSourceRect,destProxy->GetOriginal(),pDestPoint);
}

HRESULT ProxyIDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, UpdateTexture);

	ProxyIDirect3DBaseTexture9* proxySourceTexture = dynamic_cast<ProxyIDirect3DBaseTexture9*>(pSourceTexture);
	ProxyIDirect3DBaseTexture9* proxyDestinationTexture = dynamic_cast<ProxyIDirect3DBaseTexture9*>(pDestinationTexture);
	return original->UpdateTexture(proxySourceTexture->GetOriginal(),proxyDestinationTexture->GetOriginal());
}

HRESULT ProxyIDirect3DDevice9::GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetRenderTargetData);

	ProxyIDirect3DSurface9* proxyRenderTarget = dynamic_cast<ProxyIDirect3DSurface9*>(pRenderTarget); 
	ProxyIDirect3DSurface9* proxyDest = dynamic_cast<ProxyIDirect3DSurface9*>(pDestSurface); 
	return original->GetRenderTargetData(proxyRenderTarget->GetOriginal(),proxyDest->GetOriginal());
}

HRESULT ProxyIDirect3DDevice9::GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetFrontBufferData);

	ProxyIDirect3DSurface9* proxySurface = dynamic_cast<ProxyIDirect3DSurface9*>(pDestSurface); 
	return original->GetFrontBufferData(iSwapChain,proxySurface->GetOriginal());
}

HRESULT ProxyIDirect3DDevice9::StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, StretchRect);

	ProxyIDirect3DSurface9* proxySourceSurface = dynamic_cast<ProxyIDirect3DSurface9*>(pSourceSurface); 
	ProxyIDirect3DSurface9* proxyDestSurface = dynamic_cast<ProxyIDirect3DSurface9*>(pDestSurface); 
	return original->StretchRect(proxySourceSurface->GetOriginal(),pSourceRect,proxyDestSurface->GetOriginal(),pDestRect,Filter);
}

HRESULT ProxyIDirect3DDevice9::ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, ColorFill);

	ProxyIDirect3DSurface9* proxySurface = dynamic_cast<ProxyIDirect3DSurface9*>(pSurface); 
	return original->ColorFill(proxySurface->GetOriginal(),pRect,color);
}

HRESULT ProxyIDirect3DDevice9::CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateOffscreenPlainSurface);

	IDirect3DSurface9* originalSurface = NULL;
	HRESULT result = original->CreateOffscreenPlainSurface(Width,Height,Format,Pool,&originalSurface,pSharedHandle);
	if (!FAILED(result) && originalSurface != NULL)
	{
		if (ppSurface != NULL)
		{
            *ppSurface = new ProxyIDirect3DSurface9(originalSurface, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else
	{
		if (ppSurface != NULL)
		{
			*ppSurface = NULL;
		}
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetRenderTarget);
	

	ProxyIDirect3DSurface9* proxyRenderTarget = dynamic_cast<ProxyIDirect3DSurface9*>(pRenderTarget); 

	if (pRenderTarget != renderTargets[RenderTargetIndex])
	{
		renderTargets[RenderTargetIndex] = proxyRenderTarget;
	}

	if (pRenderTarget == NULL)
	{
		return original->SetRenderTarget(RenderTargetIndex,NULL);
	}
	else
	{
		return original->SetRenderTarget(RenderTargetIndex,proxyRenderTarget->GetOriginal());
	}
}


HRESULT ProxyIDirect3DDevice9::GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetRenderTarget);

	if (renderTargets[RenderTargetIndex] != NULL)
	{
		if (ppRenderTarget != NULL)
		{
			renderTargets[RenderTargetIndex]->AddRef();
			*ppRenderTarget = renderTargets[RenderTargetIndex];
		}
		return S_OK;
	}

	IDirect3DSurface9* originalSurface = NULL;
	HRESULT result = original->GetRenderTarget(RenderTargetIndex,&originalSurface);
	if (!FAILED(result) && originalSurface != NULL)
	{
		if (ppRenderTarget != NULL)
		{
            renderTargets[RenderTargetIndex] = new ProxyIDirect3DSurface9(originalSurface, this, InvestigoSingleton::Instance()->FormatCurrentResourceName("RenderTarget"));
			*ppRenderTarget = renderTargets[RenderTargetIndex];
		}
	}
	else if (ppRenderTarget != NULL)
	{
		*ppRenderTarget = NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetDepthStencilSurface);

	ProxyIDirect3DSurface9* proxyNewZStencil = dynamic_cast<ProxyIDirect3DSurface9*>(pNewZStencil); 
	if (pNewZStencil != depthStencilSurface)
	{
		depthStencilSurface = proxyNewZStencil;
	}

	if (proxyNewZStencil == NULL)
	{
		return original->SetDepthStencilSurface(NULL);
	}
	else
	{
		return original->SetDepthStencilSurface(proxyNewZStencil->GetOriginal());
	}
}

HRESULT ProxyIDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetDepthStencilSurface);

	if (depthStencilSurface != NULL)
	{
		if (ppZStencilSurface != NULL)
		{
			depthStencilSurface->AddRef();
			*ppZStencilSurface = depthStencilSurface;
		}

		return S_OK;
	}

	IDirect3DSurface9* originalSurface = NULL;
	HRESULT result = original->GetDepthStencilSurface(&originalSurface);
	if (!FAILED(result) && originalSurface != NULL)
	{
		if (ppZStencilSurface != NULL)
		{
			depthStencilSurface = new ProxyIDirect3DSurface9(originalSurface, this, "DepthStencil");
			*ppZStencilSurface = depthStencilSurface;
		}
	}
	else if (ppZStencilSurface != NULL)
	{
		*ppZStencilSurface = NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::BeginScene()
{
	DX_RECORD_API_CALL(IDirect3DDevice9, BeginScene);
	
    return original->BeginScene();
}

HRESULT ProxyIDirect3DDevice9::EndScene()
{
	DX_RECORD_API_CALL(IDirect3DDevice9, EndScene);
	
	return original->EndScene();
}

HRESULT ProxyIDirect3DDevice9::Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, Clear);
    return original->Clear(Count,pRects,Flags,Color,Z,Stencil);
}

HRESULT ProxyIDirect3DDevice9::SetTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetTransform);
    return original->SetTransform(State, pMatrix);
}

HRESULT ProxyIDirect3DDevice9::GetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetTransform);
    return original->GetTransform(State,pMatrix);
}

HRESULT ProxyIDirect3DDevice9::MultiplyTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, MultiplyTransform);
    return original->MultiplyTransform(State,pMatrix);
}

HRESULT ProxyIDirect3DDevice9::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetViewport);
    return original->SetViewport(pViewport);
}

HRESULT ProxyIDirect3DDevice9::GetViewport(D3DVIEWPORT9* pViewport)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetViewport);
    return original->GetViewport(pViewport);
}

HRESULT ProxyIDirect3DDevice9::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetMaterial);
    return original->SetMaterial(pMaterial);
}

HRESULT ProxyIDirect3DDevice9::GetMaterial(D3DMATERIAL9* pMaterial)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetMaterial);
    return original->GetMaterial(pMaterial);
}

HRESULT ProxyIDirect3DDevice9::SetLight(DWORD Index,CONST D3DLIGHT9* pLight)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetLight);
    return original->SetLight(Index,pLight);
}

HRESULT ProxyIDirect3DDevice9::GetLight(DWORD Index,D3DLIGHT9* pLight)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetLight);
    return original->GetLight(Index,pLight);
}

HRESULT ProxyIDirect3DDevice9::LightEnable(DWORD Index,BOOL Enable)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, LightEnable);
    return original->LightEnable(Index,Enable);
}

HRESULT ProxyIDirect3DDevice9::GetLightEnable(DWORD Index,BOOL* pEnable)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetLightEnable);
    return original->GetLightEnable(Index, pEnable);
}

HRESULT ProxyIDirect3DDevice9::SetClipPlane(DWORD Index,CONST float* pPlane)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetClipPlane);
    return original->SetClipPlane(Index, pPlane);
}

HRESULT ProxyIDirect3DDevice9::GetClipPlane(DWORD Index,float* pPlane)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetClipPlane);
    return original->GetClipPlane(Index,pPlane);
}

HRESULT ProxyIDirect3DDevice9::SetRenderState(D3DRENDERSTATETYPE State,DWORD Value)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetRenderState);
	
	assert(State >= 0 && State < RENDER_STATE_MAX);
	renderState[State] = Value;
    return original->SetRenderState(State, Value);
}

HRESULT ProxyIDirect3DDevice9::GetRenderState(D3DRENDERSTATETYPE State,DWORD* pValue)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetRenderState);
    return original->GetRenderState(State, pValue);
}

HRESULT ProxyIDirect3DDevice9::CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateStateBlock);

	IDirect3DStateBlock9* originalStateBlock = NULL;
    HRESULT result = original->CreateStateBlock(Type,&originalStateBlock);
	if (!FAILED(result) && originalStateBlock != NULL)
	{
		if (ppSB != NULL)
		{
			*ppSB = new ProxyIDirect3DStateBlock9(Type, originalStateBlock, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else if (ppSB != NULL)
	{
		*ppSB = NULL;
	}
	
	return result;
}

HRESULT ProxyIDirect3DDevice9::BeginStateBlock()
{
	DX_RECORD_API_CALL(IDirect3DDevice9, BeginStateBlock);
    return original->BeginStateBlock();
}

HRESULT ProxyIDirect3DDevice9::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, EndStateBlock);

	IDirect3DStateBlock9* originalStateBlock = NULL;
    HRESULT result = original->EndStateBlock(&originalStateBlock);
	if (!FAILED(result) && originalStateBlock != NULL)
	{
		if (ppSB != NULL)
		{
			*ppSB = new ProxyIDirect3DStateBlock9((D3DSTATEBLOCKTYPE)0, originalStateBlock, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else if (ppSB != NULL)
	{
		*ppSB = NULL;
	}
	
	return result;
}

HRESULT ProxyIDirect3DDevice9::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
    return original->SetClipStatus(pClipStatus);
}

HRESULT ProxyIDirect3DDevice9::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
    return original->GetClipStatus(pClipStatus);
}

HRESULT ProxyIDirect3DDevice9::GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetTexture);

	if (textures[Stage] != NULL)
	{
		if (ppTexture != NULL)
		{
			textures[Stage]->AddRef();
			*ppTexture = textures[Stage];
		}

		return S_OK;
	}

	IDirect3DBaseTexture9* originalTexture = NULL;
	HRESULT result = original->GetTexture(Stage,&originalTexture);
	if (!FAILED(result) && originalTexture != NULL)
	{
		if (ppTexture != NULL)
		{
			textures[Stage] = new ProxyIDirect3DBaseTexture9(originalTexture, this, "<get-texture>");
			*ppTexture = textures[Stage];
		}
	}
	else if (ppTexture != NULL)
	{
		*ppTexture = NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetTexture);
	

	ProxyIDirect3DBaseTexture9* proxyTexture = dynamic_cast<ProxyIDirect3DBaseTexture9*>(pTexture);

	if (pTexture != textures[Stage])
	{

		textures[Stage] = proxyTexture;

		//
		// Bound textures have been changed, compute total.
		//
		maxTextureIndexBound = 0;

		for (unsigned int textureIndex = 0; textureIndex < textures.size(); ++textureIndex) //todo: this seems a bit wasteful.
		{
			if (textures[textureIndex] != NULL)
			{
				maxTextureIndexBound = textureIndex;
			}
		}
	}

	if (proxyTexture == NULL)
	{
		return original->SetTexture(Stage,NULL);
	}
	else
	{
		return original->SetTexture(Stage,proxyTexture->GetOriginal());
	}

}

HRESULT ProxyIDirect3DDevice9::GetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetTextureStageState);
    return original->GetTextureStageState(Stage,Type, pValue);
}

HRESULT ProxyIDirect3DDevice9::SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetTextureStageState);
	
    return original->SetTextureStageState(Stage,Type,Value);
}

HRESULT ProxyIDirect3DDevice9::GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetSamplerState);
    return original->GetSamplerState(Sampler,Type, pValue);
}

HRESULT ProxyIDirect3DDevice9::SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetSamplerState);
	
    return original->SetSamplerState(Sampler,Type,Value);
}

HRESULT ProxyIDirect3DDevice9::ValidateDevice(DWORD* pNumPasses)
{
    return original->ValidateDevice(pNumPasses);
}

HRESULT ProxyIDirect3DDevice9::SetPaletteEntries(UINT PaletteNumber,CONST PALETTEENTRY* pEntries)
{
    return original->SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT ProxyIDirect3DDevice9::GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries)
{
    return original->GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT ProxyIDirect3DDevice9::SetCurrentTexturePalette(UINT PaletteNumber)
{
    return original->SetCurrentTexturePalette(PaletteNumber);
}

HRESULT ProxyIDirect3DDevice9::GetCurrentTexturePalette(UINT *PaletteNumber)
{
    return original->GetCurrentTexturePalette(PaletteNumber);
}

HRESULT ProxyIDirect3DDevice9::SetScissorRect(CONST RECT* pRect)
{
    return original->SetScissorRect(pRect);
}

HRESULT ProxyIDirect3DDevice9::GetScissorRect( RECT* pRect)
{
    return original->GetScissorRect(pRect);
}

HRESULT ProxyIDirect3DDevice9::SetSoftwareVertexProcessing(BOOL bSoftware)
{
    return original->SetSoftwareVertexProcessing(bSoftware);
}

BOOL ProxyIDirect3DDevice9::GetSoftwareVertexProcessing()
{
    return original->GetSoftwareVertexProcessing();
}

HRESULT ProxyIDirect3DDevice9::SetNPatchMode(float nSegments)
{
    return original->SetNPatchMode(nSegments);
}

float ProxyIDirect3DDevice9::GetNPatchMode()
{
    return original->GetNPatchMode();
}

HRESULT ProxyIDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount)
{
	++drawCallsThisFrame;

	DX_RECORD_DRAW_CALL(IDirect3DDevice9, DrawPrimitive);
	

	if (!InvestigoSingleton::Instance()->DrawCallsEnabled())
	{
		return S_OK;
	}

    HRESULT res = original->DrawPrimitive(PrimitiveType,StartVertex,PrimitiveCount);

	DX_DRAW_CALL_SUSPEND_POINT(IDirect3DDevice9, DrawPrimitive);

	return res;
}

HRESULT ProxyIDirect3DDevice9::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
	++drawCallsThisFrame;

	DX_RECORD_DRAW_CALL(IDirect3DDevice9, DrawIndexedPrimitive);
	

	if (!InvestigoSingleton::Instance()->DrawCallsEnabled())
	{
		return S_OK;
	}

    HRESULT res = original->DrawIndexedPrimitive(PrimitiveType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount);

	DX_DRAW_CALL_SUSPEND_POINT(IDirect3DDevice9, DrawIndexedPrimitive);

	return res;
}

HRESULT ProxyIDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
	++drawCallsThisFrame;

	DX_RECORD_DRAW_CALL(IDirect3DDevice9, DrawPrimitiveUP);
	

	if (!InvestigoSingleton::Instance()->DrawCallsEnabled())
	{
		return S_OK;
	}

	HRESULT res = original->DrawPrimitiveUP(PrimitiveType,PrimitiveCount,pVertexStreamZeroData,VertexStreamZeroStride);

	DX_DRAW_CALL_SUSPEND_POINT(IDirect3DDevice9, DrawPrimitiveUP);

	return res;
}

HRESULT ProxyIDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
	++drawCallsThisFrame;

	DX_RECORD_DRAW_CALL(IDirect3DDevice9, DrawIndexedPrimitiveUP);
	

	if (!InvestigoSingleton::Instance()->DrawCallsEnabled())
	{
		return S_OK;
	}

	HRESULT res = original->DrawIndexedPrimitiveUP(PrimitiveType,MinVertexIndex,NumVertices,PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData,VertexStreamZeroStride);

	DX_DRAW_CALL_SUSPEND_POINT(IDirect3DDevice9, DrawIndexedPrimitiveUP);

	return res;
}

HRESULT ProxyIDirect3DDevice9::ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, ProcessVertices);

	ProxyIDirect3DVertexDeclaration9* proxyVertexDecl = dynamic_cast<ProxyIDirect3DVertexDeclaration9*>(pVertexDecl); 
	ProxyIDirect3DVertexBuffer9* proxyDestBuffer = dynamic_cast<ProxyIDirect3DVertexBuffer9*>(pDestBuffer); 
	return original->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, proxyDestBuffer->GetOriginal(), proxyVertexDecl->GetOriginal(), Flags);
}

HRESULT ProxyIDirect3DDevice9::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateVertexDeclaration);
	

	IDirect3DVertexDeclaration9* originalVertexDecl = NULL;
    HRESULT result = original->CreateVertexDeclaration(pVertexElements,&originalVertexDecl);
	if (!FAILED(result) && originalVertexDecl != NULL)
	{
		if (ppDecl != NULL)
		{
            *ppDecl = new ProxyIDirect3DVertexDeclaration9(originalVertexDecl, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else if (ppDecl != NULL)
	{
		*ppDecl = NULL;
	}
	
	return result;
}

HRESULT ProxyIDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetVertexDeclaration);
	

	ProxyIDirect3DVertexDeclaration9* proxyDecl = dynamic_cast<ProxyIDirect3DVertexDeclaration9*>(pDecl); 

	if (pDecl != curVertexDecl)
	{
		curVertexDecl = proxyDecl;
	}

	if (pDecl == NULL)
	{
		return original->SetVertexDeclaration(NULL);
	}
	else
	{
		return original->SetVertexDeclaration(proxyDecl->GetOriginal());
	}
}

HRESULT ProxyIDirect3DDevice9::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetVertexDeclaration);

	if (curVertexDecl != NULL)
	{
		if (ppDecl != NULL)
		{
			curVertexDecl->AddRef();
			*ppDecl = curVertexDecl;
		}

		return S_OK;
	}

	IDirect3DVertexDeclaration9* originalVertexDecl = NULL;
    HRESULT result = original->GetVertexDeclaration(&originalVertexDecl);
	if (!FAILED(result) && originalVertexDecl != NULL)
	{
		if (ppDecl != NULL)
		{
			curVertexDecl = new ProxyIDirect3DVertexDeclaration9(originalVertexDecl, this, "VertexDeclaration");
			*ppDecl = curVertexDecl;
		}
	}
	else if (ppDecl != NULL)
	{
		*ppDecl = NULL;
	}
	
    return result;
}

HRESULT ProxyIDirect3DDevice9::SetFVF(DWORD FVF)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetFVF);
	
    return original->SetFVF(FVF);
}

HRESULT ProxyIDirect3DDevice9::GetFVF(DWORD* pFVF)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetFVF);
    return original->GetFVF(pFVF);
}

HRESULT ProxyIDirect3DDevice9::CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateVertexShader);
	

	IDirect3DVertexShader9* originalShader = NULL;
    HRESULT result = original->CreateVertexShader(pFunction,&originalShader);
	if (!FAILED(result) && originalShader != NULL)
	{
		*ppShader = new ProxyIDirect3DVertexShader9(originalShader, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
	}
	else
	{
		*ppShader = NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetVertexShader);
	

	ProxyIDirect3DVertexShader9* proxyShader = dynamic_cast<ProxyIDirect3DVertexShader9*>(pShader);
	IDirect3DVertexShader9* actualShader = proxyShader != NULL ? proxyShader->GetOriginal() : NULL;
	IDirect3DVertexShader9* curActualShader = curVertexShader != NULL ? curVertexShader->GetOriginal() : NULL;

	if (actualShader != curActualShader)
	{
		curVertexShader = proxyShader;
	}


	if (proxyShader == NULL)
	{
		return original->SetVertexShader(NULL);
	}
	else
	{		
		return original->SetVertexShader(actualShader);
	}
}

HRESULT ProxyIDirect3DDevice9::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetVertexShader);

	if (curVertexShader != NULL)
	{
		if (ppShader != NULL)
		{
			curVertexShader->AddRef();
			*ppShader = curVertexShader;
		}

		return S_OK;
	}

	IDirect3DVertexShader9* originalShader = NULL;
	HRESULT result = original->GetVertexShader(&originalShader);
	if (!FAILED(result) && originalShader != NULL)
	{
		if (ppShader != NULL)
		{
			curVertexShader = new ProxyIDirect3DVertexShader9(originalShader, this, "unknown");
			*ppShader = curVertexShader;
		}
	}
	else if (ppShader != NULL)
	{
		*ppShader = NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetVertexShaderConstantF);
	
    return original->SetVertexShaderConstantF(StartRegister,pConstantData, Vector4fCount);
}

HRESULT ProxyIDirect3DDevice9::GetVertexShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetVertexShaderConstantF);
    return original->GetVertexShaderConstantF(StartRegister,pConstantData,Vector4fCount);
}

HRESULT ProxyIDirect3DDevice9::SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetVertexShaderConstantI);
	
    return original->SetVertexShaderConstantI(StartRegister,pConstantData,Vector4iCount);
}

HRESULT ProxyIDirect3DDevice9::GetVertexShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetVertexShaderConstantI);
    return original->GetVertexShaderConstantI(StartRegister,pConstantData,Vector4iCount);
}

HRESULT ProxyIDirect3DDevice9::SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetVertexShaderConstantB);
	
    return original->SetVertexShaderConstantB(StartRegister,pConstantData,BoolCount);
}

HRESULT ProxyIDirect3DDevice9::GetVertexShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetVertexShaderConstantB);
    return original->GetVertexShaderConstantB(StartRegister,pConstantData,BoolCount);
}

HRESULT ProxyIDirect3DDevice9::SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetStreamSource);
	

	ProxyIDirect3DVertexBuffer9* proxyStreamData = dynamic_cast<ProxyIDirect3DVertexBuffer9*>(pStreamData); 
	if (pStreamData != streams[StreamNumber])
	{
		streams[StreamNumber] = proxyStreamData;
	}

	if (pStreamData == NULL)
	{
		HRESULT result = original->SetStreamSource(StreamNumber,NULL,OffsetInBytes,Stride);
		return result;
	}
	else
	{		
		assert(proxyStreamData != NULL);
		HRESULT result = original->SetStreamSource(StreamNumber,proxyStreamData->GetOriginal(),OffsetInBytes,Stride);
		return result;
	}
}

HRESULT ProxyIDirect3DDevice9::GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* OffsetInBytes,UINT* pStride)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetStreamSource);

	if (streams[StreamNumber] != NULL)
	{
		if (ppStreamData != NULL)
		{
			streams[StreamNumber]->AddRef();
			*ppStreamData = streams[StreamNumber];
		}

		return S_OK;
	}

	IDirect3DVertexBuffer9* originalVertexBuffer = NULL;
    HRESULT result = original->GetStreamSource(StreamNumber,&originalVertexBuffer,OffsetInBytes,pStride); //todo: might be good to pass in NULL if ppStreamData is set to NULL.
	if (!FAILED(result) && originalVertexBuffer != NULL)
	{
		if (ppStreamData != NULL)
		{
			*ppStreamData = new ProxyIDirect3DVertexBuffer9(originalVertexBuffer, this, (boost::format("VertexBuffer_%d") % StreamNumber).str());
		}
	}
	else
	{
		if (ppStreamData != NULL)
		{
			*ppStreamData = NULL;
		}
	}
	
    return result;
}

HRESULT ProxyIDirect3DDevice9::SetStreamSourceFreq(UINT StreamNumber,UINT Divider)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetStreamSourceFreq);
	
    return original->SetStreamSourceFreq(StreamNumber,Divider);
}

HRESULT ProxyIDirect3DDevice9::GetStreamSourceFreq(UINT StreamNumber,UINT* Divider)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetStreamSourceFreq);
    return original->GetStreamSourceFreq(StreamNumber,Divider);
}

HRESULT ProxyIDirect3DDevice9::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetIndices);
	

	ProxyIDirect3DIndexBuffer9* pProxyIndexData = dynamic_cast<ProxyIDirect3DIndexBuffer9*>(pIndexData);
	if (pIndexData != indexBuffer)
	{
		indexBuffer = pProxyIndexData;
	}

	if (pIndexData == NULL)
	{
		HRESULT result = original->SetIndices(NULL);
		return result;
	}
	else
	{		
		assert(pProxyIndexData != NULL);
		HRESULT result = original->SetIndices(pProxyIndexData->GetOriginal());
		return result;
	}
}

HRESULT ProxyIDirect3DDevice9::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetIndices);

	if (indexBuffer != NULL)
	{
		if (ppIndexData != NULL)
		{
			indexBuffer->AddRef();
			*ppIndexData = indexBuffer;
		}

		return S_OK;		
	}

	IDirect3DIndexBuffer9* originalIndexBuffer = NULL;
    HRESULT result = original->GetIndices(&originalIndexBuffer);
	if (!FAILED(result) && originalIndexBuffer != NULL)
	{
		if (ppIndexData != NULL)
		{
			*ppIndexData = new ProxyIDirect3DIndexBuffer9(originalIndexBuffer, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
	}
	else
	{
		if (ppIndexData != NULL)
		{
			*ppIndexData = NULL;
		}
	}
	
    return result;
}

HRESULT ProxyIDirect3DDevice9::CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreatePixelShader);
	

	IDirect3DPixelShader9* originalShader = NULL;
    HRESULT result = original->CreatePixelShader(pFunction,&originalShader);
	if (!FAILED(result) && originalShader != NULL)
 	{
        *ppShader = new ProxyIDirect3DPixelShader9(originalShader, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
	}
	else
	{
		*ppShader = NULL;
	}

	return result;
}

HRESULT ProxyIDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetPixelShader);
	

	ProxyIDirect3DPixelShader9* proxyShader = dynamic_cast<ProxyIDirect3DPixelShader9*>(pShader);
	IDirect3DPixelShader9* pActualShader = proxyShader != NULL ? proxyShader->GetOriginal() : NULL;
	IDirect3DPixelShader9* pCurSetShader = curPixelShader != NULL ? curPixelShader->GetOriginal() : NULL;

	if (pActualShader != pCurSetShader)
	{
		curPixelShader = proxyShader;
	}

	if (pShader == NULL)
	{
		HRESULT result = original->SetPixelShader(NULL);
		return result;
	}
	else
	{		
		return original->SetPixelShader(proxyShader->GetOriginal());
	}
}

HRESULT ProxyIDirect3DDevice9::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetPixelShader);

	if (curPixelShader != NULL)
	{
		if (ppShader != NULL)
		{
			curPixelShader->AddRef();
			*ppShader = curPixelShader;
		}

		return S_OK;
	}

	IDirect3DPixelShader9* originalShader = NULL;
	HRESULT result = original->GetPixelShader(&originalShader);
	if (!FAILED(result) && originalShader != NULL)
	{
		if (ppShader != NULL)
		{
			curPixelShader = new ProxyIDirect3DPixelShader9(originalShader, this, "unknown");
			*ppShader = curPixelShader;
		}
	}
	else if (ppShader != NULL)
	{
		*ppShader = NULL;
	}

	return result;	
}

HRESULT ProxyIDirect3DDevice9::SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetPixelShaderConstantF);
	
    return original->SetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount);
}

HRESULT ProxyIDirect3DDevice9::GetPixelShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetPixelShaderConstantF);
    return original->GetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount);
}

HRESULT ProxyIDirect3DDevice9::SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetPixelShaderConstantI);
	
    return original->SetPixelShaderConstantI(StartRegister,pConstantData,Vector4iCount);
}

HRESULT ProxyIDirect3DDevice9::GetPixelShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetPixelShaderConstantI);
    return original->GetPixelShaderConstantI(StartRegister,pConstantData,Vector4iCount);
}

HRESULT ProxyIDirect3DDevice9::SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetPixelShaderConstantB);
	
    return original->SetPixelShaderConstantB(StartRegister,pConstantData,BoolCount);
}

HRESULT ProxyIDirect3DDevice9::GetPixelShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetPixelShaderConstantB);
	return original->GetPixelShaderConstantB(StartRegister,pConstantData,BoolCount);
}

HRESULT ProxyIDirect3DDevice9::DrawRectPatch(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, DrawRectPatch);
    return original->DrawRectPatch(Handle,pNumSegs, pRectPatchInfo);
}

HRESULT ProxyIDirect3DDevice9::DrawTriPatch(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, DrawTriPatch);
    return original->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT ProxyIDirect3DDevice9::DeletePatch(UINT Handle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, DeletePatch);
    return original->DeletePatch(Handle);
}

HRESULT ProxyIDirect3DDevice9::CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateQuery);

	IDirect3DQuery9* originalQuery = NULL;
	HRESULT result = original->CreateQuery(Type, ppQuery == NULL ? NULL : &originalQuery);
	if (ppQuery != NULL)
	{
		if (!FAILED(result) && originalQuery != NULL)
		{
			*ppQuery = new ProxyIDirect3DQuery9(originalQuery, this, InvestigoSingleton::Instance()->FormatCurrentResourceName());
		}
		else
		{
			*ppQuery = NULL;
		}
	}
	return result;
}

//
// Format the state of the device as JSON.
//
void ProxyIDirect3DDevice9::FormatStateAsJSON(jsonstream& output) const
{
	for (int renderStateDataIndex = 0; renderStateDataIndex < RENDER_STATE_DATA_SIZE; ++renderStateDataIndex)
	{
		const RenderStateData& renderStateDataEntry = GetRenderStateData(renderStateDataIndex);
		int currentValue = renderState[renderStateDataEntry.renderStateIndex];
		const char* value = renderStateDataEntry.parseRenderStateOption(currentValue);

		output << jsonstream::openObject
		       << "name" << renderStateDataEntry.name
			   << "value" << value
			   << jsonstream::closeObject;
	}
}

//
// Get a screenshot of the current backbuffer.
//
void ProxyIDirect3DDevice9::GetBackbufferScreenshot(std::vector<unsigned char>& data)
{
	/*
	RECT DesktopRect;
	GetClientRect(GetDesktopWindow(), &DesktopRect);

	//todo: this would need mods to work with fullscreen app.
	IDirect3DSurface9* pSurface;
	if (FAILED(original->CreateOffscreenPlainSurface(DesktopRect.right, DesktopRect.bottom, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM,  &pSurface, NULL)))
	{
		return;
	}

	if (FAILED(original->GetFrontBufferData(0, pSurface)))
	{
		pSurface->Release();
		return;
	}

	LPD3DXBUFFER buffer = NULL;
	if (!FAILED(D3DXSaveSurfaceToFileInMemory(&buffer, D3DXIFF_JPG, pSurface, NULL, NULL)))
	{
		int size = buffer->GetBufferSize();
		data.resize(size);
		memcpy(&data[0], buffer->GetBufferPointer(), size);

		buffer->Release();
	}

	pSurface->Release();
	*/

	boost::unique_lock<boost::mutex> lock(screenshotMutex);
	if (screenshotData.size() == 0) {
		data.resize(0);
		return;
	} else {
		data.resize(screenshotData.size());
		memcpy(&data[0], &screenshotData[0], screenshotData.size());
	}
}

//
// Get a screenshot of the render target.
// http://stackoverflow.com/questions/120066/doing-readback-from-direct3d-textures-and-surfaces
//
void ProxyIDirect3DDevice9::GetRenderTargetScreenshot(std::vector<unsigned char>& data)
{
	/*todo:
	if (renderTargets.size() == 0 || renderTargets[0] == NULL)
	{
	return;
	}

	ProxyIDirect3DSurface9* proxyRenderTarget = renderTargets[0];
	IDirect3DSurface9* renderTarget = proxyRenderTarget->GetOriginal();
	*/

	IDirect3DSurface9* renderTarget = NULL;
	if (FAILED(original->GetRenderTarget(0, &renderTarget)))
	{
		return;
	}

	if (renderTarget == NULL)
	{
		return;
	}

	D3DSURFACE_DESC rtDesc;
	if (FAILED(renderTarget->GetDesc(&rtDesc)))
	{
		renderTarget->Release();
		return; //todo: error msg.
	}

	IDirect3DSurface9* resolvedSurface = NULL;
	if (rtDesc.MultiSampleType != D3DMULTISAMPLE_NONE)
	{
		//
		// GetRenderTargetData fails with multi-sampled render targets.
		// Need to copy to a non-multi-sample render target.
		//
		if (FAILED(original->CreateRenderTarget(rtDesc.Width, rtDesc.Height, rtDesc.Format, D3DMULTISAMPLE_NONE, 0, FALSE, &resolvedSurface, NULL)))
		{
			return; 
		}

		if (FAILED(StretchRect(renderTarget, NULL, resolvedSurface, NULL, D3DTEXF_NONE)))
		{
			resolvedSurface->Release();
			return;
		}
		
		renderTarget = resolvedSurface;
	}

	IDirect3DSurface9* offscreenSurface;
	if (!FAILED(original->CreateOffscreenPlainSurface(rtDesc.Width, rtDesc.Height, rtDesc.Format, D3DPOOL_SYSTEMMEM, &offscreenSurface, NULL)))
	{
		if (!FAILED(original->GetRenderTargetData(renderTarget, offscreenSurface)))
		{
			LPD3DXBUFFER buffer = NULL;
			if (!FAILED(D3DXSaveSurfaceToFileInMemory(&buffer, D3DXIFF_JPG, offscreenSurface, NULL, NULL)))
			{
				int size = buffer->GetBufferSize();
				data.resize(size);
				memcpy(&data[0], buffer->GetBufferPointer(), size);

				buffer->Release();
			}
			else
			{
				//todo: error msg;
				int x = 3;
			}
		}
		else
		{
			//todo: error msg;
			int x = 3;
		}

		offscreenSurface->Release();
	}
	else
	{
		//todo: error msg;
		int x = 3;
	}

	if (resolvedSurface)
	{
		resolvedSurface->Release();
	}

	renderTarget->Release();
}

//
// Retreive the data for a currently bound texture.
//
void ProxyIDirect3DDevice9::GetBoundTexture(unsigned int index, std::vector<unsigned char>& data)
{
	if (textures.size() <= index || textures[index] == NULL)
	{
		return;
	}

	/*
	ProxyIDirect3DTexture9* texture = dynamic_cast<ProxyIDirect3DTexture9*>(textures[index]);
	if (texture == NULL) //todo: implement this for other textures as well.
	{
		return;
	}
	*/

	IDirect3DBaseTexture9* curTexture = NULL;
	if (FAILED(original->GetTexture(index, &curTexture)))
	{
		return;
	}

	if (curTexture == NULL)
	{
		return;
	}

	IDirect3DTexture9* originalTexture = NULL;
	if (FAILED(curTexture->QueryInterface(IID_IDirect3DTexture9, (void**)&originalTexture)))
	{
		curTexture->Release();
		return;
	}

	D3DSURFACE_DESC desc;
	if (FAILED(originalTexture->GetLevelDesc(0, &desc)))
	{
		originalTexture->Release();
		curTexture->Release();
		return;
	}

	IDirect3DSurface9* surface;
	if (FAILED(originalTexture->GetSurfaceLevel(0, &surface)))
	{
		originalTexture->Release();
		curTexture->Release();
		return; //todo: need a logging system to report errors.
	}

	LPD3DXBUFFER buffer = NULL;
	if (!FAILED(D3DXSaveSurfaceToFileInMemory(&buffer, D3DXIFF_JPG, surface, NULL, NULL)))
	{
		int size = buffer->GetBufferSize();
		data.resize(size);
		memcpy(&data[0], buffer->GetBufferPointer(), size);

		buffer->Release();
	}
	else
	{
		//todo: err msg.
		int x = 3;
	
	}

	surface->Release();
	originalTexture->Release();
	curTexture->Release();
}

//
// Dump a screenshot to the specified file.
//
bool ProxyIDirect3DDevice9::TakeScreenshot(const std::string& filePath, D3DXIMAGE_FILEFORMAT fileFormat)
{
	LPDIRECT3DSURFACE9 backBuf;
	if (!FAILED(original->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuf)))
	{
		bool ok = !FAILED(D3DXSaveSurfaceToFileA(filePath.c_str(), fileFormat, backBuf, NULL, NULL));

		backBuf->Release();

		return ok;
	}

	return false;
}

//
// Remove any cached references to the DX objects.
//
void ProxyIDirect3DDevice9::ClearSurface(ProxyIDirect3DSurface9* surface)
{
	for (unsigned int i = 0; i < renderTargets.size(); ++i)
	{
		if (renderTargets[i] == surface)
		{
			renderTargets[i] = NULL;
		}
	}

	if (depthStencilSurface == surface)
	{
		depthStencilSurface = NULL;
	}

	if (backBuffer == surface)
	{
		backBuffer = NULL;
	}
}

void ProxyIDirect3DDevice9::ClearTexture(ProxyIDirect3DBaseTexture9* texture)
{
	for (unsigned int i = 0; i < textures.size(); ++i)
	{
		if (textures[i] == texture)
		{
			textures[i] = NULL;
		}
	}
}

void ProxyIDirect3DDevice9::ClearVertexShader(ProxyIDirect3DVertexShader9* shader)
{
	if (curVertexShader == shader)
	{
		curVertexShader = NULL;
	}
}

void ProxyIDirect3DDevice9::ClearPixelShader(ProxyIDirect3DPixelShader9* shader)
{
	if (curPixelShader == shader)
	{
		 curPixelShader = NULL;
	}
}

void ProxyIDirect3DDevice9::ClearIndexBuffer(ProxyIDirect3DIndexBuffer9* buffer)
{
	if (indexBuffer == buffer)
	{
		indexBuffer = NULL;			 
	}
}

void ProxyIDirect3DDevice9::ClearVertexBuffer(ProxyIDirect3DVertexBuffer9* buffer)
{
	for (unsigned int i = 0; i < streams.size(); ++i)
	{
		if (streams[i] == buffer)
		{
			streams[i] = NULL;
		}
	}
}

void ProxyIDirect3DDevice9::ClearVertexDecl(ProxyIDirect3DVertexDeclaration9* decl)
{
	if (curVertexDecl == decl)
	{
		curVertexDecl = NULL;
	}
}

//
// Format device configuration as JSON.
//
//todo: could a generic way to format pages of information and return them, this would be part of the HTTP lib.
void ProxyIDirect3DDevice9::FormatConfigAsJSON(jsonstream& output) const //todo: make this fn more data driven, or move to a util fn.
{
	stringstream focusWindowStr;
	focusWindowStr << "0x" << std::hex << focusWindow << std::dec;

	stringstream hDeviceWindowStr;
	hDeviceWindowStr << "0x" << std::hex << presentationParameters.hDeviceWindow << std::dec;

	output  << jsonstream::openObject
			<< "name" << "IDirect3D9::CreateDevice"
			<< "value" << jsonstream ::openArray
			<< jsonstream::openObject
			<< "name" << "Adapter"
			<< "value" << adapter
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "DeviceType"
			<< "value" << DeviceTypeToString(deviceType)
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "hFocusWindow"
			<< "value" << focusWindowStr.str()
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "BehaviorFlags"
			<< "value" << BehaviourFlagsToString(behaviorFlags)
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "pPresentationParameters"
			<< "value" << jsonstream::openArray
			<< jsonstream::openObject
			<< "name" << "BackBufferWidth"
			<< "value" << presentationParameters.BackBufferWidth
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "BackBufferHeight"
			<< "value" << presentationParameters.BackBufferHeight
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "BackBufferFormat"
			<< "value" << FormatToString(presentationParameters.BackBufferFormat)
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "BackBufferCount"
			<< "value" << presentationParameters.BackBufferCount
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "MultiSampleType"
			<< "value" << MultiSampleTypeToString(presentationParameters.MultiSampleType)
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "MultiSampleQuality"
			<< "value" << presentationParameters.MultiSampleQuality
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "SwapEffect"
			<< "value" << SwapEffectToString(presentationParameters.SwapEffect)
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "hDeviceWindow"
			<< "value" << hDeviceWindowStr.str()
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "Windowed"
			<< "value" << presentationParameters.Windowed
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "EnableAutoDepthStencil"
			<< "value" << presentationParameters.EnableAutoDepthStencil
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "AutoDepthStencilFormat"
			<< "value" << FormatToString(presentationParameters.AutoDepthStencilFormat)
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "Flags"
			<< "value" << PresentFlagsToString(presentationParameters.Flags)
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "FullScreen_RefreshRateInHz"
			<< "value" << presentationParameters.FullScreen_RefreshRateInHz
			<< jsonstream::closeObject
			<< jsonstream::openObject
			<< "name" << "PresentationInterval"
			<< "value" << presentationParameters.PresentationInterval
			<< jsonstream::closeObject
			<< jsonstream::closeArray
			<< jsonstream::closeObject
			<< jsonstream::closeArray
			<< jsonstream::closeObject;
}

