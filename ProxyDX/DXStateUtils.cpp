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
#include "DXStateUtils.h"

#include <sstream>

using std::stringstream;
using std::string;

const char* DeviceTypeToString(D3DDEVTYPE deviceType)
{
	switch (deviceType)
	{
	case D3DDEVTYPE_HAL:		return "D3DDEVTYPE_HAL";
	case D3DDEVTYPE_NULLREF:	return "D3DDEVTYPE_NULLREF";
	case D3DDEVTYPE_REF:		return "D3DDEVTYPE_REF";
	case D3DDEVTYPE_SW:			return "D3DDEVTYPE_SW";
	default:					return "unknown";
	}
}

const char* FormatToString(D3DFORMAT format) 
{
	if (format == D3DFMT_UNKNOWN) return "D3DFMT_UNKNOWN";
	else if (format == D3DFMT_R8G8B8) return "D3DFMT_R8G8B8";
	else if (format == D3DFMT_A8R8G8B8) return "D3DFMT_A8R8G8B8";
	else if (format == D3DFMT_X8R8G8B8) return "D3DFMT_X8R8G8B8";
	else if (format == D3DFMT_R5G6B5) return "D3DFMT_R5G6B5";
	else if (format == D3DFMT_X1R5G5B5) return "D3DFMT_X1R5G5B5";
	else if (format == D3DFMT_A1R5G5B5) return "D3DFMT_A1R5G5B5";
	else if (format == D3DFMT_A4R4G4B4) return "D3DFMT_A4R4G4B4";
	else if (format == D3DFMT_R3G3B2) return "D3DFMT_R3G3B2";
	else if (format == D3DFMT_A8) return "D3DFMT_A8";
	else if (format == D3DFMT_A8R3G3B2) return "D3DFMT_A8R3G3B2";
	else if (format == D3DFMT_X4R4G4B4) return "D3DFMT_X4R4G4B4";
	else if (format == D3DFMT_A2B10G10R10) return "D3DFMT_A2B10G10R10";
	else if (format == D3DFMT_A8B8G8R8) return "D3DFMT_A8B8G8R8";
	else if (format == D3DFMT_X8B8G8R8) return "D3DFMT_X8B8G8R8";
	else if (format == D3DFMT_G16R16) return "D3DFMT_G16R16";
	else if (format == D3DFMT_A2R10G10B10) return "D3DFMT_A2R10G10B10";
	else if (format == D3DFMT_A16B16G16R16) return "D3DFMT_A16B16G16R16";
	else if (format == D3DFMT_A8P8) return "D3DFMT_A8P8";
	else if (format == D3DFMT_P8) return "D3DFMT_P8";
	else if (format == D3DFMT_L8) return "D3DFMT_L8";
	else if (format == D3DFMT_A8L8) return "D3DFMT_A8L8";
	else if (format == D3DFMT_A4L4) return "D3DFMT_A4L4";
	else if (format == D3DFMT_V8U8) return "D3DFMT_V8U8";
	else if (format == D3DFMT_L6V5U5) return "D3DFMT_L6V5U5";
	else if (format == D3DFMT_X8L8V8U8) return "D3DFMT_X8L8V8U8";
	else if (format == D3DFMT_Q8W8V8U8) return "D3DFMT_Q8W8V8U8";
	else if (format == D3DFMT_V16U16) return "D3DFMT_V16U16";
	else if (format == D3DFMT_A2W10V10U10) return "D3DFMT_A2W10V10U10";
	else if (format == D3DFMT_UYVY) return "D3DFMT_UYVY";
	else if (format == D3DFMT_R8G8_B8G8) return "D3DFMT_R8G8_B8G8";
	else if (format == D3DFMT_YUY2) return "D3DFMT_YUY2";
	else if (format == D3DFMT_G8R8_G8B8) return "D3DFMT_G8R8_G8B8";
	else if (format == D3DFMT_DXT1) return "D3DFMT_DXT1";
	else if (format == D3DFMT_DXT2) return "D3DFMT_DXT2";
	else if (format == D3DFMT_DXT3) return "D3DFMT_DXT3";
	else if (format == D3DFMT_DXT4) return "D3DFMT_DXT4";
	else if (format == D3DFMT_DXT5) return "D3DFMT_DXT5";
	else if (format == D3DFMT_D16_LOCKABLE) return "D3DFMT_D16_LOCKABLE";
	else if (format == D3DFMT_D32) return "D3DFMT_D32";
	else if (format == D3DFMT_D15S1) return "D3DFMT_D15S1";
	else if (format == D3DFMT_D24S8) return "D3DFMT_D24S8";
	else if (format == D3DFMT_D24X8) return "D3DFMT_D24X8";
	else if (format == D3DFMT_D24X4S4) return "D3DFMT_D24X4S4";
	else if (format == D3DFMT_D16) return "D3DFMT_D16";
	else if (format == D3DFMT_D32F_LOCKABLE) return "D3DFMT_D32F_LOCKABLE";
	else if (format == D3DFMT_D24FS8) return "D3DFMT_D24FS8";
	else if (format == D3DFMT_D32_LOCKABLE) return "D3DFMT_D32_LOCKABLE";
	else if (format == D3DFMT_S8_LOCKABLE) return "D3DFMT_S8_LOCKABLE";
	else if (format == D3DFMT_L16) return "D3DFMT_L16";
	else if (format == D3DFMT_VERTEXDATA) return "D3DFMT_VERTEXDATA";
	else if (format == D3DFMT_INDEX16) return "D3DFMT_INDEX16";
	else if (format == D3DFMT_INDEX32) return "D3DFMT_INDEX32";
	else if (format == D3DFMT_Q16W16V16U16) return "D3DFMT_Q16W16V16U16";
	else if (format == D3DFMT_MULTI2_ARGB8) return "D3DFMT_MULTI2_ARGB8";
	else if (format == D3DFMT_R16F) return "D3DFMT_R16F";
	else if (format == D3DFMT_G16R16F) return "D3DFMT_G16R16F";
	else if (format == D3DFMT_A16B16G16R16F) return "D3DFMT_A16B16G16R16F";
	else if (format == D3DFMT_R32F) return "D3DFMT_R32F";
	else if (format == D3DFMT_G32R32F) return "D3DFMT_G32R32F";
	else if (format == D3DFMT_A32B32G32R32F) return "D3DFMT_A32B32G32R32F";
	else if (format == D3DFMT_CxV8U8) return "D3DFMT_CxV8U8";
	else if (format == D3DFMT_A1) return "D3DFMT_A1";
	else if (format == D3DFMT_A2B10G10R10_XR_BIAS) return "D3DFMT_A2B10G10R10_XR_BIAS";
	else if (format == D3DFMT_BINARYBUFFER) return "D3DFMT_BINARYBUFFER";
	else return "invalid";
}

const char* MultiSampleTypeToString(D3DMULTISAMPLE_TYPE type)
{
	if (type == D3DMULTISAMPLE_NONE) return "D3DMULTISAMPLE_NONE";
	else if (type == D3DMULTISAMPLE_NONMASKABLE) return "D3DMULTISAMPLE_NONMASKABLE";
	else if (type == D3DMULTISAMPLE_2_SAMPLES) return "D3DMULTISAMPLE_2_SAMPLES";
	else if (type == D3DMULTISAMPLE_3_SAMPLES) return "D3DMULTISAMPLE_3_SAMPLES";
	else if (type == D3DMULTISAMPLE_4_SAMPLES) return "D3DMULTISAMPLE_4_SAMPLES";
	else if (type == D3DMULTISAMPLE_5_SAMPLES) return "D3DMULTISAMPLE_5_SAMPLES";
	else if (type == D3DMULTISAMPLE_6_SAMPLES) return "D3DMULTISAMPLE_6_SAMPLES";
	else if (type == D3DMULTISAMPLE_7_SAMPLES) return "D3DMULTISAMPLE_7_SAMPLES";
	else if (type == D3DMULTISAMPLE_8_SAMPLES) return "D3DMULTISAMPLE_8_SAMPLES";
	else if (type == D3DMULTISAMPLE_9_SAMPLES) return "D3DMULTISAMPLE_9_SAMPLES";
	else if (type == D3DMULTISAMPLE_10_SAMPLES) return "D3DMULTISAMPLE_10_SAMPLES";
	else if (type == D3DMULTISAMPLE_11_SAMPLES) return "D3DMULTISAMPLE_11_SAMPLES";
	else if (type == D3DMULTISAMPLE_12_SAMPLES) return "D3DMULTISAMPLE_12_SAMPLES";
	else if (type == D3DMULTISAMPLE_13_SAMPLES) return "D3DMULTISAMPLE_13_SAMPLES";
	else if (type == D3DMULTISAMPLE_14_SAMPLES) return "D3DMULTISAMPLE_14_SAMPLES";
	else if (type == D3DMULTISAMPLE_15_SAMPLES) return "D3DMULTISAMPLE_15_SAMPLES";
	else if (type == D3DMULTISAMPLE_16_SAMPLES) return "D3DMULTISAMPLE_16_SAMPLES";
	else return "invalid";
}

const char* SwapEffectToString(D3DSWAPEFFECT swapEffect)
{
	if (swapEffect == D3DSWAPEFFECT_DISCARD) return "D3DSWAPEFFECT_DISCARD";
	else if (swapEffect == D3DSWAPEFFECT_FLIP) return "D3DSWAPEFFECT_FLIP";
	else if (swapEffect == D3DSWAPEFFECT_COPY) return "D3DSWAPEFFECT_COPY";
	else if (swapEffect == D3DSWAPEFFECT_OVERLAY) return "D3DSWAPEFFECT_OVERLAY";
	else if (swapEffect == D3DSWAPEFFECT_FLIPEX) return "D3DSWAPEFFECT_FLIPEX";
	else return "invalid";
}

string PresentFlagsToString(DWORD flags)
{
	stringstream output;

	bool firstOne = true;

	if ((flags & D3DPRESENTFLAG_DEVICECLIP) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_DEVICECLIP";
	}

	if ((flags & D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL";
	}

	if ((flags & D3DPRESENTFLAG_LOCKABLE_BACKBUFFER) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_LOCKABLE_BACKBUFFER";
	}

	if ((flags & D3DPRESENTFLAG_NOAUTOROTATE) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_NOAUTOROTATE";
	}

	if ((flags & D3DPRESENTFLAG_UNPRUNEDMODE) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_UNPRUNEDMODE";
	}

	if ((flags & D3DPRESENTFLAG_VIDEO) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_VIDEO";
	}

	if ((flags & D3DPRESENTFLAG_OVERLAY_LIMITEDRGB) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_OVERLAY_LIMITEDRGB";
	}

	if ((flags & D3DPRESENTFLAG_OVERLAY_YCbCr_BT709) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_OVERLAY_YCbCr_BT709";
	}

	if ((flags & D3DPRESENTFLAG_OVERLAY_YCbCr_xvYCC) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_OVERLAY_YCbCr_xvYCC";
	}

	if ((flags & D3DPRESENTFLAG_RESTRICTED_CONTENT) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_RESTRICTED_CONTENT";
	}

	if ((flags & D3DPRESENTFLAG_RESTRICT_SHARED_RESOURCE_DRIVER) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}
		output << "D3DPRESENTFLAG_RESTRICT_SHARED_RESOURCE_DRIVER";
	}

	return output.str();
}

string BehaviourFlagsToString(DWORD flags)
{
	stringstream output;

	bool firstOne = true;

	if ((flags & D3DCREATE_ADAPTERGROUP_DEVICE) != 0)
	{
		firstOne = false;
		output << "D3DCREATE_ADAPTERGROUP_DEVICE";
	}

	if ((flags & D3DCREATE_DISABLE_DRIVER_MANAGEMENT) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_DISABLE_DRIVER_MANAGEMENT";
	}

	if ((flags & D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_DISABLE_DRIVER_MANAGEMENT_EX";
	}

	if ((flags & D3DCREATE_DISABLE_PRINTSCREEN) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_DISABLE_PRINTSCREEN";
	}

	if ((flags & D3DCREATE_DISABLE_PSGP_THREADING) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_DISABLE_PSGP_THREADING";
	}

	if ((flags & D3DCREATE_ENABLE_PRESENTSTATS) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_ENABLE_PRESENTSTATS";
	}

	if ((flags & D3DCREATE_FPU_PRESERVE) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_FPU_PRESERVE";
	}

	if ((flags & D3DCREATE_HARDWARE_VERTEXPROCESSING) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_HARDWARE_VERTEXPROCESSING";
	}

	if ((flags & D3DCREATE_MIXED_VERTEXPROCESSING) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_MIXED_VERTEXPROCESSING";
	}

	if ((flags & D3DCREATE_MULTITHREADED) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_MULTITHREADED";
	}

	if ((flags & D3DCREATE_NOWINDOWCHANGES) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_NOWINDOWCHANGES";
	}

	if ((flags & D3DCREATE_PUREDEVICE) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_PUREDEVICE";
	}

	if ((flags & D3DCREATE_SCREENSAVER) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_SCREENSAVER";
	}

	if ((flags & D3DCREATE_SOFTWARE_VERTEXPROCESSING) != 0)
	{
		if (firstOne)
		{
			firstOne = false;
		}
		else
		{
			output << ", ";
		}

		output << "D3DCREATE_SOFTWARE_VERTEXPROCESSING";
	}

	return output.str();
}

const char* ParseZBufferType(DWORD value) //todo: these aren't really parsing functions!
{
	switch (value)
	{
	case D3DZB_FALSE:	return "D3DZB_FALSE";
	case D3DZB_TRUE:	return "D3DZB_TRUE";
	case D3DZB_USEW:	return "D3DZB_USEW";
	}

	return "unknown";	
}

const char* ParseFillMode(DWORD value)
{
	switch (value)
	{
	case D3DFILL_POINT:		return "D3DFILL_POINT";
	case D3DFILL_WIREFRAME: return "D3DFILL_WIREFRAME";
	case D3DFILL_SOLID:		return "D3DFILL_SOLID";
	}

	return "unknown";	
}

const char* ParseShadeMode(DWORD value)
{
	switch (value)
	{
	case D3DSHADE_FLAT:		return "D3DSHADE_FLAT";
	case D3DSHADE_GOURAUD:	return "D3DSHADE_GOURAUD";
	case D3DSHADE_PHONG:	return "D3DSHADE_PHONG";
	}

	return "unknown";	
}

const char* ParseBoolean(DWORD value)
{
	switch (value)
	{
	case TRUE:		return "TRUE";
	case FALSE:		return "FALSE";
	}

	return "unknown";	
}

const char* ParseBlendMode(DWORD value)
{
	switch (value)
	{
	case D3DBLEND_ZERO: return "D3DBLEND_ZERO";
	case D3DBLEND_ONE: return "D3DBLEND_ONE";
	case D3DBLEND_SRCCOLOR: return "D3DBLEND_SRCCOLOR";
	case D3DBLEND_INVSRCCOLOR: return "D3DBLEND_INVSRCCOLOR";
	case D3DBLEND_SRCALPHA: return "D3DBLEND_SRCALPHA";
	case D3DBLEND_INVSRCALPHA: return "D3DBLEND_INVSRCALPHA";
	case D3DBLEND_DESTALPHA: return "D3DBLEND_DESTALPHA";
	case D3DBLEND_INVDESTALPHA: return "D3DBLEND_INVDESTALPHA";
	case D3DBLEND_DESTCOLOR: return "D3DBLEND_DESTCOLOR";
	case D3DBLEND_INVDESTCOLOR: return "D3DBLEND_INVDESTCOLOR";
	case D3DBLEND_SRCALPHASAT: return "D3DBLEND_SRCALPHASAT";
	case D3DBLEND_BOTHSRCALPHA: return "D3DBLEND_BOTHSRCALPHA";
	case D3DBLEND_BOTHINVSRCALPHA: return "D3DBLEND_BOTHINVSRCALPHA";
	case D3DBLEND_BLENDFACTOR: return "D3DBLEND_BLENDFACTOR";
	case D3DBLEND_INVBLENDFACTOR: return "D3DBLEND_INVBLENDFACTOR";
	case D3DBLEND_SRCCOLOR2: return "D3DBLEND_SRCCOLOR2";
	case D3DBLEND_INVSRCCOLOR2: return "D3DBLEND_INVSRCCOLOR2";
	}

	return "unknown";	
}

const char* ParseCullMode(DWORD value)
{
	switch (value)
	{
	case D3DCULL_NONE: return "D3DCULL_NONE";
	case D3DCULL_CW: return "D3DCULL_CW";
	case D3DCULL_CCW: return "D3DCULL_CCW";
	}

	return "unknown";	
}

const char* ParseCmpFunc(DWORD value)
{
	switch (value)
	{
	case D3DCMP_NEVER: return "D3DCMP_NEVER";
	case D3DCMP_LESS: return "D3DCMP_LESS";
	case D3DCMP_EQUAL: return "D3DCMP_EQUAL";
	case D3DCMP_LESSEQUAL: return "D3DCMP_LESSEQUAL";
	case D3DCMP_GREATER: return "D3DCMP_GREATER";
	case D3DCMP_NOTEQUAL: return "D3DCMP_NOTEQUAL";
	case D3DCMP_GREATEREQUAL: return "D3DCMP_GREATEREQUAL";
	case D3DCMP_ALWAYS: return "D3DCMP_ALWAYS";
	}

	return "unknown";	
}

const char* ParseDWORD(DWORD value)
{
	static char buf[256];
	return itoa(value, buf, 10);
}

const char* ParseHex(DWORD value)
{
	static char buf[256];
	return itoa(value, buf, 16);
}

const char* ParseFloat(DWORD value)
{
	static char buf[256];
	float* f = (float*)&value;
	sprintf(buf, "%f", *f);
	return buf;
}

const char* ParseColor(DWORD value)
{
	static char buf[256];
	return itoa(value, buf, 16);
}

const char* ParseFogMode(DWORD value)
{
	switch (value)
	{
	case D3DFOG_NONE: return "D3DFOG_NONE";
	case D3DFOG_EXP: return "D3DFOG_EXP";
	case D3DFOG_EXP2: return "D3DFOG_EXP2";
	case D3DFOG_LINEAR: return "D3DFOG_LINEAR";
	}

	return "unknown";	
}

const char* ParseStencilOp(DWORD value)
{
	switch (value)
	{
	case D3DSTENCILOP_KEEP: return "D3DSTENCILOP_KEEP";
	case D3DSTENCILOP_ZERO: return "D3DSTENCILOP_ZERO";
	case D3DSTENCILOP_REPLACE: return "D3DSTENCILOP_REPLACE";
	case D3DSTENCILOP_INCRSAT: return "D3DSTENCILOP_INCRSAT";
	case D3DSTENCILOP_DECRSAT: return "D3DSTENCILOP_DECRSAT";
	case D3DSTENCILOP_INVERT: return "D3DSTENCILOP_INVERT";
	case D3DSTENCILOP_INCR: return "D3DSTENCILOP_INCR";
	case D3DSTENCILOP_DECR: return "D3DSTENCILOP_DECR";
	}

	return "unknown";	
}

const char* ParseTextureWrapFlags(DWORD value)
{
	static char buf[1024];
	if (value == 0)
	{
		"none";
	}

	strcpy(buf, "");

	bool gotFlags = false;

	if ((value & D3DWRAPCOORD_0) != 0)
	{
		strcat(buf, "D3DWRAPCOORD_0");
		gotFlags = true;
	}

	if ((value & D3DWRAPCOORD_1) != 0)
	{
		if (gotFlags)
		{
			strcat(buf, " | ");
		}
		strcat(buf, "D3DWRAPCOORD_1");
		gotFlags = true;
	}

	if ((value & D3DWRAPCOORD_2) != 0)
	{
		if (gotFlags)
		{
			strcat(buf, " | ");
		}
		strcat(buf, "D3DWRAPCOORD_2");
		gotFlags = true;
	}

	if ((value & D3DWRAPCOORD_3) != 0)
	{
		if (gotFlags)
		{
			strcat(buf, " | ");
		}
		strcat(buf, "D3DWRAPCOORD_3");
		gotFlags = true;
	}

	return buf;
}

const char* ParseMaterialSource(DWORD value)
{
	switch (value)
	{
	case D3DMCS_MATERIAL: return "D3DMCS_MATERIAL";
	case D3DMCS_COLOR1: return "D3DMCS_COLOR1";
	case D3DMCS_COLOR2: return "D3DMCS_COLOR2";
	}

	return "unknown";	
}

const char* ParseVertexBlend(DWORD value)
{
	switch (value)
	{
	case D3DVBF_DISABLE: return "D3DVBF_DISABLE";
	case D3DVBF_1WEIGHTS: return "D3DVBF_1WEIGHTS";
	case D3DVBF_2WEIGHTS: return "D3DVBF_2WEIGHTS";
	case D3DVBF_3WEIGHTS: return "D3DVBF_3WEIGHTS";
	case D3DVBF_TWEENING: return "D3DVBF_TWEENING";
	case D3DVBF_0WEIGHTS: return "D3DVBF_0WEIGHTS";
	}

	return "unknown";	
}

const char* ParsePatchEdge(DWORD value)
{
	switch (value)
	{
	case D3DPATCHEDGE_DISCRETE: return "D3DPATCHEDGE_DISCRETE";
	case D3DPATCHEDGE_CONTINUOUS: return "D3DPATCHEDGE_CONTINUOUS";
	}

	return "unknown";	
}

const char* ParseDebugMonitor(DWORD value)
{
	switch (value)
	{
	case D3DDMT_ENABLE: return "D3DDMT_ENABLE";
	case D3DDMT_DISABLE: return "D3DDMT_DISABLE";
	}

	return "unknown";	
}

const char* ParseBlendOp(DWORD value)
{
	switch (value)
	{
	case D3DBLENDOP_ADD: return "D3DBLENDOP_ADD";
	case D3DBLENDOP_SUBTRACT: return "D3DBLENDOP_SUBTRACT";
	case D3DBLENDOP_REVSUBTRACT: return "D3DBLENDOP_REVSUBTRACT";
	case D3DBLENDOP_MIN: return "D3DBLENDOP_MIN";
	case D3DBLENDOP_MAX: return "D3DBLENDOP_MAX";
	}

	return "unknown";	
}

const char* ParsePositionDegree(DWORD value)
{
	switch (value)
	{
	case D3DDEGREE_LINEAR: return "D3DDEGREE_LINEAR";
	case D3DDEGREE_QUADRATIC: return "D3DDEGREE_QUADRATIC";
	case D3DDEGREE_CUBIC: return "D3DDEGREE_CUBIC";
	case D3DDEGREE_QUINTIC: return "D3DDEGREE_QUINTIC";
	}

	return "unknown";	
}

//
// Data for each render state.
//
const RenderStateData renderStateData[] =
{
	{ D3DRS_ZENABLE, "D3DRS_ZENABLE", ParseZBufferType },
	{ D3DRS_FILLMODE, "D3DRS_FILLMODE", ParseFillMode },
	{ D3DRS_SHADEMODE, "D3DRS_SHADEMODE", ParseShadeMode },
	{ D3DRS_ZWRITEENABLE, "D3DRS_ZWRITEENABLE", ParseBoolean },
	{ D3DRS_ALPHATESTENABLE, "D3DRS_ALPHATESTENABLE", ParseBoolean },
	{ D3DRS_LASTPIXEL, "D3DRS_LASTPIXEL", ParseBoolean },
	{ D3DRS_SRCBLEND, "D3DRS_SRCBLEND", ParseBlendMode },
	{ D3DRS_DESTBLEND, "D3DRS_DESTBLEND", ParseBlendMode },
	{ D3DRS_CULLMODE, "D3DRS_CULLMODE", ParseCullMode },
	{ D3DRS_ZFUNC, "D3DRS_ZFUNC", ParseCmpFunc },
	{ D3DRS_ALPHAREF, "D3DRS_ALPHAREF", ParseDWORD },
	{ D3DRS_ALPHAFUNC, "D3DRS_ALPHAFUNC", ParseCmpFunc },
	{ D3DRS_DITHERENABLE, "D3DRS_DITHERENABLE", ParseBoolean },
	{ D3DRS_ALPHABLENDENABLE, "D3DRS_ALPHABLENDENABLE", ParseBoolean },
	{ D3DRS_FOGENABLE, "D3DRS_FOGENABLE", ParseBoolean },
	{ D3DRS_SPECULARENABLE, "D3DRS_SPECULARENABLE", ParseBoolean },
	{ D3DRS_FOGCOLOR, "D3DRS_FOGCOLOR", ParseColor },
	{ D3DRS_FOGTABLEMODE, "D3DRS_FOGTABLEMODE", ParseFogMode },
	{ D3DRS_FOGSTART, "D3DRS_FOGSTART", ParseFloat },
	{ D3DRS_FOGEND, "D3DRS_FOGEND", ParseFloat },
	{ D3DRS_FOGDENSITY, "D3DRS_FOGDENSITY", ParseFloat },
	{ D3DRS_RANGEFOGENABLE, "D3DRS_RANGEFOGENABLE", ParseBoolean },
	{ D3DRS_STENCILENABLE, "D3DRS_STENCILENABLE", ParseBoolean },
	{ D3DRS_STENCILFAIL, "D3DRS_STENCILFAIL", ParseStencilOp },
	{ D3DRS_STENCILZFAIL, "D3DRS_STENCILZFAIL", ParseStencilOp },
	{ D3DRS_STENCILPASS, "D3DRS_STENCILPASS", ParseStencilOp },
	{ D3DRS_STENCILFUNC, "D3DRS_STENCILFUNC", ParseCmpFunc },
	{ D3DRS_STENCILREF, "D3DRS_STENCILREF", ParseDWORD },
	{ D3DRS_STENCILMASK, "D3DRS_STENCILMASK", ParseHex },
	{ D3DRS_STENCILWRITEMASK, "D3DRS_STENCILWRITEMASK", ParseHex },
	{ D3DRS_TEXTUREFACTOR, "D3DRS_TEXTUREFACTOR", ParseColor },
	{ D3DRS_WRAP0, "D3DRS_WRAP0", ParseTextureWrapFlags },
	{ D3DRS_WRAP1, "D3DRS_WRAP1", ParseTextureWrapFlags },
	{ D3DRS_WRAP2, "D3DRS_WRAP2", ParseTextureWrapFlags },
	{ D3DRS_WRAP3, "D3DRS_WRAP3", ParseTextureWrapFlags },
	{ D3DRS_WRAP4, "D3DRS_WRAP4", ParseTextureWrapFlags },
	{ D3DRS_WRAP5, "D3DRS_WRAP5", ParseTextureWrapFlags },
	{ D3DRS_WRAP6, "D3DRS_WRAP6", ParseTextureWrapFlags },
	{ D3DRS_WRAP7, "D3DRS_WRAP7", ParseTextureWrapFlags },
	{ D3DRS_CLIPPING, "D3DRS_CLIPPING", ParseBoolean },
	{ D3DRS_LIGHTING, "D3DRS_LIGHTING", ParseBoolean },
	{ D3DRS_AMBIENT, "D3DRS_AMBIENT", ParseColor },
	{ D3DRS_FOGVERTEXMODE, "D3DRS_FOGVERTEXMODE", ParseFogMode },
	{ D3DRS_COLORVERTEX, "D3DRS_COLORVERTEX", ParseBoolean },
	{ D3DRS_LOCALVIEWER, "D3DRS_LOCALVIEWER", ParseBoolean },
	{ D3DRS_NORMALIZENORMALS, "D3DRS_NORMALIZENORMALS", ParseBoolean },
	{ D3DRS_DIFFUSEMATERIALSOURCE, "D3DRS_DIFFUSEMATERIALSOURCE", ParseMaterialSource },
	{ D3DRS_SPECULARMATERIALSOURCE, "D3DRS_SPECULARMATERIALSOURCE", ParseMaterialSource },
	{ D3DRS_AMBIENTMATERIALSOURCE, "D3DRS_AMBIENTMATERIALSOURCE", ParseMaterialSource },
	{ D3DRS_EMISSIVEMATERIALSOURCE, "D3DRS_EMISSIVEMATERIALSOURCE", ParseMaterialSource },
	{ D3DRS_VERTEXBLEND, "D3DRS_VERTEXBLEND", ParseVertexBlend },
	{ D3DRS_CLIPPLANEENABLE, "D3DRS_CLIPPLANEENABLE", ParseHex },
	{ D3DRS_POINTSIZE, "D3DRS_POINTSIZE", ParseFloat },
	{ D3DRS_POINTSIZE_MIN, "D3DRS_POINTSIZE_MIN", ParseFloat },
	{ D3DRS_POINTSPRITEENABLE, "D3DRS_POINTSPRITEENABLE", ParseBoolean },
	{ D3DRS_POINTSCALEENABLE, "D3DRS_POINTSCALEENABLE", ParseBoolean },
	{ D3DRS_POINTSCALE_A, "D3DRS_POINTSCALE_A", ParseFloat },
	{ D3DRS_POINTSCALE_B, "D3DRS_POINTSCALE_B", ParseFloat },
	{ D3DRS_POINTSCALE_C, "D3DRS_POINTSCALE_C", ParseFloat },
	{ D3DRS_MULTISAMPLEANTIALIAS, "D3DRS_MULTISAMPLEANTIALIAS", ParseBoolean },
	{ D3DRS_MULTISAMPLEMASK, "D3DRS_MULTISAMPLEMASK", ParseHex },
	{ D3DRS_PATCHEDGESTYLE, "D3DRS_PATCHEDGESTYLE", ParsePatchEdge },
	{ D3DRS_DEBUGMONITORTOKEN, "D3DRS_DEBUGMONITORTOKEN", ParseDebugMonitor },
	{ D3DRS_POINTSIZE_MAX, "D3DRS_POINTSIZE_MAX", ParseFloat },
	{ D3DRS_INDEXEDVERTEXBLENDENABLE, "D3DRS_INDEXEDVERTEXBLENDENABLE", ParseBoolean },
	{ D3DRS_COLORWRITEENABLE, "D3DRS_COLORWRITEENABLE", ParseHex },
	{ D3DRS_TWEENFACTOR, "D3DRS_TWEENFACTOR", ParseFloat },
	{ D3DRS_BLENDOP, "D3DRS_BLENDOP", ParseBlendOp },
	{ D3DRS_POSITIONDEGREE, "D3DRS_POSITIONDEGREE", ParsePositionDegree },
	{ D3DRS_NORMALDEGREE, "D3DRS_NORMALDEGREE", ParsePositionDegree },
	{ D3DRS_SCISSORTESTENABLE, "D3DRS_SCISSORTESTENABLE", ParseBoolean },
	{ D3DRS_SLOPESCALEDEPTHBIAS, "D3DRS_SLOPESCALEDEPTHBIAS", ParseDWORD },
	{ D3DRS_ANTIALIASEDLINEENABLE, "D3DRS_ANTIALIASEDLINEENABLE", ParseBoolean	},
	{ D3DRS_MINTESSELLATIONLEVEL, "D3DRS_MINTESSELLATIONLEVEL", ParseFloat },
	{ D3DRS_MAXTESSELLATIONLEVEL, "D3DRS_MAXTESSELLATIONLEVEL", ParseFloat },
	{ D3DRS_ADAPTIVETESS_X, "D3DRS_ADAPTIVETESS_X", ParseFloat },
	{ D3DRS_ADAPTIVETESS_Y, "D3DRS_ADAPTIVETESS_Y", ParseFloat },
	{ D3DRS_ADAPTIVETESS_Z, "D3DRS_ADAPTIVETESS_Z", ParseFloat },
	{ D3DRS_ADAPTIVETESS_W, "D3DRS_ADAPTIVETESS_W", ParseFloat },
	{ D3DRS_ENABLEADAPTIVETESSELLATION, "D3DRS_ENABLEADAPTIVETESSELLATION", ParseBoolean },
	{ D3DRS_TWOSIDEDSTENCILMODE, "D3DRS_TWOSIDEDSTENCILMODE", ParseBoolean },
	{ D3DRS_CCW_STENCILFAIL, "D3DRS_CCW_STENCILFAIL", ParseStencilOp },
	{ D3DRS_CCW_STENCILZFAIL, "D3DRS_CCW_STENCILZFAIL", ParseStencilOp },
	{ D3DRS_CCW_STENCILPASS, "D3DRS_CCW_STENCILPASS", ParseStencilOp },
	{ D3DRS_CCW_STENCILFUNC, "D3DRS_CCW_STENCILFUNC", ParseCmpFunc },
	{ D3DRS_COLORWRITEENABLE1, "D3DRS_COLORWRITEENABLE1", ParseHex },
	{ D3DRS_COLORWRITEENABLE2, "D3DRS_COLORWRITEENABLE2", ParseHex },
	{ D3DRS_COLORWRITEENABLE3, "D3DRS_COLORWRITEENABLE3", ParseHex },
	{ D3DRS_BLENDFACTOR, "D3DRS_BLENDFACTOR", ParseColor },
	{ D3DRS_SRGBWRITEENABLE, "D3DRS_SRGBWRITEENABLE", ParseBoolean },
	{ D3DRS_DEPTHBIAS, "D3DRS_DEPTHBIAS", ParseFloat },
	{ D3DRS_WRAP8, "D3DRS_WRAP8", ParseTextureWrapFlags },
	{ D3DRS_WRAP9, "D3DRS_WRAP9", ParseTextureWrapFlags },
	{ D3DRS_WRAP10, "D3DRS_WRAP10", ParseTextureWrapFlags },
	{ D3DRS_WRAP11, "D3DRS_WRAP11", ParseTextureWrapFlags },
	{ D3DRS_WRAP12, "D3DRS_WRAP12", ParseTextureWrapFlags },
	{ D3DRS_WRAP13, "D3DRS_WRAP13", ParseTextureWrapFlags },
	{ D3DRS_WRAP14, "D3DRS_WRAP14", ParseTextureWrapFlags },
	{ D3DRS_WRAP15, "D3DRS_WRAP15", ParseTextureWrapFlags },
	{ D3DRS_SEPARATEALPHABLENDENABLE, "D3DRS_SEPARATEALPHABLENDENABLE", ParseBoolean },
	{ D3DRS_SRCBLENDALPHA, "D3DRS_SRCBLENDALPHA", ParseBlendMode },
	{ D3DRS_DESTBLENDALPHA, "D3DRS_DESTBLENDALPHA", ParseBlendMode },
	{ D3DRS_BLENDOPALPHA, "D3DRS_BLENDOPALPHA", ParseBlendOp },
};

//
// Retreive the data for a particular render state index.
//
const RenderStateData& GetRenderStateData(int renderStateDataIndex)
{
	assert(renderStateDataIndex >= 0 && renderStateDataIndex < RENDER_STATE_DATA_SIZE);

	return renderStateData[renderStateDataIndex];
}

//
// The number of actual render states defined by DX.
//
const int RENDER_STATE_DATA_SIZE = sizeof(renderStateData) / sizeof(renderStateData[0]);
