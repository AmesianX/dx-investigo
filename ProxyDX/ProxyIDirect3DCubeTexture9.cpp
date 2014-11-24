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
#include "ProxyIDirect3DCubeTexture9.h"
#include "ProxyIDirect3DSurface9.h"
#include "ProxyIDirect3DDevice9.h"

/*** IUnknown methods ***/
HRESULT __stdcall ProxyIDirect3DCubeTexture9::QueryInterface(REFIID riid, void** ppvObj)
{
	return original->QueryInterface(riid, ppvObj);
}

ULONG __stdcall ProxyIDirect3DCubeTexture9::AddRef()
{
	return original->AddRef();
}

ULONG __stdcall ProxyIDirect3DCubeTexture9::Release()
{
	ULONG count = original->Release();
	if (count == 0)
	{
		original = NULL;
		delete this;
	}
	return count;
}

/*** IDirect3DBaseTexture9 methods ***/
HRESULT __stdcall ProxyIDirect3DCubeTexture9::GetDevice(IDirect3DDevice9** ppDevice)
{
	return original->GetDevice(ppDevice);
}

HRESULT __stdcall ProxyIDirect3DCubeTexture9::SetPrivateData(REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags)
{
	return original->SetPrivateData(refguid,pData,SizeOfData,Flags);
}

HRESULT __stdcall ProxyIDirect3DCubeTexture9::GetPrivateData(REFGUID refguid,void* pData,DWORD* pSizeOfData)
{
	return original->GetPrivateData(refguid,pData,pSizeOfData);
}

HRESULT __stdcall ProxyIDirect3DCubeTexture9::FreePrivateData(REFGUID refguid)
{
	return original->FreePrivateData(refguid);
}

DWORD __stdcall ProxyIDirect3DCubeTexture9::SetPriority(DWORD PriorityNew)
{
	return original->SetPriority(PriorityNew);
}

DWORD __stdcall ProxyIDirect3DCubeTexture9::GetPriority()
{
	return original->GetPriority();
}

void __stdcall ProxyIDirect3DCubeTexture9::PreLoad()
{
	return original->PreLoad();
}

D3DRESOURCETYPE __stdcall ProxyIDirect3DCubeTexture9::GetType()
{
	return original->GetType();
}

DWORD __stdcall ProxyIDirect3DCubeTexture9::SetLOD(DWORD LODNew)
{
	return original->SetLOD(LODNew);
}

DWORD __stdcall ProxyIDirect3DCubeTexture9::GetLOD()
{
	return original->GetLOD();
}

DWORD __stdcall ProxyIDirect3DCubeTexture9::GetLevelCount()
{
	return original->GetLevelCount();
}

HRESULT __stdcall ProxyIDirect3DCubeTexture9::SetAutoGenFilterType(D3DTEXTUREFILTERTYPE FilterType)
{
	return original->SetAutoGenFilterType(FilterType);
}

D3DTEXTUREFILTERTYPE __stdcall ProxyIDirect3DCubeTexture9::GetAutoGenFilterType()
{
	return original->GetAutoGenFilterType();
}

void __stdcall ProxyIDirect3DCubeTexture9::GenerateMipSubLevels()
{
	return original->GenerateMipSubLevels();
}

HRESULT __stdcall ProxyIDirect3DCubeTexture9::GetLevelDesc(UINT Level,D3DSURFACE_DESC *pDesc)
{
	return original->GetLevelDesc(Level,pDesc);
}

HRESULT __stdcall ProxyIDirect3DCubeTexture9::GetCubeMapSurface(D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface9** ppCubeMapSurface)
{
	return original->GetCubeMapSurface(FaceType, Level, ppCubeMapSurface);
}

HRESULT __stdcall ProxyIDirect3DCubeTexture9::LockRect(D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags)
{
	DX_RECORD_API_CALL(IDirect3DCubeTexture9, LockRect);
	return original->LockRect(FaceType,Level,pLockedRect,pRect,Flags);
}

HRESULT __stdcall ProxyIDirect3DCubeTexture9::UnlockRect(D3DCUBEMAP_FACES FaceType,UINT Level)
{
	DX_RECORD_API_CALL(IDirect3DCubeTexture9, UnlockRect);
	return original->UnlockRect(FaceType,Level);
}

HRESULT __stdcall ProxyIDirect3DCubeTexture9::AddDirtyRect(D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect)
{
	DX_RECORD_API_CALL(IDirect3DCubeTexture9, AddDirtyRect);
	return original->AddDirtyRect(FaceType,pDirtyRect);
}

