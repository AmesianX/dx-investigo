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
#include "ProxyIDirect3DTexture9.h"
#include "ProxyIDirect3DSurface9.h"
#include "ProxyIDirect3DDevice9.h"

using std::string;

ProxyIDirect3DTexture9::ProxyIDirect3DTexture9(IDirect3DTexture9* _original, ProxyIDirect3DDevice9* proxyDevice, const string& textureName) :
	ProxyIDirect3DBaseTexture9(_original, proxyDevice, textureName),
	original(_original)
{
}

ProxyIDirect3DTexture9::~ProxyIDirect3DTexture9() 
{
	for (unsigned int i = 0; i < surfaceLevels.size(); ++i)
	{
		delete surfaceLevels[i];
	}
}

/*** IUnknown methods ***/
HRESULT __stdcall ProxyIDirect3DTexture9::QueryInterface(REFIID riid, void** ppvObj)
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

ULONG __stdcall ProxyIDirect3DTexture9::AddRef()
{
	return original->AddRef();
}

ULONG __stdcall ProxyIDirect3DTexture9::Release()
{
	ULONG count = original->Release();
	if (count == 0)
	{
		delete this;
	}

	return count;
}

/*** IDirect3DBaseTexture9 methods ***/
HRESULT __stdcall ProxyIDirect3DTexture9::GetDevice(IDirect3DDevice9** ppDevice)
{
	proxyDevice->AddRef();
	*ppDevice = proxyDevice;
	return S_OK;
}

HRESULT __stdcall ProxyIDirect3DTexture9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	return original->SetPrivateData(refguid,pData,SizeOfData,Flags);
}

HRESULT __stdcall ProxyIDirect3DTexture9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return original->GetPrivateData(refguid,pData,pSizeOfData);
}

HRESULT __stdcall ProxyIDirect3DTexture9::FreePrivateData(REFGUID refguid)
{
	return original->FreePrivateData(refguid);
}

DWORD __stdcall ProxyIDirect3DTexture9::SetPriority(DWORD PriorityNew)
{
	return original->SetPriority(PriorityNew);
}

DWORD __stdcall ProxyIDirect3DTexture9::GetPriority()
{
	return original->GetPriority();
}

void __stdcall ProxyIDirect3DTexture9::PreLoad()
{
	return original->PreLoad();
}

D3DRESOURCETYPE __stdcall ProxyIDirect3DTexture9::GetType()
{
	return original->GetType();
}

DWORD __stdcall ProxyIDirect3DTexture9::SetLOD(DWORD LODNew)
{
	return original->SetLOD(LODNew);
}

DWORD __stdcall ProxyIDirect3DTexture9::GetLOD()
{
	return original->GetLOD();
}

DWORD __stdcall ProxyIDirect3DTexture9::GetLevelCount()
{
	return original->GetLevelCount();
}

HRESULT __stdcall ProxyIDirect3DTexture9::SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType)
{
	return original->SetAutoGenFilterType(FilterType);
}

D3DTEXTUREFILTERTYPE __stdcall ProxyIDirect3DTexture9::GetAutoGenFilterType()
{
	return original->GetAutoGenFilterType();
}

void __stdcall ProxyIDirect3DTexture9::GenerateMipSubLevels()
{
	return original->GenerateMipSubLevels();
}

HRESULT __stdcall ProxyIDirect3DTexture9::GetLevelDesc(UINT Level,D3DSURFACE_DESC *pDesc)
{
	return original->GetLevelDesc(Level,pDesc);
}

HRESULT __stdcall ProxyIDirect3DTexture9::GetSurfaceLevel(UINT Level,IDirect3DSurface9** ppSurfaceLevel)
{
	if (surfaceLevels.size() > Level && surfaceLevels[Level] != NULL)
	{
		if (ppSurfaceLevel != NULL)
		{
			surfaceLevels[Level]->AddRef();
			*ppSurfaceLevel = surfaceLevels[Level];
		}

		return S_OK;
	}

	IDirect3DSurface9* originalSurface = NULL;
	HRESULT result = original->GetSurfaceLevel(Level,&originalSurface);
	if (!FAILED(result) && originalSurface != NULL && ppSurfaceLevel != NULL)
	{
		if (surfaceLevels.size() <= Level)
		{
			surfaceLevels.resize(Level+1);
		}
		surfaceLevels[Level] = new ProxyIDirect3DSurface9(originalSurface, proxyDevice, (boost::format("%s_%d") % GetName() % Level).str());
		*ppSurfaceLevel = surfaceLevels[Level];
	}
	else if (ppSurfaceLevel != NULL)
	{
		*ppSurfaceLevel = NULL;
	}

	return result;
}

HRESULT __stdcall ProxyIDirect3DTexture9::LockRect(UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags)
{
	DX_RECORD_API_CALL(IDirect3DTexture9, LockRect)
	return original->LockRect(Level,pLockedRect,pRect,Flags);
}

HRESULT __stdcall ProxyIDirect3DTexture9::UnlockRect(UINT Level)
{
	DX_RECORD_API_CALL(IDirect3DTexture9, UnlockRect)
	return original->UnlockRect(Level);
}

HRESULT __stdcall ProxyIDirect3DTexture9::AddDirtyRect(CONST RECT* pDirtyRect)
{
	DX_RECORD_API_CALL(IDirect3DTexture9, AddDirtyRect)
	return original->AddDirtyRect(pDirtyRect);
}
