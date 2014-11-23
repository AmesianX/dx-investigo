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
#include "ProxyIDirect3D9.h"
#include "ProxyIDirect3DDevice9.h"
#include "DXStateUtils.h"
#include "jsonstream.h"

extern ProxyIDirect3DDevice9* g_pDevice;

ProxyIDirect3D9::ProxyIDirect3D9(IDirect3D9 *_original) :
	original(_original)
{
	InvestigoSingleton::Instance()->SetD3D(this);
}

ProxyIDirect3D9::~ProxyIDirect3D9()
{
    InvestigoSingleton::Instance()->SetD3D(NULL);
}

HRESULT __stdcall ProxyIDirect3D9::QueryInterface(REFIID riid, void** ppvObj)
{
    *ppvObj = NULL;

	HRESULT hRes = original->QueryInterface(riid, ppvObj); 
	if (hRes == S_OK)
	{
		*ppvObj = this;
	}
	
	return hRes;
}

ULONG __stdcall ProxyIDirect3D9::AddRef(void)
{
    return original->AddRef();
}

ULONG __stdcall ProxyIDirect3D9::Release(void)
{
	ULONG count = original->Release();
	if (count == 0) 
	{
  	    delete(this); 
	}

	return(count);
}

HRESULT __stdcall ProxyIDirect3D9::RegisterSoftwareDevice(void* pInitializeFunction)
{
    return original->RegisterSoftwareDevice(pInitializeFunction);
}

UINT __stdcall ProxyIDirect3D9::GetAdapterCount(void)
{
    return original->GetAdapterCount();
}

HRESULT __stdcall ProxyIDirect3D9::GetAdapterIdentifier(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier)
{
    return original->GetAdapterIdentifier(Adapter,Flags,pIdentifier);
}

UINT __stdcall ProxyIDirect3D9::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
    return original->GetAdapterModeCount(Adapter, Format);
}

HRESULT __stdcall ProxyIDirect3D9::EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode)
{
    return original->EnumAdapterModes(Adapter,Format,Mode,pMode);
}

HRESULT __stdcall ProxyIDirect3D9::GetAdapterDisplayMode( UINT Adapter,D3DDISPLAYMODE* pMode)
{
    return original->GetAdapterDisplayMode(Adapter,pMode);
}

HRESULT __stdcall ProxyIDirect3D9::CheckDeviceType(UINT iAdapter,D3DDEVTYPE DevType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed)
{
    return original->CheckDeviceType(iAdapter,DevType,DisplayFormat,BackBufferFormat,bWindowed);
}

HRESULT __stdcall ProxyIDirect3D9::CheckDeviceFormat(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat)
{
    return original->CheckDeviceFormat(Adapter,DeviceType,AdapterFormat,Usage,RType,CheckFormat);
}

HRESULT __stdcall ProxyIDirect3D9::CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels)
{
    return original->CheckDeviceMultiSampleType(Adapter,DeviceType,SurfaceFormat,Windowed,MultiSampleType,pQualityLevels);
}

HRESULT __stdcall ProxyIDirect3D9::CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat)
{
    return original->CheckDepthStencilMatch(Adapter,DeviceType,AdapterFormat,RenderTargetFormat,DepthStencilFormat);
}

HRESULT __stdcall ProxyIDirect3D9::CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat)
{
    return original->CheckDeviceFormatConversion(Adapter,DeviceType,SourceFormat,TargetFormat);
}

HRESULT __stdcall ProxyIDirect3D9::GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps)
{
    return original->GetDeviceCaps(Adapter,DeviceType,pCaps);
}

HMONITOR __stdcall ProxyIDirect3D9::GetAdapterMonitor(UINT Adapter)
{
    return original->GetAdapterMonitor(Adapter);
}

HRESULT __stdcall ProxyIDirect3D9::CreateDevice(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppResult)
{
	// Look for 'NVIDIA PerfHUD' adapter
	// If it is present, override default settings

	/*todo: experimental code to enable NVPerfHUD, doesn't seem to work tho.

	char buf[1024]; 

	char dir[1024];
	GetCurrentDirectoryA(1024, dir);
	sprintf(buf, "Dir: %s\n", dir);
	OutputDebugStringA(buf);

	sprintf(buf, "Searching %d adapters\n", original->GetAdapterCount()); 
	OutputDebugStringA(buf);

	for (UINT adapterIndex=0;adapterIndex<original->GetAdapterCount();adapterIndex++) 
	{
		D3DADAPTER_IDENTIFIER9  Identifier;
		original->GetAdapterIdentifier(Adapter,0,&Identifier);

		sprintf(buf, "Adapter[%d]: %s\n", adapterIndex, Identifier.Description); 
		OutputDebugStringA(buf);

		if (strstr(Identifier.Description,"PerfHUD") != 0)
		{
			Adapter = adapterIndex;
			DeviceType = D3DDEVTYPE_REF;

			OutputDebugStringA("got nvperhud\n!");
			break;
		}
	}

	DeviceType = D3DDEVTYPE_REF;

	sprintf(buf, "Adapter: %d\n", Adapter); 
	OutputDebugStringA(buf);

	sprintf(buf, "DeviceType: %d\n", DeviceType); 
	OutputDebugStringA(buf);

	s.ShowCallstack(0, 100);
	*/

	IDirect3DDevice9* orginalDevice = NULL;
	HRESULT hres = original->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, &orginalDevice);
	if (!FAILED(hres) && orginalDevice != NULL)
	{
		if (ppResult != NULL)
		{
			*ppResult = new ProxyIDirect3DDevice9(orginalDevice, Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters);
		}
	}
	else if (ppResult != NULL)
	{
		*ppResult = NULL;
	}
	
	return hres;
}
  
//
// Format configuration as JSON.
//
void ProxyIDirect3D9::FormatConfigAsJSON(jsonstream& output) const
{
	D3DFORMAT format = D3DFMT_X8R8G8B8;

	output	<< jsonstream::openObject 
			<< "name" << "adaptors"
			<< "value" << jsonstream::openArray;

	//
	// We are calling D3D functions that are logically const, but unfortunately not marked with the 'const' keyword.
	//
	IDirect3D9* d3d = const_cast<IDirect3D9*>(original); 

	for (unsigned int adaptorIndex = 0; adaptorIndex < d3d->GetAdapterCount(); ++adaptorIndex)
	{
		FormatAdaptorAsJSON(output, d3d, adaptorIndex, format);
	}

	output	<< jsonstream::closeArray			
			<< jsonstream::closeObject;
}

void ProxyIDirect3D9::FormatAdaptorAsJSON( jsonstream& output, IDirect3D9* d3d, unsigned int adaptorIndex, D3DFORMAT format ) const
{
    output  << jsonstream::openObject
            << "name" << adaptorIndex
            << "value";

	output << jsonstream::openArray;

	D3DADAPTER_IDENTIFIER9 adaptorId;
	if (FAILED(d3d->GetAdapterIdentifier(adaptorIndex, 0, &adaptorId)))
	{
		output << jsonstream::closeArray;
		return;
	}

	unsigned int numModes = d3d->GetAdapterModeCount(adaptorIndex, format);

	output	<< jsonstream::openObject
		<< "name" << "Description"
		<< "value" << adaptorId.Description
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "DeviceName"
		<< "value" << adaptorId.DeviceName
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "DriverVersion.LowPart"
		<< "value" << adaptorId.DriverVersion.LowPart
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "DriverVersion.HighPart"
		<< "value" << adaptorId.DriverVersion.HighPart
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "VendorId"
		<< "value" << adaptorId.VendorId
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "DeviceId"
		<< "value" << adaptorId.DeviceId
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "SubSysId"
		<< "value" << adaptorId.SubSysId
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "Revision"
		<< "value" << adaptorId.Revision
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "DeviceIdentifier"
		<< "value" << adaptorId.DeviceIdentifier
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "WHQLLevel"
		<< "value" << adaptorId.WHQLLevel
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "modes"
		<< "value" << jsonstream::openArray;

	for (unsigned int modeIndex = 0; modeIndex < numModes; ++modeIndex)
	{
		FormatModeAsJSON(output, d3d, adaptorIndex, format, modeIndex);
	}

	output	<< jsonstream::closeArray
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "caps"
		<< "value" << jsonstream::openArray;

	D3DDEVTYPE devTypes[] = { D3DDEVTYPE_HAL, D3DDEVTYPE_NULLREF, D3DDEVTYPE_REF, D3DDEVTYPE_SW  };

	for (unsigned int devTypeIndex = 0; devTypeIndex < (sizeof(devTypes) / sizeof(devTypes[0])); ++devTypeIndex)
	{
		FormatDeviceCapsAsJSON(devTypes[devTypeIndex], output, d3d, adaptorIndex);
	}

	output	<< jsonstream::closeArray
			<< jsonstream::closeObject
			<< jsonstream::closeArray
            << jsonstream::closeObject;
}

void ProxyIDirect3D9::FormatModeAsJSON(jsonstream& output, IDirect3D9* d3d, unsigned int adaptorIndex, D3DFORMAT format, unsigned int modeIndex) const
{
	D3DDISPLAYMODE displayMode;

	output	<< jsonstream::openArray;

	if (SUCCEEDED(d3d->EnumAdapterModes(adaptorIndex, format, modeIndex, &displayMode)))
	{
		output	<< jsonstream::openObject
				<< "name" << "Width"
				<< "value" << displayMode.Width
				<< jsonstream::closeObject
				<< jsonstream::openObject
				<< "name" << "Height"
				<< "value" << displayMode.Height
				<< jsonstream::closeObject
				<< jsonstream::openObject
				<< "name" << "RefreshRate"
				<< "value" << displayMode.RefreshRate
				<< jsonstream::closeObject
				<< jsonstream::openObject
				<< "name" << "Format"
				<< "value" << FormatToString(displayMode.Format)
				<< jsonstream::closeObject;
	}

	output << jsonstream::closeArray;
}

void ProxyIDirect3D9::FormatDeviceCapsAsJSON(D3DDEVTYPE devType, jsonstream& output, IDirect3D9* d3d, unsigned int adaptorIndex) const
{
	D3DCAPS9 caps;

	output	<< jsonstream::openObject
		<< "name" << DeviceTypeToString(devType)
		<< "value" << jsonstream::openArray;

	if (!FAILED(d3d->GetDeviceCaps(adaptorIndex, devType, &caps)))
	{
		FormatDeviceCapsDataAsJSON(output, caps);
	}	

	output	<< jsonstream::closeArray
		<< jsonstream::closeObject;
}

void ProxyIDirect3D9::FormatDeviceCapsDataAsJSON(jsonstream& output, D3DCAPS9 &caps) const
{
	output	<< jsonstream::openObject
		<< "name" << "AdapterOrdinal"
		<< "value" << caps.AdapterOrdinal
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "Caps"
		<< "value" << caps.Caps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "Caps2"
		<< "value" << caps.Caps2
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "Caps3"
		<< "value" << caps.Caps3
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "PresentationIntervals"
		<< "value" << caps.PresentationIntervals
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "CursorCaps"
		<< "value" << caps.CursorCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "DevCaps"
		<< "value" << caps.DevCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "PrimitiveMiscCaps"
		<< "value" << caps.PrimitiveMiscCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "RasterCaps"
		<< "value" << caps.RasterCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "ZCmpCaps"
		<< "value" << caps.ZCmpCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "SrcBlendCaps"
		<< "value" << caps.SrcBlendCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "DestBlendCaps"
		<< "value" << caps.DestBlendCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "AlphaCmpCaps"
		<< "value" << caps.AlphaCmpCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "ShadeCaps"
		<< "value" << caps.ShadeCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "TextureCaps"
		<< "value" << caps.TextureCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "TextureFilterCaps"
		<< "value" << caps.TextureFilterCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "CubeTextureFilterCaps"
		<< "value" << caps.CubeTextureFilterCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "VolumeTextureFilterCaps"
		<< "value" << caps.VolumeTextureFilterCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "TextureAddressCaps"
		<< "value" << caps.TextureAddressCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "VolumeTextureAddressCaps"
		<< "value" << caps.VolumeTextureAddressCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "LineCaps"
		<< "value" << caps.LineCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxTextureWidth"
		<< "value" << caps.MaxTextureWidth
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxTextureHeight"
		<< "value" << caps.MaxTextureHeight
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxVolumeExtent"
		<< "value" << caps.MaxVolumeExtent
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxTextureRepeat"
		<< "value" << caps.MaxTextureRepeat
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxTextureAspectRatio"
		<< "value" << caps.MaxTextureAspectRatio
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxAnisotropy"
		<< "value" << caps.MaxAnisotropy
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxVertexW"
		<< "value" << caps.MaxVertexW
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "GuardBandLeft"
		<< "value" << caps.GuardBandLeft
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "GuardBandTop"
		<< "value" << caps.GuardBandTop
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "GuardBandRight"
		<< "value" << caps.GuardBandRight
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "GuardBandBottom"
		<< "value" << caps.GuardBandBottom
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "ExtentsAdjust"
		<< "value" << caps.ExtentsAdjust
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "StencilCaps"
		<< "value" << caps.StencilCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "FVFCaps"
		<< "value" << caps.FVFCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "TextureOpCaps"
		<< "value" << caps.TextureOpCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxTextureBlendStages"
		<< "value" << caps.MaxTextureBlendStages
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxSimultaneousTextures"
		<< "value" << caps.MaxSimultaneousTextures
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "VertexProcessingCaps"
		<< "value" << caps.VertexProcessingCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxActiveLights"
		<< "value" << caps.MaxActiveLights
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxUserClipPlanes"
		<< "value" << caps.MaxUserClipPlanes
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxVertexBlendMatrices"
		<< "value" << caps.MaxVertexBlendMatrices
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxVertexBlendMatrixIndex"
		<< "value" << caps.MaxVertexBlendMatrixIndex
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxPointSize"
		<< "value" << caps.MaxPointSize
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxPrimitiveCount"
		<< "value" << caps.MaxPrimitiveCount
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxVertexIndex"
		<< "value" << caps.MaxVertexIndex
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxStreams"
		<< "value" << caps.MaxStreams
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxStreamStride"
		<< "value" << caps.MaxStreamStride
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "VertexShaderVersion"
		<< "value" << caps.VertexShaderVersion
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxVertexShaderConst"
		<< "value" << caps.MaxVertexShaderConst
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "PixelShaderVersion"
		<< "value" << caps.PixelShaderVersion
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "PixelShader1xMaxValue"
		<< "value" << caps.PixelShader1xMaxValue
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "DevCaps2"
		<< "value" << caps.DevCaps2
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MasterAdapterOrdinal"
		<< "value" << caps.MasterAdapterOrdinal
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "AdapterOrdinalInGroup"
		<< "value" << caps.AdapterOrdinalInGroup
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "NumberOfAdaptersInGroup"
		<< "value" << caps.NumberOfAdaptersInGroup
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "DeclTypes"
		<< "value" << caps.DeclTypes
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "NumSimultaneousRTs"
		<< "value" << caps.NumSimultaneousRTs
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "StretchRectFilterCaps"
		<< "value" << caps.StretchRectFilterCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "VS20Caps.Caps"
		<< "value" << caps.VS20Caps.Caps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "VS20Caps.DynamicFlowControlDepth"
		<< "value" << caps.VS20Caps.DynamicFlowControlDepth
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "VS20Caps.NumTemps"
		<< "value" << caps.VS20Caps.NumTemps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "VS20Caps.StaticFlowControlDepth"
		<< "value" << caps.VS20Caps.StaticFlowControlDepth
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "PS20Caps.Caps"
		<< "value" << caps.PS20Caps.Caps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "PS20Caps.DynamicFlowControlDepth"
		<< "value" << caps.PS20Caps.DynamicFlowControlDepth
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "PS20Caps.NumTemps"
		<< "value" << caps.PS20Caps.NumTemps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "PS20Caps.StaticFlowControlDepth"
		<< "value" << caps.PS20Caps.StaticFlowControlDepth
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "PS20Caps.NumInstructionSlots"
		<< "value" << caps.PS20Caps.NumInstructionSlots
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "VertexTextureFilterCaps"
		<< "value" << caps.VertexTextureFilterCaps
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxVShaderInstructionsExecuted"
		<< "value" << caps.MaxVShaderInstructionsExecuted
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxPShaderInstructionsExecuted"
		<< "value" << caps.MaxPShaderInstructionsExecuted
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxVertexShader30InstructionSlots"
		<< "value" << caps.MaxVertexShader30InstructionSlots
		<< jsonstream::closeObject
		<< jsonstream::openObject
		<< "name" << "MaxPixelShader30InstructionSlots"
		<< "value" << caps.MaxPixelShader30InstructionSlots
		<< jsonstream::closeObject;
}
