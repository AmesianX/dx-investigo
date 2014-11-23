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
#include "ProxyIDirect3D9.h"

HINSTANCE hThisInstance = 0;
HINSTANCE hDirectX = 0;
FARPROC p[14] = {0};

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
        InvestigoSingleton::Init();

        hThisInstance = hInst;
        const char* directXDllPath = InvestigoSingleton::Instance()->GetDirectXDllPath().c_str();
		hDirectX = LoadLibraryA(directXDllPath);            
		if (!hDirectX) 
		{
            InvestigoSingleton::Instance()->ErrorLog() << "Failed to load DirectX DLL: " << directXDllPath << "\n";
            MessageBox(NULL, "Failed to load DirectX dll see error log for details.", "Failed to load DirectX", MB_OK);

            InvestigoSingleton::Deinit();
			
            exit(1); // Abort the appplication, without DirectX it is unlikely to work.
		}

		p[0] = GetProcAddress(hDirectX,"D3DPERF_BeginEvent");
		p[1] = GetProcAddress(hDirectX,"D3DPERF_EndEvent");
		p[2] = GetProcAddress(hDirectX,"D3DPERF_GetStatus");
		p[3] = GetProcAddress(hDirectX,"D3DPERF_QueryRepeatFrame");
		p[4] = GetProcAddress(hDirectX,"D3DPERF_SetMarker");
		p[5] = GetProcAddress(hDirectX,"D3DPERF_SetOptions");
		p[6] = GetProcAddress(hDirectX,"D3DPERF_SetRegion");
		p[7] = GetProcAddress(hDirectX,"DebugSetLevel");
		p[8] = GetProcAddress(hDirectX,"DebugSetMute");
		p[9] = GetProcAddress(hDirectX,"Direct3DCreate9");
		p[10] = GetProcAddress(hDirectX,"Direct3DCreate9Ex");
		p[11] = GetProcAddress(hDirectX,"Direct3DShaderValidatorCreate9");
		p[12] = GetProcAddress(hDirectX,"PSGPError");
		p[13] = GetProcAddress(hDirectX,"PSGPSampleTexture");

	}
	else if (reason == DLL_PROCESS_DETACH)
	{
		InvestigoSingleton::Deinit();

		FreeLibrary(hDirectX);
		hDirectX = NULL;
	}

	return 1;
}

Investigo::Interface* __stdcall GetApplicationInterface()
{
	return InvestigoSingleton::Instance();
}

// D3DPERF_BeginEvent
extern "C" int __stdcall __E__0__( D3DCOLOR col, LPCWSTR wszName ) //todo: be nice to make use of events.
{
	typedef int (WINAPI *pfnD3DPERF_BeginEvent)( D3DCOLOR col, LPCWSTR wszName );
	return ((pfnD3DPERF_BeginEvent) p[0])(col, wszName);
}

// D3DPERF_EndEvent
extern "C" int __stdcall __E__1__()
{
	typedef int (WINAPI *pfnD3DPERF_EndEvent)();
	return ((pfnD3DPERF_EndEvent) p[1])();
}

// D3DPERF_GetStatus
extern "C" __declspec(naked) void __stdcall __E__2__()
{
	__asm
	{
		jmp p[2*4];
	}
}

// D3DPERF_QueryRepeatFrame
extern "C" __declspec(naked) void __stdcall __E__3__()
{
	__asm
	{
		jmp p[3*4];
	}
}

// D3DPERF_SetMarker
extern "C" __declspec(naked) void __stdcall __E__4__()
{
	__asm
	{
		jmp p[4*4];
	}
}

// D3DPERF_SetOptions
extern "C" __declspec(naked) void __stdcall __E__5__()
{
	__asm
	{
		jmp p[5*4];
	}
}

// D3DPERF_SetRegion
extern "C" __declspec(naked) void __stdcall __E__6__()
{
	__asm
	{
		jmp p[6*4];
	}
}

// DebugSetLevel
extern "C" __declspec(naked) void __stdcall __E__7__()
{
	__asm
	{
		jmp p[7*4];
	}
}

// DebugSetMute
extern "C" __declspec(naked) void __stdcall __E__8__()
{
	__asm
	{
		jmp p[8*4];
	}
}

// Direct3DCreate9
IDirect3D9* WINAPI __E__9__(UINT SDKVersion)
{
	typedef IDirect3D9 *(WINAPI* pfnDirect3DCreate9)(UINT SDKVersion);
	IDirect3D9* original = ((pfnDirect3DCreate9) p[9])(SDKVersion);
	return new ProxyIDirect3D9(original);
}

// Direct3DCreate9Ex
extern "C" __declspec(naked) void __stdcall __E__10__()
{
	__asm
	{
		jmp p[10*4];
	}
}

// Direct3DShaderValidatorCreate9
extern "C" __declspec(naked) void __stdcall __E__11__()
{
	__asm
	{
		jmp p[11*4];
	}
}

// PSGPError
extern "C" __declspec(naked) void __stdcall __E__12__()
{
	__asm
	{
		jmp p[12*4];
	}
}

// PSGPSampleTexture
extern "C" __declspec(naked) void __stdcall __E__13__()
{
	__asm
	{
		jmp p[13*4];
	}
}

