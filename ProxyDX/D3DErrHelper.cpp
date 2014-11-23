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
#include "D3DErrHelper.h"

#define D3DAPPERR_NODIRECT3D          0x82000001
#define D3DAPPERR_NOWINDOW            0x82000002
#define D3DAPPERR_NOCOMPATIBLEDEVICES 0x82000003
#define D3DAPPERR_NOWINDOWABLEDEVICES 0x82000004
#define D3DAPPERR_NOHARDWAREDEVICE    0x82000005
#define D3DAPPERR_HALNOTCOMPATIBLE    0x82000006
#define D3DAPPERR_NOWINDOWEDHAL       0x82000007
#define D3DAPPERR_NODESKTOPHAL        0x82000008
#define D3DAPPERR_NOHALTHISMODE       0x82000009
#define D3DAPPERR_NONZEROREFCOUNT     0x8200000a
#define D3DAPPERR_MEDIANOTFOUND       0x8200000b
#define D3DAPPERR_RESETFAILED         0x8200000c
#define D3DAPPERR_NULLREFDEVICE       0x8200000d

//
// Get an user-displayable string for the error code.
//
const char* GetD3DErrorStr(HRESULT hr)
{
	switch (hr)
	{
	case D3DAPPERR_NODIRECT3D:
		return "Could not initialize Direct3D. You may "
			"want to check that the latest version of"
			"DirectX is correctly installed on your "
			"system.  Also make sure that this program "
			"was compiled with header files that match "
			"the installed DirectX DLLs.";

	case D3DAPPERR_NOCOMPATIBLEDEVICES:
		return "Could not find any compatible Direct3D.";
		break;

	case D3DAPPERR_NOWINDOWABLEDEVICES:
		return "This sample cannot run in a desktop "
			"window with the current display settings. "
			"Please change your desktop settings to a "
			"16- or 32-bit display mode and re-run this "
			"sample.";
		break;

	case D3DAPPERR_NOHARDWAREDEVICE:
		return "No hardware-accelerated Direct3D devices were found.";
		break;

	case D3DAPPERR_HALNOTCOMPATIBLE:
		return "This sample requires functionality that is "
			"not available on your Direct3D hardware accelerator.";

	case D3DAPPERR_NOWINDOWEDHAL:
		return "Your Direct3D hardware accelerator cannot render into a window. "
			"Press F2 while the app is running to see a "
			"list of available devices and modes.";

	case D3DAPPERR_NODESKTOPHAL:
		return "Your Direct3D hardware accelerator cannot render into a window with the current "
			"desktop display settings. Press F2 while the app is running to see a "
			"list of available devices and modes.";

	case D3DAPPERR_NOHALTHISMODE:
		return "This sample requires functionality that is "
			"not available on your Direct3D hardware "
			"accelerator with the current desktop display settings. "
			"Press F2 while the app is running to see a "
			"list of available devices and modes.";

	case D3DAPPERR_MEDIANOTFOUND:
	case 0x80070002: // HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND ):
		return "Could not load required media.";
		break;

	case D3DAPPERR_RESETFAILED:
		return "Could not reset the Direct3D device.";

	case D3DAPPERR_NONZEROREFCOUNT:
		return "A D3D object has a non-zero reference "
			"count (meaning things were not properly cleaned up).";
		break;

	case D3DAPPERR_NULLREFDEVICE:
		return "Warning: Nothing will be rendered. "
			"The reference rendering device was selected, but your "
			"computer only has a reduced-functionality reference device "
			"installed.  Install the DirectX SDK to get the full reference device.";

	case E_OUTOFMEMORY:
		return "Not enough memory.";

	case D3DERR_OUTOFVIDEOMEMORY:
		return "Not enough video memory.";
		break;

	case D3DERR_DRIVERINTERNALERROR:
		return "A serious problem occured inside the display driver.";

	case D3DERR_CONFLICTINGRENDERSTATE:
		return "The currently set render states cannot be used together.";

	case D3DERR_CONFLICTINGTEXTUREFILTER:
		return "The current texture filters cannot be used together.";

	case D3DERR_CONFLICTINGTEXTUREPALETTE:
		return "The current textures cannot be used simultaneously.";

	case D3DERR_DEVICELOST:
		return "The device has been lost but cannot be reset at this time. Therefore, rendering is not possible.";

	case D3DERR_DEVICENOTRESET:
		return "The device has been lost but can be reset at this time.";

	case D3DERR_INVALIDCALL:
		return "The method call is invalid. For example, a method's parameter may not be a valid pointer.";

	case D3DERR_INVALIDDEVICE:
		return "The requested device type is not valid.";

	case D3DERR_MOREDATA:
		return "There is more data available than the specified buffer size can hold.";

	case D3DERR_NOTAVAILABLE:
		return "This device does not support the queried technique.";

	case D3DERR_NOTFOUND:
		return "The requested item was not found.";

	case D3DERR_TOOMANYOPERATIONS:
		return "The application is requesting more texture-filtering operations than the device supports.";

	case D3DERR_UNSUPPORTEDALPHAARG:
		return "The device does not support a specified texture-blending argument for the alpha channel.";

	case D3DERR_UNSUPPORTEDALPHAOPERATION:
		return "The device does not support a specified texture-blending operation for the alpha channel.";

	case D3DERR_UNSUPPORTEDCOLORARG:
		return "The device does not support a specified texture-blending argument for color values.";

	case D3DERR_UNSUPPORTEDCOLOROPERATION:
		return "The device does not support a specified texture-blending operation for color values.";

	case D3DERR_UNSUPPORTEDFACTORVALUE:
		return "The device does not support the specified texture factor value. Not used; provided only to support older drivers.";

	case D3DERR_UNSUPPORTEDTEXTUREFILTER:
		return "The device does not support the specified texture filter.";

	case D3DERR_WRONGTEXTUREFORMAT:
		return "The pixel format of the texture surface is not valid.";

	case E_FAIL:
		return "An undetermined error occurred inside the Direct3D subsystem.";

	case E_INVALIDARG:
		return "An invalid parameter was passed to the returning function.";

	default:
		return "Generic application error. Enable debug output for detailed information.";
	}
}
