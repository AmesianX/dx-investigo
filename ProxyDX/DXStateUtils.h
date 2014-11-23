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

#include <string>

//
// Utils to help format DX state.
//

const int RENDER_STATE_MAX = D3DRS_BLENDOPALPHA+1;

typedef const char* (*ParseRenderStateOption)(DWORD value);

//
// Defines some data for a particular render state.
//
struct RenderStateData
{
	int renderStateIndex;
	const char* name;
	ParseRenderStateOption parseRenderStateOption;
};

//
// Retreive the data for a particular render state index.
//
const RenderStateData& GetRenderStateData(int renderStateDataIndex);

//
// The number of actual render states defined by DX.
//
extern const int RENDER_STATE_DATA_SIZE;

//
// Various formatting functions.
//
const char* DeviceTypeToString(D3DDEVTYPE deviceType);
const char* FormatToString(D3DFORMAT format);
const char* MultiSampleTypeToString(D3DMULTISAMPLE_TYPE type);
const char* SwapEffectToString(D3DSWAPEFFECT swapEffect);
std::string PresentFlagsToString(DWORD flags);
std::string BehaviourFlagsToString(DWORD flags);
