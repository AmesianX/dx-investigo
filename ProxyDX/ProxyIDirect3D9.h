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
#pragma once

#include "Investigo.h"

class jsonstream;

class ProxyIDirect3D9 : public IDirect3D9
{
public:
    ProxyIDirect3D9(IDirect3D9* _original);
    virtual ~ProxyIDirect3D9();

	HRESULT  __stdcall QueryInterface(REFIID riid, void** ppvObj);
    ULONG    __stdcall AddRef();
	ULONG    __stdcall Release();
    HRESULT  __stdcall RegisterSoftwareDevice(void* pInitializeFunction);
	UINT     __stdcall GetAdapterCount();
	HRESULT  __stdcall GetAdapterIdentifier(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier) ;
    UINT     __stdcall GetAdapterModeCount(UINT Adapter, D3DFORMAT Format);
    HRESULT  __stdcall EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode) ;
    HRESULT  __stdcall GetAdapterDisplayMode( UINT Adapter,D3DDISPLAYMODE* pMode) ;
    HRESULT  __stdcall CheckDeviceType(UINT iAdapter,D3DDEVTYPE DevType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed) ;
    HRESULT  __stdcall CheckDeviceFormat(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) ;
    HRESULT  __stdcall CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels) ;
    HRESULT  __stdcall CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) ;
    HRESULT  __stdcall CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat);
    HRESULT  __stdcall GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps) ;
	HMONITOR __stdcall GetAdapterMonitor(UINT Adapter) ;
	HRESULT  __stdcall CreateDevice(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface) ;

	//
	// Format configuration as JSON.
	//
	void FormatConfigAsJSON(jsonstream& output) const;
	
private:

	void FormatAdaptorAsJSON( jsonstream& output, IDirect3D9* d3d, unsigned int adaptorIndex, D3DFORMAT format ) const;
	void FormatModeAsJSON( jsonstream& output, IDirect3D9* d3d, unsigned int adaptorIndex, D3DFORMAT format, unsigned int modeIndex ) const;
	void FormatDeviceCapsAsJSON(D3DDEVTYPE devType, jsonstream& output, IDirect3D9* d3d, unsigned int adaptorIndex) const;
	void FormatDeviceCapsDataAsJSON(jsonstream& output, D3DCAPS9 &caps) const;
		
   	IDirect3D9* original;
};
