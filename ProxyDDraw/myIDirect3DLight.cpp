// Generated with:
// ddwrappergen 1.130524 (c)2013 Jari Komppa http://iki.fi/sol/
//
// If you wish to use the generator, don't do manual changes to this file
// This is your first and only warning.
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
// distribution.

#include "wrapper.h"
#include "myIDirect3DLight.h"

myIDirect3DLight::myIDirect3DLight(IDirect3DLight * aOriginal)
{
  logf("myIDirect3DLight ctor\n");
  mOriginal = aOriginal;
}

myIDirect3DLight::~myIDirect3DLight()
{
  logf("myIDirect3DLight dtor\n");
}

HRESULT __stdcall myIDirect3DLight::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
  EnterCriticalSection(&gCS);
  logf("myIDirect3DLight::QueryInterface(REFIID, LPVOID * 0x%x);", ppvObj);
  HRESULT x = mOriginal->QueryInterface(riid, ppvObj);
  logfc(" -> return %d\n", x);
  pushtab();
  if (x == 0) genericQueryInterface(riid, ppvObj);
  poptab();
  LeaveCriticalSection(&gCS);
  return x;
}

ULONG __stdcall myIDirect3DLight::AddRef()
{
  EnterCriticalSection(&gCS);
  logf("myIDirect3DLight::AddRef();");
  ULONG x = mOriginal->AddRef();
  logfc(" -> return %d\n", x);
  pushtab();
  poptab();
  LeaveCriticalSection(&gCS);
  return x;
}

ULONG __stdcall myIDirect3DLight::Release()
{
  EnterCriticalSection(&gCS);
  logf("myIDirect3DLight::Release();");
  ULONG x = mOriginal->Release();
  logfc(" -> return %d\n", x);
  pushtab();
  if (x == 0)
  {
    wrapstore(mOriginal, 0);
    mOriginal = NULL;
    delete this;
  }
  poptab();
  LeaveCriticalSection(&gCS);
  return x;
}

HRESULT __stdcall myIDirect3DLight::Initialize(LPDIRECT3D a)
{
  EnterCriticalSection(&gCS);
  logf("myIDirect3DLight::Initialize(LPDIRECT3D 0x%x);", a);
  HRESULT x = mOriginal->Initialize((a)?((myIDirect3D *)a)->mOriginal:0);
  logfc(" -> return %d\n", x);
  pushtab();
  poptab();
  LeaveCriticalSection(&gCS);
  return x;
}

HRESULT __stdcall myIDirect3DLight::SetLight(LPD3DLIGHT a)
{
  EnterCriticalSection(&gCS);
  logf("myIDirect3DLight::SetLight(LPD3DLIGHT 0x%x);", a);
  HRESULT x = mOriginal->SetLight(a);
  logfc(" -> return %d\n", x);
  pushtab();
  poptab();
  LeaveCriticalSection(&gCS);
  return x;
}

HRESULT __stdcall myIDirect3DLight::GetLight(LPD3DLIGHT a)
{
  EnterCriticalSection(&gCS);
  logf("myIDirect3DLight::GetLight(LPD3DLIGHT 0x%x);", a);
  HRESULT x = mOriginal->GetLight(a);
  logfc(" -> return %d\n", x);
  pushtab();
  poptab();
  LeaveCriticalSection(&gCS);
  return x;
}

