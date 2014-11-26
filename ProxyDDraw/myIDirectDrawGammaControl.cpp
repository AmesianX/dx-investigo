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
#include "myIDirectDrawGammaControl.h"

myIDirectDrawGammaControl::myIDirectDrawGammaControl(IDirectDrawGammaControl * aOriginal)
{
  logf("myIDirectDrawGammaControl ctor\n");
  mOriginal = aOriginal;
}

myIDirectDrawGammaControl::~myIDirectDrawGammaControl()
{
  logf("myIDirectDrawGammaControl dtor\n");
}

HRESULT __stdcall myIDirectDrawGammaControl::QueryInterface(REFIID riid, LPVOID FAR * ppvObj)
{
  EnterCriticalSection(&gCS);
  logf("myIDirectDrawGammaControl::QueryInterface(REFIID, LPVOID FAR * 0x%x);", ppvObj);
  HRESULT x = mOriginal->QueryInterface(riid, ppvObj);
  logfc(" -> return %d\n", x);
  pushtab();
  if (x == 0) genericQueryInterface(riid, ppvObj);
  poptab();
  LeaveCriticalSection(&gCS);
  return x;
}

ULONG __stdcall myIDirectDrawGammaControl::AddRef()
{
  EnterCriticalSection(&gCS);
  logf("myIDirectDrawGammaControl::AddRef();");
  ULONG x = mOriginal->AddRef();
  logfc(" -> return %d\n", x);
  pushtab();
  poptab();
  LeaveCriticalSection(&gCS);
  return x;
}

ULONG __stdcall myIDirectDrawGammaControl::Release()
{
  EnterCriticalSection(&gCS);
  logf("myIDirectDrawGammaControl::Release();");
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

HRESULT __stdcall myIDirectDrawGammaControl::GetGammaRamp(DWORD a, LPDDGAMMARAMP b)
{
  EnterCriticalSection(&gCS);
  logf("myIDirectDrawGammaControl::GetGammaRamp(DWORD %d, LPDDGAMMARAMP 0x%x);", a, b);
  HRESULT x = mOriginal->GetGammaRamp(a, b);
  logfc(" -> return %d\n", x);
  pushtab();
  poptab();
  LeaveCriticalSection(&gCS);
  return x;
}

HRESULT __stdcall myIDirectDrawGammaControl::SetGammaRamp(DWORD a, LPDDGAMMARAMP b)
{
  EnterCriticalSection(&gCS);
  logf("myIDirectDrawGammaControl::SetGammaRamp(DWORD %d, LPDDGAMMARAMP 0x%x);", a, b);
  HRESULT x = mOriginal->SetGammaRamp(a, b);
  logfc(" -> return %d\n", x);
  pushtab();
  poptab();
  LeaveCriticalSection(&gCS);
  return x;
}

