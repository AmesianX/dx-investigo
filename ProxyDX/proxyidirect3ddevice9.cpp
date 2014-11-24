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

const int MAX_RENDER_TARGETS = 200;
const int MAX_TEXTURES = 2000;
const int MAX_STREAMS = 2000;

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
	maxTextureIndexBound(0)
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
	return original->QueryInterface(riid, ppvObj);
}

ULONG ProxyIDirect3DDevice9::AddRef()
{
    return original->AddRef();
}

ULONG ProxyIDirect3DDevice9::Release()
{
	return original->Release();

	////fio:
	////char buf[1024];
	////sprintf(buf, "ProxyIDirect3DDevice9::Release[0x%X]: %d\n", this, count);
	////OutputDebugStringA(buf);

	//if (count == 0)
	//{		
	//	delete(this);
	//}

	//return count;
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
	return original->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
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
	return original->CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT ProxyIDirect3DDevice9::GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain)
{
	return original->GetSwapChain(iSwapChain, pSwapChain);
}

UINT ProxyIDirect3DDevice9::GetNumberOfSwapChains()
{
    return original->GetNumberOfSwapChains();
}

HRESULT ProxyIDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	//todo: need to release and restore all cached proxies.
	//todo: record updated presentation parameters.
    return original->Reset(pPresentationParameters);
}

STDMETHODIMP ProxyIDirect3DDevice9::Present(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, Present)

	//InvestigoSingleton::Instance()->RenderHUD(original);

	//{
	//	boost::unique_lock<boost::mutex> lock(screenshotMutex);

	//	LPDIRECT3DSURFACE9 backBuf;
	//	if (!FAILED(original->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuf)))
	//	{
	//		LPD3DXBUFFER buffer = NULL;
	//		if (!FAILED(D3DXSaveSurfaceToFileInMemory(&buffer, D3DXIFF_JPG, backBuf, NULL, NULL)))
	//		{
	//			int size = buffer->GetBufferSize();
	//			screenshotData.resize(size);
	//			memcpy(&screenshotData[0], buffer->GetBufferPointer(), size);

	//			buffer->Release();
	//		}
	//		backBuf->Release();
	//	}
	//}

	HRESULT hres = original->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

	//InvestigoSingleton::Instance()->NotifyFrameEnd();
	return hres;

	//drawCallsLastFrame = drawCallsThisFrame;
	//drawCallsThisFrame = 0;

	//DX_INSPECTOR_SUSPEND_POINT(IDirect3DDevice9, Present)

	//return hres;
}

HRESULT ProxyIDirect3DDevice9::GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetBackBuffer);

	return original->GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
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

	return original->CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

HRESULT ProxyIDirect3DDevice9::CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateVolumeTexture);

	return original->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT ProxyIDirect3DDevice9::CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateCubeTexture);

	return original->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT ProxyIDirect3DDevice9::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateVertexBuffer);

	return original->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT ProxyIDirect3DDevice9::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateIndexBuffer);

	return original->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT ProxyIDirect3DDevice9::CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateRenderTarget);

	return original->CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT ProxyIDirect3DDevice9::CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreateDepthStencilSurface);

	return original->CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT ProxyIDirect3DDevice9::UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, UpdateSurface);

	return original->UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT ProxyIDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, UpdateTexture);

	return original->UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT ProxyIDirect3DDevice9::GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetRenderTargetData);

	return original->GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT ProxyIDirect3DDevice9::GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetFrontBufferData);

	return original->GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT ProxyIDirect3DDevice9::StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter)
{
	return original->StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT ProxyIDirect3DDevice9::ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color)
{
	return original->ColorFill(pSurface, pRect, color);
}

HRESULT ProxyIDirect3DDevice9::CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
	return original->CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT ProxyIDirect3DDevice9::SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget)
{
	return original->SetRenderTarget(RenderTargetIndex, pRenderTarget);
}


HRESULT ProxyIDirect3DDevice9::GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget)
{
	return original->GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT ProxyIDirect3DDevice9::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	return original->SetDepthStencilSurface(pNewZStencil);
}

HRESULT ProxyIDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	return original->GetDepthStencilSurface(ppZStencilSurface);
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
	return original->CreateStateBlock(Type, ppSB);
}

HRESULT ProxyIDirect3DDevice9::BeginStateBlock()
{
	DX_RECORD_API_CALL(IDirect3DDevice9, BeginStateBlock);
    return original->BeginStateBlock();
}

HRESULT ProxyIDirect3DDevice9::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, EndStateBlock);
	return original->EndStateBlock(ppSB);
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
	return original->GetTexture(Stage, ppTexture);
}

HRESULT ProxyIDirect3DDevice9::SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetTexture);
	return original->SetTexture(Stage, pTexture);
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
	return original->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT ProxyIDirect3DDevice9::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
	return original->DrawIndexedPrimitive(PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT ProxyIDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
	return original->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT ProxyIDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
	return original->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT ProxyIDirect3DDevice9::ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags)
{
	return original->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT ProxyIDirect3DDevice9::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl)
{
	return original->CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT ProxyIDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	return original->SetVertexDeclaration(pDecl);
}

HRESULT ProxyIDirect3DDevice9::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	return original->GetVertexDeclaration(ppDecl);
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
	return original->CreateVertexShader(pFunction, ppShader);
}

HRESULT ProxyIDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	return original->SetVertexShader(pShader);
}

HRESULT ProxyIDirect3DDevice9::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	return original->GetVertexShader(ppShader);
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
	return original->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT ProxyIDirect3DDevice9::GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* OffsetInBytes,UINT* pStride)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetStreamSource);
	return original->GetStreamSource(StreamNumber, ppStreamData, OffsetInBytes, pStride);
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
	return original->SetIndices(pIndexData);
}

HRESULT ProxyIDirect3DDevice9::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetIndices);
	return original->GetIndices(ppIndexData);
}

HRESULT ProxyIDirect3DDevice9::CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, CreatePixelShader);
	return original->CreatePixelShader(pFunction, ppShader);
}

HRESULT ProxyIDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, SetPixelShader);
	return original->SetPixelShader(pShader);
}

HRESULT ProxyIDirect3DDevice9::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	DX_RECORD_API_CALL(IDirect3DDevice9, GetPixelShader);
	return original->GetPixelShader(ppShader);
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
	return original->CreateQuery(Type, ppQuery);
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
	data.resize(screenshotData.size());
	memcpy(&data[0], &screenshotData[0], screenshotData.size());

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

