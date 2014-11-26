#include <windows.h>
#include <fstream>
#pragma pack(1)


HINSTANCE hLThis = 0;
HINSTANCE hL = 0;
FARPROC p[727] = {0};

void log(const char* x) {

}
void log2(const char* x) {
	FILE * pFile = NULL;
	fopen_s(&pFile, "c:\\DAOC\\gdi32.log", "a");
	if (pFile != NULL) {
		fputs(x, pFile);
		fputs("\n", pFile);
		fclose(pFile);
	}
}

BOOL WINAPI DllMain(HINSTANCE hInst,DWORD reason,LPVOID)
	{
	if (reason == DLL_PROCESS_ATTACH)
		{
		hLThis = hInst;
		hL = LoadLibrary("c:\\windows\\SysWoW64\\rgdi32.dll");
		if (!hL) return false;


		p[0] = GetProcAddress(hL,"AbortDoc");
		p[1] = GetProcAddress(hL,"AbortPath");
		p[2] = GetProcAddress(hL,"AddFontMemResourceEx");
		p[3] = GetProcAddress(hL,"AddFontResourceA");
		p[4] = GetProcAddress(hL,"AddFontResourceExA");
		p[5] = GetProcAddress(hL,"AddFontResourceExW");
		p[6] = GetProcAddress(hL,"AddFontResourceTracking");
		p[7] = GetProcAddress(hL,"AddFontResourceW");
		p[8] = GetProcAddress(hL,"AngleArc");
		p[9] = GetProcAddress(hL,"AnimatePalette");
		p[10] = GetProcAddress(hL,"AnyLinkedFonts");
		p[11] = GetProcAddress(hL,"Arc");
		p[12] = GetProcAddress(hL,"ArcTo");
		p[13] = GetProcAddress(hL,"BRUSHOBJ_hGetColorTransform");
		p[14] = GetProcAddress(hL,"BRUSHOBJ_pvAllocRbrush");
		p[15] = GetProcAddress(hL,"BRUSHOBJ_pvGetRbrush");
		p[16] = GetProcAddress(hL,"BRUSHOBJ_ulGetBrushColor");
		p[17] = GetProcAddress(hL,"BeginGdiRendering");
		p[18] = GetProcAddress(hL,"BeginPath");
		p[19] = GetProcAddress(hL,"BitBlt");
		p[20] = GetProcAddress(hL,"CLIPOBJ_bEnum");
		p[21] = GetProcAddress(hL,"CLIPOBJ_cEnumStart");
		p[22] = GetProcAddress(hL,"CLIPOBJ_ppoGetPath");
		p[23] = GetProcAddress(hL,"CancelDC");
		p[24] = GetProcAddress(hL,"CheckColorsInGamut");
		p[25] = GetProcAddress(hL,"ChoosePixelFormat");
		p[26] = GetProcAddress(hL,"Chord");
		p[27] = GetProcAddress(hL,"ClearBitmapAttributes");
		p[28] = GetProcAddress(hL,"ClearBrushAttributes");
		p[29] = GetProcAddress(hL,"CloseEnhMetaFile");
		p[30] = GetProcAddress(hL,"CloseFigure");
		p[31] = GetProcAddress(hL,"CloseMetaFile");
		p[32] = GetProcAddress(hL,"ColorCorrectPalette");
		p[33] = GetProcAddress(hL,"ColorMatchToTarget");
		p[34] = GetProcAddress(hL,"CombineRgn");
		p[35] = GetProcAddress(hL,"CombineTransform");
		p[36] = GetProcAddress(hL,"ConfigureOPMProtectedOutput");
		p[37] = GetProcAddress(hL,"CopyEnhMetaFileA");
		p[38] = GetProcAddress(hL,"CopyEnhMetaFileW");
		p[39] = GetProcAddress(hL,"CopyMetaFileA");
		p[40] = GetProcAddress(hL,"CopyMetaFileW");
		p[41] = GetProcAddress(hL,"CreateBitmap");
		p[42] = GetProcAddress(hL,"CreateBitmapFromDxSurface");
		p[43] = GetProcAddress(hL,"CreateBitmapIndirect");
		p[44] = GetProcAddress(hL,"CreateBrushIndirect");
		p[45] = GetProcAddress(hL,"CreateColorSpaceA");
		p[46] = GetProcAddress(hL,"CreateColorSpaceW");
		p[47] = GetProcAddress(hL,"CreateCompatibleBitmap");
		p[48] = GetProcAddress(hL,"CreateCompatibleDC");
		p[49] = GetProcAddress(hL,"CreateDCA");
		p[50] = GetProcAddress(hL,"CreateDCW");
		p[51] = GetProcAddress(hL,"CreateDIBPatternBrush");
		p[52] = GetProcAddress(hL,"CreateDIBPatternBrushPt");
		p[53] = GetProcAddress(hL,"CreateDIBSection");
		p[54] = GetProcAddress(hL,"CreateDIBitmap");
		p[55] = GetProcAddress(hL,"CreateDiscardableBitmap");
		p[56] = GetProcAddress(hL,"CreateEllipticRgn");
		p[57] = GetProcAddress(hL,"CreateEllipticRgnIndirect");
		p[58] = GetProcAddress(hL,"CreateEnhMetaFileA");
		p[59] = GetProcAddress(hL,"CreateEnhMetaFileW");
		p[60] = GetProcAddress(hL,"CreateFontA");
		p[61] = GetProcAddress(hL,"CreateFontIndirectA");
		p[62] = GetProcAddress(hL,"CreateFontIndirectExA");
		p[63] = GetProcAddress(hL,"CreateFontIndirectExW");
		p[64] = GetProcAddress(hL,"CreateFontIndirectW");
		p[65] = GetProcAddress(hL,"CreateFontW");
		p[66] = GetProcAddress(hL,"CreateHalftonePalette");
		p[67] = GetProcAddress(hL,"CreateHatchBrush");
		p[68] = GetProcAddress(hL,"CreateICA");
		p[69] = GetProcAddress(hL,"CreateICW");
		p[70] = GetProcAddress(hL,"CreateMetaFileA");
		p[71] = GetProcAddress(hL,"CreateMetaFileW");
		p[72] = GetProcAddress(hL,"CreateOPMProtectedOutputs");
		p[73] = GetProcAddress(hL,"CreatePalette");
		p[74] = GetProcAddress(hL,"CreatePatternBrush");
		p[75] = GetProcAddress(hL,"CreatePen");
		p[76] = GetProcAddress(hL,"CreatePenIndirect");
		p[77] = GetProcAddress(hL,"CreatePolyPolygonRgn");
		p[78] = GetProcAddress(hL,"CreatePolygonRgn");
		p[79] = GetProcAddress(hL,"CreateRectRgn");
		p[80] = GetProcAddress(hL,"CreateRectRgnIndirect");
		p[81] = GetProcAddress(hL,"CreateRoundRectRgn");
		p[82] = GetProcAddress(hL,"CreateScalableFontResourceA");
		p[83] = GetProcAddress(hL,"CreateScalableFontResourceW");
		p[84] = GetProcAddress(hL,"CreateSolidBrush");
		p[85] = GetProcAddress(hL,"D3DKMTAcquireKeyedMutex");
		p[86] = GetProcAddress(hL,"D3DKMTCheckExclusiveOwnership");
		p[87] = GetProcAddress(hL,"D3DKMTCheckMonitorPowerState");
		p[88] = GetProcAddress(hL,"D3DKMTCheckOcclusion");
		p[89] = GetProcAddress(hL,"D3DKMTCheckSharedResourceAccess");
		p[90] = GetProcAddress(hL,"D3DKMTCheckVidPnExclusiveOwnership");
		p[91] = GetProcAddress(hL,"D3DKMTCloseAdapter");
		p[92] = GetProcAddress(hL,"D3DKMTConfigureSharedResource");
		p[93] = GetProcAddress(hL,"D3DKMTCreateAllocation");
		p[94] = GetProcAddress(hL,"D3DKMTCreateAllocation2");
		p[95] = GetProcAddress(hL,"D3DKMTCreateContext");
		p[96] = GetProcAddress(hL,"D3DKMTCreateDCFromMemory");
		p[97] = GetProcAddress(hL,"D3DKMTCreateDevice");
		p[98] = GetProcAddress(hL,"D3DKMTCreateKeyedMutex");
		p[99] = GetProcAddress(hL,"D3DKMTCreateOverlay");
		p[100] = GetProcAddress(hL,"D3DKMTCreateSynchronizationObject");
		p[101] = GetProcAddress(hL,"D3DKMTCreateSynchronizationObject2");
		p[102] = GetProcAddress(hL,"D3DKMTDestroyAllocation");
		p[103] = GetProcAddress(hL,"D3DKMTDestroyContext");
		p[104] = GetProcAddress(hL,"D3DKMTDestroyDCFromMemory");
		p[105] = GetProcAddress(hL,"D3DKMTDestroyDevice");
		p[106] = GetProcAddress(hL,"D3DKMTDestroyKeyedMutex");
		p[107] = GetProcAddress(hL,"D3DKMTDestroyOverlay");
		p[108] = GetProcAddress(hL,"D3DKMTDestroySynchronizationObject");
		p[109] = GetProcAddress(hL,"D3DKMTEscape");
		p[110] = GetProcAddress(hL,"D3DKMTFlipOverlay");
		p[111] = GetProcAddress(hL,"D3DKMTGetContextSchedulingPriority");
		p[112] = GetProcAddress(hL,"D3DKMTGetDeviceState");
		p[113] = GetProcAddress(hL,"D3DKMTGetDisplayModeList");
		p[114] = GetProcAddress(hL,"D3DKMTGetMultisampleMethodList");
		p[115] = GetProcAddress(hL,"D3DKMTGetOverlayState");
		p[116] = GetProcAddress(hL,"D3DKMTGetPresentHistory");
		p[117] = GetProcAddress(hL,"D3DKMTGetPresentQueueEvent");
		p[118] = GetProcAddress(hL,"D3DKMTGetProcessSchedulingPriorityClass");
		p[119] = GetProcAddress(hL,"D3DKMTGetRuntimeData");
		p[120] = GetProcAddress(hL,"D3DKMTGetScanLine");
		p[121] = GetProcAddress(hL,"D3DKMTGetSharedPrimaryHandle");
		p[122] = GetProcAddress(hL,"D3DKMTInvalidateActiveVidPn");
		p[123] = GetProcAddress(hL,"D3DKMTLock");
		p[124] = GetProcAddress(hL,"D3DKMTOpenAdapterFromDeviceName");
		p[125] = GetProcAddress(hL,"D3DKMTOpenAdapterFromGdiDisplayName");
		p[126] = GetProcAddress(hL,"D3DKMTOpenAdapterFromHdc");
		p[127] = GetProcAddress(hL,"D3DKMTOpenKeyedMutex");
		p[128] = GetProcAddress(hL,"D3DKMTOpenResource");
		p[129] = GetProcAddress(hL,"D3DKMTOpenResource2");
		p[130] = GetProcAddress(hL,"D3DKMTOpenSynchronizationObject");
		p[131] = GetProcAddress(hL,"D3DKMTPollDisplayChildren");
		p[132] = GetProcAddress(hL,"D3DKMTPresent");
		p[133] = GetProcAddress(hL,"D3DKMTQueryAdapterInfo");
		p[134] = GetProcAddress(hL,"D3DKMTQueryAllocationResidency");
		p[135] = GetProcAddress(hL,"D3DKMTQueryResourceInfo");
		p[136] = GetProcAddress(hL,"D3DKMTQueryStatistics");
		p[137] = GetProcAddress(hL,"D3DKMTReleaseKeyedMutex");
		p[138] = GetProcAddress(hL,"D3DKMTReleaseProcessVidPnSourceOwners");
		p[139] = GetProcAddress(hL,"D3DKMTRender");
		p[140] = GetProcAddress(hL,"D3DKMTSetAllocationPriority");
		p[141] = GetProcAddress(hL,"D3DKMTSetContextSchedulingPriority");
		p[142] = GetProcAddress(hL,"D3DKMTSetDisplayMode");
		p[143] = GetProcAddress(hL,"D3DKMTSetDisplayPrivateDriverFormat");
		p[144] = GetProcAddress(hL,"D3DKMTSetGammaRamp");
		p[145] = GetProcAddress(hL,"D3DKMTSetProcessSchedulingPriorityClass");
		p[146] = GetProcAddress(hL,"D3DKMTSetQueuedLimit");
		p[147] = GetProcAddress(hL,"D3DKMTSetVidPnSourceOwner");
		p[148] = GetProcAddress(hL,"D3DKMTSharedPrimaryLockNotification");
		p[149] = GetProcAddress(hL,"D3DKMTSharedPrimaryUnLockNotification");
		p[150] = GetProcAddress(hL,"D3DKMTSignalSynchronizationObject");
		p[151] = GetProcAddress(hL,"D3DKMTSignalSynchronizationObject2");
		p[152] = GetProcAddress(hL,"D3DKMTUnlock");
		p[153] = GetProcAddress(hL,"D3DKMTUpdateOverlay");
		p[154] = GetProcAddress(hL,"D3DKMTWaitForIdle");
		p[155] = GetProcAddress(hL,"D3DKMTWaitForSynchronizationObject");
		p[156] = GetProcAddress(hL,"D3DKMTWaitForSynchronizationObject2");
		p[157] = GetProcAddress(hL,"D3DKMTWaitForVerticalBlankEvent");
		p[158] = GetProcAddress(hL,"DDCCIGetCapabilitiesString");
		p[159] = GetProcAddress(hL,"DDCCIGetCapabilitiesStringLength");
		p[160] = GetProcAddress(hL,"DDCCIGetTimingReport");
		p[161] = GetProcAddress(hL,"DDCCIGetVCPFeature");
		p[162] = GetProcAddress(hL,"DDCCISaveCurrentSettings");
		p[163] = GetProcAddress(hL,"DDCCISetVCPFeature");
		p[164] = GetProcAddress(hL,"DPtoLP");
		p[165] = GetProcAddress(hL,"DdCreateFullscreenSprite");
		p[166] = GetProcAddress(hL,"DdDestroyFullscreenSprite");
		p[167] = GetProcAddress(hL,"DdEntry0");
		p[168] = GetProcAddress(hL,"DdEntry1");
		p[169] = GetProcAddress(hL,"DdEntry10");
		p[170] = GetProcAddress(hL,"DdEntry11");
		p[171] = GetProcAddress(hL,"DdEntry12");
		p[172] = GetProcAddress(hL,"DdEntry13");
		p[173] = GetProcAddress(hL,"DdEntry14");
		p[174] = GetProcAddress(hL,"DdEntry15");
		p[175] = GetProcAddress(hL,"DdEntry16");
		p[176] = GetProcAddress(hL,"DdEntry17");
		p[177] = GetProcAddress(hL,"DdEntry18");
		p[178] = GetProcAddress(hL,"DdEntry19");
		p[179] = GetProcAddress(hL,"DdEntry2");
		p[180] = GetProcAddress(hL,"DdEntry20");
		p[181] = GetProcAddress(hL,"DdEntry21");
		p[182] = GetProcAddress(hL,"DdEntry22");
		p[183] = GetProcAddress(hL,"DdEntry23");
		p[184] = GetProcAddress(hL,"DdEntry24");
		p[185] = GetProcAddress(hL,"DdEntry25");
		p[186] = GetProcAddress(hL,"DdEntry26");
		p[187] = GetProcAddress(hL,"DdEntry27");
		p[188] = GetProcAddress(hL,"DdEntry28");
		p[189] = GetProcAddress(hL,"DdEntry29");
		p[190] = GetProcAddress(hL,"DdEntry3");
		p[191] = GetProcAddress(hL,"DdEntry30");
		p[192] = GetProcAddress(hL,"DdEntry31");
		p[193] = GetProcAddress(hL,"DdEntry32");
		p[194] = GetProcAddress(hL,"DdEntry33");
		p[195] = GetProcAddress(hL,"DdEntry34");
		p[196] = GetProcAddress(hL,"DdEntry35");
		p[197] = GetProcAddress(hL,"DdEntry36");
		p[198] = GetProcAddress(hL,"DdEntry37");
		p[199] = GetProcAddress(hL,"DdEntry38");
		p[200] = GetProcAddress(hL,"DdEntry39");
		p[201] = GetProcAddress(hL,"DdEntry4");
		p[202] = GetProcAddress(hL,"DdEntry40");
		p[203] = GetProcAddress(hL,"DdEntry41");
		p[204] = GetProcAddress(hL,"DdEntry42");
		p[205] = GetProcAddress(hL,"DdEntry43");
		p[206] = GetProcAddress(hL,"DdEntry44");
		p[207] = GetProcAddress(hL,"DdEntry45");
		p[208] = GetProcAddress(hL,"DdEntry46");
		p[209] = GetProcAddress(hL,"DdEntry47");
		p[210] = GetProcAddress(hL,"DdEntry48");
		p[211] = GetProcAddress(hL,"DdEntry49");
		p[212] = GetProcAddress(hL,"DdEntry5");
		p[213] = GetProcAddress(hL,"DdEntry50");
		p[214] = GetProcAddress(hL,"DdEntry51");
		p[215] = GetProcAddress(hL,"DdEntry52");
		p[216] = GetProcAddress(hL,"DdEntry53");
		p[217] = GetProcAddress(hL,"DdEntry54");
		p[218] = GetProcAddress(hL,"DdEntry55");
		p[219] = GetProcAddress(hL,"DdEntry56");
		p[220] = GetProcAddress(hL,"DdEntry6");
		p[221] = GetProcAddress(hL,"DdEntry7");
		p[222] = GetProcAddress(hL,"DdEntry8");
		p[223] = GetProcAddress(hL,"DdEntry9");
		p[224] = GetProcAddress(hL,"DdNotifyFullscreenSpriteUpdate");
		p[225] = GetProcAddress(hL,"DdQueryVisRgnUniqueness");
		p[226] = GetProcAddress(hL,"DeleteColorSpace");
		p[227] = GetProcAddress(hL,"DeleteDC");
		p[228] = GetProcAddress(hL,"DeleteEnhMetaFile");
		p[229] = GetProcAddress(hL,"DeleteMetaFile");
		p[230] = GetProcAddress(hL,"DeleteObject");
		p[231] = GetProcAddress(hL,"DescribePixelFormat");
		p[232] = GetProcAddress(hL,"DestroyOPMProtectedOutput");
		p[233] = GetProcAddress(hL,"DestroyPhysicalMonitorInternal");
		p[234] = GetProcAddress(hL,"DeviceCapabilitiesExA");
		p[235] = GetProcAddress(hL,"DeviceCapabilitiesExW");
		p[236] = GetProcAddress(hL,"DrawEscape");
		p[237] = GetProcAddress(hL,"Ellipse");
		p[238] = GetProcAddress(hL,"EnableEUDC");
		p[239] = GetProcAddress(hL,"EndDoc");
		p[240] = GetProcAddress(hL,"EndFormPage");
		p[241] = GetProcAddress(hL,"EndGdiRendering");
		p[242] = GetProcAddress(hL,"EndPage");
		p[243] = GetProcAddress(hL,"EndPath");
		p[244] = GetProcAddress(hL,"EngAcquireSemaphore");
		p[245] = GetProcAddress(hL,"EngAlphaBlend");
		p[246] = GetProcAddress(hL,"EngAssociateSurface");
		p[247] = GetProcAddress(hL,"EngBitBlt");
		p[248] = GetProcAddress(hL,"EngCheckAbort");
		p[249] = GetProcAddress(hL,"EngComputeGlyphSet");
		p[250] = GetProcAddress(hL,"EngCopyBits");
		p[251] = GetProcAddress(hL,"EngCreateBitmap");
		p[252] = GetProcAddress(hL,"EngCreateClip");
		p[253] = GetProcAddress(hL,"EngCreateDeviceBitmap");
		p[254] = GetProcAddress(hL,"EngCreateDeviceSurface");
		p[255] = GetProcAddress(hL,"EngCreatePalette");
		p[256] = GetProcAddress(hL,"EngCreateSemaphore");
		p[257] = GetProcAddress(hL,"EngDeleteClip");
		p[258] = GetProcAddress(hL,"EngDeletePalette");
		p[259] = GetProcAddress(hL,"EngDeletePath");
		p[260] = GetProcAddress(hL,"EngDeleteSemaphore");
		p[261] = GetProcAddress(hL,"EngDeleteSurface");
		p[262] = GetProcAddress(hL,"EngEraseSurface");
		p[263] = GetProcAddress(hL,"EngFillPath");
		p[264] = GetProcAddress(hL,"EngFindResource");
		p[265] = GetProcAddress(hL,"EngFreeModule");
		p[266] = GetProcAddress(hL,"EngGetCurrentCodePage");
		p[267] = GetProcAddress(hL,"EngGetDriverName");
		p[268] = GetProcAddress(hL,"EngGetPrinterDataFileName");
		p[269] = GetProcAddress(hL,"EngGradientFill");
		p[270] = GetProcAddress(hL,"EngLineTo");
		p[271] = GetProcAddress(hL,"EngLoadModule");
		p[272] = GetProcAddress(hL,"EngLockSurface");
		p[273] = GetProcAddress(hL,"EngMarkBandingSurface");
		p[274] = GetProcAddress(hL,"EngMultiByteToUnicodeN");
		p[275] = GetProcAddress(hL,"EngMultiByteToWideChar");
		p[276] = GetProcAddress(hL,"EngPaint");
		p[277] = GetProcAddress(hL,"EngPlgBlt");
		p[278] = GetProcAddress(hL,"EngQueryEMFInfo");
		p[279] = GetProcAddress(hL,"EngQueryLocalTime");
		p[280] = GetProcAddress(hL,"EngReleaseSemaphore");
		p[281] = GetProcAddress(hL,"EngStretchBlt");
		p[282] = GetProcAddress(hL,"EngStretchBltROP");
		p[283] = GetProcAddress(hL,"EngStrokeAndFillPath");
		p[284] = GetProcAddress(hL,"EngStrokePath");
		p[285] = GetProcAddress(hL,"EngTextOut");
		p[286] = GetProcAddress(hL,"EngTransparentBlt");
		p[287] = GetProcAddress(hL,"EngUnicodeToMultiByteN");
		p[288] = GetProcAddress(hL,"EngUnlockSurface");
		p[289] = GetProcAddress(hL,"EngWideCharToMultiByte");
		p[290] = GetProcAddress(hL,"EnumEnhMetaFile");
		p[291] = GetProcAddress(hL,"EnumFontFamiliesA");
		p[292] = GetProcAddress(hL,"EnumFontFamiliesExA");
		p[293] = GetProcAddress(hL,"EnumFontFamiliesExW");
		p[294] = GetProcAddress(hL,"EnumFontFamiliesW");
		p[295] = GetProcAddress(hL,"EnumFontsA");
		p[296] = GetProcAddress(hL,"EnumFontsW");
		p[297] = GetProcAddress(hL,"EnumICMProfilesA");
		p[298] = GetProcAddress(hL,"EnumICMProfilesW");
		p[299] = GetProcAddress(hL,"EnumMetaFile");
		p[300] = GetProcAddress(hL,"EnumObjects");
		p[301] = GetProcAddress(hL,"EqualRgn");
		p[302] = GetProcAddress(hL,"Escape");
		p[303] = GetProcAddress(hL,"EudcLoadLinkW");
		p[304] = GetProcAddress(hL,"EudcUnloadLinkW");
		p[305] = GetProcAddress(hL,"ExcludeClipRect");
		p[306] = GetProcAddress(hL,"ExtCreatePen");
		p[307] = GetProcAddress(hL,"ExtCreateRegion");
		p[308] = GetProcAddress(hL,"ExtEscape");
		p[309] = GetProcAddress(hL,"ExtFloodFill");
		p[310] = GetProcAddress(hL,"ExtSelectClipRgn");
		p[311] = GetProcAddress(hL,"ExtTextOutA");
		p[312] = GetProcAddress(hL,"ExtTextOutW");
		p[313] = GetProcAddress(hL,"FONTOBJ_cGetAllGlyphHandles");
		p[314] = GetProcAddress(hL,"FONTOBJ_cGetGlyphs");
		p[315] = GetProcAddress(hL,"FONTOBJ_pQueryGlyphAttrs");
		p[316] = GetProcAddress(hL,"FONTOBJ_pfdg");
		p[317] = GetProcAddress(hL,"FONTOBJ_pifi");
		p[318] = GetProcAddress(hL,"FONTOBJ_pvTrueTypeFontFile");
		p[319] = GetProcAddress(hL,"FONTOBJ_pxoGetXform");
		p[320] = GetProcAddress(hL,"FONTOBJ_vGetInfo");
		p[321] = GetProcAddress(hL,"FillPath");
		p[322] = GetProcAddress(hL,"FillRgn");
		p[323] = GetProcAddress(hL,"FixBrushOrgEx");
		p[324] = GetProcAddress(hL,"FlattenPath");
		p[325] = GetProcAddress(hL,"FloodFill");
		p[326] = GetProcAddress(hL,"FontIsLinked");
		p[327] = GetProcAddress(hL,"FrameRgn");
		p[328] = GetProcAddress(hL,"GdiAddFontResourceW");
		p[329] = GetProcAddress(hL,"GdiAddGlsBounds");
		p[330] = GetProcAddress(hL,"GdiAddGlsRecord");
		p[331] = GetProcAddress(hL,"GdiAlphaBlend");
		p[332] = GetProcAddress(hL,"GdiArtificialDecrementDriver");
		p[333] = GetProcAddress(hL,"GdiCleanCacheDC");
		p[334] = GetProcAddress(hL,"GdiComment");
		p[335] = GetProcAddress(hL,"GdiConsoleTextOut");
		p[336] = GetProcAddress(hL,"GdiConvertAndCheckDC");
		p[337] = GetProcAddress(hL,"GdiConvertBitmap");
		p[338] = GetProcAddress(hL,"GdiConvertBitmapV5");
		p[339] = GetProcAddress(hL,"GdiConvertBrush");
		p[340] = GetProcAddress(hL,"GdiConvertDC");
		p[341] = GetProcAddress(hL,"GdiConvertEnhMetaFile");
		p[342] = GetProcAddress(hL,"GdiConvertFont");
		p[343] = GetProcAddress(hL,"GdiConvertMetaFilePict");
		p[344] = GetProcAddress(hL,"GdiConvertPalette");
		p[345] = GetProcAddress(hL,"GdiConvertRegion");
		p[346] = GetProcAddress(hL,"GdiConvertToDevmodeW");
		p[347] = GetProcAddress(hL,"GdiCreateLocalEnhMetaFile");
		p[348] = GetProcAddress(hL,"GdiCreateLocalMetaFilePict");
		p[349] = GetProcAddress(hL,"GdiDeleteLocalDC");
		p[350] = GetProcAddress(hL,"GdiDeleteSpoolFileHandle");
		p[351] = GetProcAddress(hL,"GdiDescribePixelFormat");
		p[352] = GetProcAddress(hL,"GdiDllInitialize");
		p[353] = GetProcAddress(hL,"GdiDrawStream");
		p[354] = GetProcAddress(hL,"GdiEndDocEMF");
		p[355] = GetProcAddress(hL,"GdiEndPageEMF");
		p[356] = GetProcAddress(hL,"GdiEntry1");
		p[357] = GetProcAddress(hL,"GdiEntry10");
		p[358] = GetProcAddress(hL,"GdiEntry11");
		p[359] = GetProcAddress(hL,"GdiEntry12");
		p[360] = GetProcAddress(hL,"GdiEntry13");
		p[361] = GetProcAddress(hL,"GdiEntry14");
		p[362] = GetProcAddress(hL,"GdiEntry15");
		p[363] = GetProcAddress(hL,"GdiEntry16");
		p[364] = GetProcAddress(hL,"GdiEntry2");
		p[365] = GetProcAddress(hL,"GdiEntry3");
		p[366] = GetProcAddress(hL,"GdiEntry4");
		p[367] = GetProcAddress(hL,"GdiEntry5");
		p[368] = GetProcAddress(hL,"GdiEntry6");
		p[369] = GetProcAddress(hL,"GdiEntry7");
		p[370] = GetProcAddress(hL,"GdiEntry8");
		p[371] = GetProcAddress(hL,"GdiEntry9");
		p[372] = GetProcAddress(hL,"GdiFixUpHandle");
		p[373] = GetProcAddress(hL,"GdiFlush");
		p[374] = GetProcAddress(hL,"GdiFullscreenControl");
		p[375] = GetProcAddress(hL,"GdiGetBatchLimit");
		p[376] = GetProcAddress(hL,"GdiGetBitmapBitsSize");
		p[377] = GetProcAddress(hL,"GdiGetCharDimensions");
		p[378] = GetProcAddress(hL,"GdiGetCodePage");
		p[379] = GetProcAddress(hL,"GdiGetDC");
		p[380] = GetProcAddress(hL,"GdiGetDevmodeForPage");
		p[381] = GetProcAddress(hL,"GdiGetLocalBrush");
		p[382] = GetProcAddress(hL,"GdiGetLocalDC");
		p[383] = GetProcAddress(hL,"GdiGetLocalFont");
		p[384] = GetProcAddress(hL,"GdiGetPageCount");
		p[385] = GetProcAddress(hL,"GdiGetPageHandle");
		p[386] = GetProcAddress(hL,"GdiGetSpoolFileHandle");
		p[387] = GetProcAddress(hL,"GdiGetSpoolMessage");
		p[388] = GetProcAddress(hL,"GdiGradientFill");
		p[389] = GetProcAddress(hL,"GdiInitSpool");
		p[390] = GetProcAddress(hL,"GdiInitializeLanguagePack");
		p[391] = GetProcAddress(hL,"GdiIsMetaFileDC");
		p[392] = GetProcAddress(hL,"GdiIsMetaPrintDC");
		p[393] = GetProcAddress(hL,"GdiIsPlayMetafileDC");
		p[394] = GetProcAddress(hL,"GdiIsScreenDC");
		p[395] = GetProcAddress(hL,"GdiLoadType1Fonts");
		p[396] = GetProcAddress(hL,"GdiPlayDCScript");
		p[397] = GetProcAddress(hL,"GdiPlayEMF");
		p[398] = GetProcAddress(hL,"GdiPlayJournal");
		p[399] = GetProcAddress(hL,"GdiPlayPageEMF");
		p[400] = GetProcAddress(hL,"GdiPlayPrivatePageEMF");
		p[401] = GetProcAddress(hL,"GdiPlayScript");
		p[402] = GetProcAddress(hL,"GdiPrinterThunk");
		p[403] = GetProcAddress(hL,"GdiProcessSetup");
		p[404] = GetProcAddress(hL,"GdiQueryFonts");
		p[405] = GetProcAddress(hL,"GdiQueryTable");
		p[406] = GetProcAddress(hL,"GdiRealizationInfo");
		p[407] = GetProcAddress(hL,"GdiReleaseDC");
		p[408] = GetProcAddress(hL,"GdiReleaseLocalDC");
		p[409] = GetProcAddress(hL,"GdiResetDCEMF");
		p[410] = GetProcAddress(hL,"GdiSetAttrs");
		p[411] = GetProcAddress(hL,"GdiSetBatchLimit");
		p[412] = GetProcAddress(hL,"GdiSetLastError");
		p[413] = GetProcAddress(hL,"GdiSetPixelFormat");
		p[414] = GetProcAddress(hL,"GdiSetServerAttr");
		p[415] = GetProcAddress(hL,"GdiStartDocEMF");
		p[416] = GetProcAddress(hL,"GdiStartPageEMF");
		p[417] = GetProcAddress(hL,"GdiSwapBuffers");
		p[418] = GetProcAddress(hL,"GdiTransparentBlt");
		p[419] = GetProcAddress(hL,"GdiValidateHandle");
		p[420] = GetProcAddress(hL,"GetArcDirection");
		p[421] = GetProcAddress(hL,"GetAspectRatioFilterEx");
		p[422] = GetProcAddress(hL,"GetBitmapAttributes");
		p[423] = GetProcAddress(hL,"GetBitmapBits");
		p[424] = GetProcAddress(hL,"GetBitmapDimensionEx");
		p[425] = GetProcAddress(hL,"GetBkColor");
		p[426] = GetProcAddress(hL,"GetBkMode");
		p[427] = GetProcAddress(hL,"GetBoundsRect");
		p[428] = GetProcAddress(hL,"GetBrushAttributes");
		p[429] = GetProcAddress(hL,"GetBrushOrgEx");
		p[430] = GetProcAddress(hL,"GetCOPPCompatibleOPMInformation");
		p[431] = GetProcAddress(hL,"GetCertificate");
		p[432] = GetProcAddress(hL,"GetCertificateSize");
		p[433] = GetProcAddress(hL,"GetCharABCWidthsA");
		p[434] = GetProcAddress(hL,"GetCharABCWidthsFloatA");
		p[435] = GetProcAddress(hL,"GetCharABCWidthsFloatW");
		p[436] = GetProcAddress(hL,"GetCharABCWidthsI");
		p[437] = GetProcAddress(hL,"GetCharABCWidthsW");
		p[438] = GetProcAddress(hL,"GetCharWidth32A");
		p[439] = GetProcAddress(hL,"GetCharWidth32W");
		p[440] = GetProcAddress(hL,"GetCharWidthA");
		p[441] = GetProcAddress(hL,"GetCharWidthFloatA");
		p[442] = GetProcAddress(hL,"GetCharWidthFloatW");
		p[443] = GetProcAddress(hL,"GetCharWidthI");
		p[444] = GetProcAddress(hL,"GetCharWidthInfo");
		p[445] = GetProcAddress(hL,"GetCharWidthW");
		p[446] = GetProcAddress(hL,"GetCharacterPlacementA");
		p[447] = GetProcAddress(hL,"GetCharacterPlacementW");
		p[448] = GetProcAddress(hL,"GetClipBox");
		p[449] = GetProcAddress(hL,"GetClipRgn");
		p[450] = GetProcAddress(hL,"GetColorAdjustment");
		p[451] = GetProcAddress(hL,"GetColorSpace");
		p[452] = GetProcAddress(hL,"GetCurrentObject");
		p[453] = GetProcAddress(hL,"GetCurrentPositionEx");
		p[454] = GetProcAddress(hL,"GetDCBrushColor");
		p[455] = GetProcAddress(hL,"GetDCOrgEx");
		p[456] = GetProcAddress(hL,"GetDCPenColor");
		p[457] = GetProcAddress(hL,"GetDIBColorTable");
		p[458] = GetProcAddress(hL,"GetDIBits");
		p[459] = GetProcAddress(hL,"GetDeviceCaps");
		p[460] = GetProcAddress(hL,"GetDeviceGammaRamp");
		p[461] = GetProcAddress(hL,"GetETM");
		p[462] = GetProcAddress(hL,"GetEUDCTimeStamp");
		p[463] = GetProcAddress(hL,"GetEUDCTimeStampExW");
		p[464] = GetProcAddress(hL,"GetEnhMetaFileA");
		p[465] = GetProcAddress(hL,"GetEnhMetaFileBits");
		p[466] = GetProcAddress(hL,"GetEnhMetaFileDescriptionA");
		p[467] = GetProcAddress(hL,"GetEnhMetaFileDescriptionW");
		p[468] = GetProcAddress(hL,"GetEnhMetaFileHeader");
		p[469] = GetProcAddress(hL,"GetEnhMetaFilePaletteEntries");
		p[470] = GetProcAddress(hL,"GetEnhMetaFilePixelFormat");
		p[471] = GetProcAddress(hL,"GetEnhMetaFileW");
		p[472] = GetProcAddress(hL,"GetFontAssocStatus");
		p[473] = GetProcAddress(hL,"GetFontData");
		p[474] = GetProcAddress(hL,"GetFontFileData");
		p[475] = GetProcAddress(hL,"GetFontFileInfo");
		p[476] = GetProcAddress(hL,"GetFontLanguageInfo");
		p[477] = GetProcAddress(hL,"GetFontRealizationInfo");
		p[478] = GetProcAddress(hL,"GetFontResourceInfoW");
		p[479] = GetProcAddress(hL,"GetFontUnicodeRanges");
		p[480] = GetProcAddress(hL,"GetGlyphIndicesA");
		p[481] = GetProcAddress(hL,"GetGlyphIndicesW");
		p[482] = GetProcAddress(hL,"GetGlyphOutline");
		p[483] = GetProcAddress(hL,"GetGlyphOutlineA");
		p[484] = GetProcAddress(hL,"GetGlyphOutlineW");
		p[485] = GetProcAddress(hL,"GetGlyphOutlineWow");
		p[486] = GetProcAddress(hL,"GetGraphicsMode");
		p[487] = GetProcAddress(hL,"GetHFONT");
		p[488] = GetProcAddress(hL,"GetICMProfileA");
		p[489] = GetProcAddress(hL,"GetICMProfileW");
		p[490] = GetProcAddress(hL,"GetKerningPairs");
		p[491] = GetProcAddress(hL,"GetKerningPairsA");
		p[492] = GetProcAddress(hL,"GetKerningPairsW");
		p[493] = GetProcAddress(hL,"GetLayout");
		p[494] = GetProcAddress(hL,"GetLogColorSpaceA");
		p[495] = GetProcAddress(hL,"GetLogColorSpaceW");
		p[496] = GetProcAddress(hL,"GetMapMode");
		p[497] = GetProcAddress(hL,"GetMetaFileA");
		p[498] = GetProcAddress(hL,"GetMetaFileBitsEx");
		p[499] = GetProcAddress(hL,"GetMetaFileW");
		p[500] = GetProcAddress(hL,"GetMetaRgn");
		p[501] = GetProcAddress(hL,"GetMiterLimit");
		p[502] = GetProcAddress(hL,"GetNearestColor");
		p[503] = GetProcAddress(hL,"GetNearestPaletteIndex");
		p[504] = GetProcAddress(hL,"GetNumberOfPhysicalMonitors");
		p[505] = GetProcAddress(hL,"GetOPMInformation");
		p[506] = GetProcAddress(hL,"GetOPMRandomNumber");
		p[507] = GetProcAddress(hL,"GetObjectA");
		p[508] = GetProcAddress(hL,"GetObjectType");
		p[509] = GetProcAddress(hL,"GetObjectW");
		p[510] = GetProcAddress(hL,"GetOutlineTextMetricsA");
		p[511] = GetProcAddress(hL,"GetOutlineTextMetricsW");
		p[512] = GetProcAddress(hL,"GetPaletteEntries");
		p[513] = GetProcAddress(hL,"GetPath");
		p[514] = GetProcAddress(hL,"GetPhysicalMonitorDescription");
		p[515] = GetProcAddress(hL,"GetPhysicalMonitors");
		p[516] = GetProcAddress(hL,"GetPixel");
		p[517] = GetProcAddress(hL,"GetPixelFormat");
		p[518] = GetProcAddress(hL,"GetPolyFillMode");
		p[519] = GetProcAddress(hL,"GetROP2");
		p[520] = GetProcAddress(hL,"GetRandomRgn");
		p[521] = GetProcAddress(hL,"GetRasterizerCaps");
		p[522] = GetProcAddress(hL,"GetRegionData");
		p[523] = GetProcAddress(hL,"GetRelAbs");
		p[524] = GetProcAddress(hL,"GetRgnBox");
		p[525] = GetProcAddress(hL,"GetStockObject");
		p[526] = GetProcAddress(hL,"GetStretchBltMode");
		p[527] = GetProcAddress(hL,"GetStringBitmapA");
		p[528] = GetProcAddress(hL,"GetStringBitmapW");
		p[529] = GetProcAddress(hL,"GetSuggestedOPMProtectedOutputArraySize");
		p[530] = GetProcAddress(hL,"GetSystemPaletteEntries");
		p[531] = GetProcAddress(hL,"GetSystemPaletteUse");
		p[532] = GetProcAddress(hL,"GetTextAlign");
		p[533] = GetProcAddress(hL,"GetTextCharacterExtra");
		p[534] = GetProcAddress(hL,"GetTextCharset");
		p[535] = GetProcAddress(hL,"GetTextCharsetInfo");
		p[536] = GetProcAddress(hL,"GetTextColor");
		p[537] = GetProcAddress(hL,"GetTextExtentExPointA");
		p[538] = GetProcAddress(hL,"GetTextExtentExPointI");
		p[539] = GetProcAddress(hL,"GetTextExtentExPointW");
		p[540] = GetProcAddress(hL,"GetTextExtentExPointWPri");
		p[541] = GetProcAddress(hL,"GetTextExtentPoint32A");
		p[542] = GetProcAddress(hL,"GetTextExtentPoint32W");
		p[543] = GetProcAddress(hL,"GetTextExtentPointA");
		p[544] = GetProcAddress(hL,"GetTextExtentPointI");
		p[545] = GetProcAddress(hL,"GetTextExtentPointW");
		p[546] = GetProcAddress(hL,"GetTextFaceA");
		p[547] = GetProcAddress(hL,"GetTextFaceAliasW");
		p[548] = GetProcAddress(hL,"GetTextFaceW");
		p[549] = GetProcAddress(hL,"GetTextMetricsA");
		p[550] = GetProcAddress(hL,"GetTextMetricsW");
		p[551] = GetProcAddress(hL,"GetTransform");
		p[552] = GetProcAddress(hL,"GetViewportExtEx");
		p[553] = GetProcAddress(hL,"GetViewportOrgEx");
		p[554] = GetProcAddress(hL,"GetWinMetaFileBits");
		p[555] = GetProcAddress(hL,"GetWindowExtEx");
		p[556] = GetProcAddress(hL,"GetWindowOrgEx");
		p[557] = GetProcAddress(hL,"GetWorldTransform");
		p[558] = GetProcAddress(hL,"HT_Get8BPPFormatPalette");
		p[559] = GetProcAddress(hL,"HT_Get8BPPMaskPalette");
		p[560] = GetProcAddress(hL,"IntersectClipRect");
		p[561] = GetProcAddress(hL,"InvertRgn");
		p[562] = GetProcAddress(hL,"IsValidEnhMetaRecord");
		p[563] = GetProcAddress(hL,"IsValidEnhMetaRecordOffExt");
		p[564] = GetProcAddress(hL,"LPtoDP");
		p[565] = GetProcAddress(hL,"LineDDA");
		p[566] = GetProcAddress(hL,"LineTo");
		p[567] = GetProcAddress(hL,"MaskBlt");
		p[568] = GetProcAddress(hL,"MirrorRgn");
		p[569] = GetProcAddress(hL,"ModifyWorldTransform");
		p[570] = GetProcAddress(hL,"MoveToEx");
		p[571] = GetProcAddress(hL,"NamedEscape");
		p[572] = GetProcAddress(hL,"OffsetClipRgn");
		p[573] = GetProcAddress(hL,"OffsetRgn");
		p[574] = GetProcAddress(hL,"OffsetViewportOrgEx");
		p[575] = GetProcAddress(hL,"OffsetWindowOrgEx");
		p[576] = GetProcAddress(hL,"PATHOBJ_bEnum");
		p[577] = GetProcAddress(hL,"PATHOBJ_bEnumClipLines");
		p[578] = GetProcAddress(hL,"PATHOBJ_vEnumStart");
		p[579] = GetProcAddress(hL,"PATHOBJ_vEnumStartClipLines");
		p[580] = GetProcAddress(hL,"PATHOBJ_vGetBounds");
		p[581] = GetProcAddress(hL,"PaintRgn");
		p[582] = GetProcAddress(hL,"PatBlt");
		p[583] = GetProcAddress(hL,"PathToRegion");
		p[584] = GetProcAddress(hL,"Pie");
		p[585] = GetProcAddress(hL,"PlayEnhMetaFile");
		p[586] = GetProcAddress(hL,"PlayEnhMetaFileRecord");
		p[587] = GetProcAddress(hL,"PlayMetaFile");
		p[588] = GetProcAddress(hL,"PlayMetaFileRecord");
		p[589] = GetProcAddress(hL,"PlgBlt");
		p[590] = GetProcAddress(hL,"PolyBezier");
		p[591] = GetProcAddress(hL,"PolyBezierTo");
		p[592] = GetProcAddress(hL,"PolyDraw");
		p[593] = GetProcAddress(hL,"PolyPatBlt");
		p[594] = GetProcAddress(hL,"PolyPolygon");
		p[595] = GetProcAddress(hL,"PolyPolyline");
		p[596] = GetProcAddress(hL,"PolyTextOutA");
		p[597] = GetProcAddress(hL,"PolyTextOutW");
		p[598] = GetProcAddress(hL,"Polygon");
		p[599] = GetProcAddress(hL,"Polyline");
		p[600] = GetProcAddress(hL,"PolylineTo");
		p[601] = GetProcAddress(hL,"PtInRegion");
		p[602] = GetProcAddress(hL,"PtVisible");
		p[603] = GetProcAddress(hL,"QueryFontAssocStatus");
		p[604] = GetProcAddress(hL,"RealizePalette");
		p[605] = GetProcAddress(hL,"RectInRegion");
		p[606] = GetProcAddress(hL,"RectVisible");
		p[607] = GetProcAddress(hL,"Rectangle");
		p[608] = GetProcAddress(hL,"RemoveFontMemResourceEx");
		p[609] = GetProcAddress(hL,"RemoveFontResourceA");
		p[610] = GetProcAddress(hL,"RemoveFontResourceExA");
		p[611] = GetProcAddress(hL,"RemoveFontResourceExW");
		p[612] = GetProcAddress(hL,"RemoveFontResourceTracking");
		p[613] = GetProcAddress(hL,"RemoveFontResourceW");
		p[614] = GetProcAddress(hL,"ResetDCA");
		p[615] = GetProcAddress(hL,"ResetDCW");
		p[616] = GetProcAddress(hL,"ResizePalette");
		p[617] = GetProcAddress(hL,"RestoreDC");
		p[618] = GetProcAddress(hL,"RoundRect");
		p[619] = GetProcAddress(hL,"STROBJ_bEnum");
		p[620] = GetProcAddress(hL,"STROBJ_bEnumPositionsOnly");
		p[621] = GetProcAddress(hL,"STROBJ_bGetAdvanceWidths");
		p[622] = GetProcAddress(hL,"STROBJ_dwGetCodePage");
		p[623] = GetProcAddress(hL,"STROBJ_vEnumStart");
		p[624] = GetProcAddress(hL,"SaveDC");
		p[625] = GetProcAddress(hL,"ScaleViewportExtEx");
		p[626] = GetProcAddress(hL,"ScaleWindowExtEx");
		p[627] = GetProcAddress(hL,"SelectBrushLocal");
		p[628] = GetProcAddress(hL,"SelectClipPath");
		p[629] = GetProcAddress(hL,"SelectClipRgn");
		p[630] = GetProcAddress(hL,"SelectFontLocal");
		p[631] = GetProcAddress(hL,"SelectObject");
		p[632] = GetProcAddress(hL,"SelectPalette");
		p[633] = GetProcAddress(hL,"SetAbortProc");
		p[634] = GetProcAddress(hL,"SetArcDirection");
		p[635] = GetProcAddress(hL,"SetBitmapAttributes");
		p[636] = GetProcAddress(hL,"SetBitmapBits");
		p[637] = GetProcAddress(hL,"SetBitmapDimensionEx");
		p[638] = GetProcAddress(hL,"SetBkColor");
		p[639] = GetProcAddress(hL,"SetBkMode");
		p[640] = GetProcAddress(hL,"SetBoundsRect");
		p[641] = GetProcAddress(hL,"SetBrushAttributes");
		p[642] = GetProcAddress(hL,"SetBrushOrgEx");
		p[643] = GetProcAddress(hL,"SetColorAdjustment");
		p[644] = GetProcAddress(hL,"SetColorSpace");
		p[645] = GetProcAddress(hL,"SetDCBrushColor");
		p[646] = GetProcAddress(hL,"SetDCPenColor");
		p[647] = GetProcAddress(hL,"SetDIBColorTable");
		p[648] = GetProcAddress(hL,"SetDIBits");
		p[649] = GetProcAddress(hL,"SetDIBitsToDevice");
		p[650] = GetProcAddress(hL,"SetDeviceGammaRamp");
		p[651] = GetProcAddress(hL,"SetEnhMetaFileBits");
		p[652] = GetProcAddress(hL,"SetFontEnumeration");
		p[653] = GetProcAddress(hL,"SetGraphicsMode");
		p[654] = GetProcAddress(hL,"SetICMMode");
		p[655] = GetProcAddress(hL,"SetICMProfileA");
		p[656] = GetProcAddress(hL,"SetICMProfileW");
		p[657] = GetProcAddress(hL,"SetLayout");
		p[658] = GetProcAddress(hL,"SetLayoutWidth");
		p[659] = GetProcAddress(hL,"SetMagicColors");
		p[660] = GetProcAddress(hL,"SetMapMode");
		p[661] = GetProcAddress(hL,"SetMapperFlags");
		p[662] = GetProcAddress(hL,"SetMetaFileBitsEx");
		p[663] = GetProcAddress(hL,"SetMetaRgn");
		p[664] = GetProcAddress(hL,"SetMiterLimit");
		p[665] = GetProcAddress(hL,"SetOPMSigningKeyAndSequenceNumbers");
		p[666] = GetProcAddress(hL,"SetPaletteEntries");
		p[667] = GetProcAddress(hL,"SetPixel");
		p[668] = GetProcAddress(hL,"SetPixelFormat");
		p[669] = GetProcAddress(hL,"SetPixelV");
		p[670] = GetProcAddress(hL,"SetPolyFillMode");
		p[671] = GetProcAddress(hL,"SetROP2");
		p[672] = GetProcAddress(hL,"SetRectRgn");
		p[673] = GetProcAddress(hL,"SetRelAbs");
		p[674] = GetProcAddress(hL,"SetStretchBltMode");
		p[675] = GetProcAddress(hL,"SetSystemPaletteUse");
		p[676] = GetProcAddress(hL,"SetTextAlign");
		p[677] = GetProcAddress(hL,"SetTextCharacterExtra");
		p[678] = GetProcAddress(hL,"SetTextColor");
		p[679] = GetProcAddress(hL,"SetTextJustification");
		p[680] = GetProcAddress(hL,"SetViewportExtEx");
		p[681] = GetProcAddress(hL,"SetViewportOrgEx");
		p[682] = GetProcAddress(hL,"SetVirtualResolution");
		p[683] = GetProcAddress(hL,"SetWinMetaFileBits");
		p[684] = GetProcAddress(hL,"SetWindowExtEx");
		p[685] = GetProcAddress(hL,"SetWindowOrgEx");
		p[686] = GetProcAddress(hL,"SetWorldTransform");
		p[687] = GetProcAddress(hL,"StartDocA");
		p[688] = GetProcAddress(hL,"StartDocW");
		p[689] = GetProcAddress(hL,"StartFormPage");
		p[690] = GetProcAddress(hL,"StartPage");
		p[691] = GetProcAddress(hL,"StretchBlt");
		p[692] = GetProcAddress(hL,"StretchDIBits");
		p[693] = GetProcAddress(hL,"StrokeAndFillPath");
		p[694] = GetProcAddress(hL,"StrokePath");
		p[695] = GetProcAddress(hL,"SwapBuffers");
		p[696] = GetProcAddress(hL,"TextOutA");
		p[697] = GetProcAddress(hL,"TextOutW");
		p[698] = GetProcAddress(hL,"TranslateCharsetInfo");
		p[699] = GetProcAddress(hL,"UnloadNetworkFonts");
		p[700] = GetProcAddress(hL,"UnrealizeObject");
		p[701] = GetProcAddress(hL,"UpdateColors");
		p[702] = GetProcAddress(hL,"UpdateICMRegKeyA");
		p[703] = GetProcAddress(hL,"UpdateICMRegKeyW");
		p[704] = GetProcAddress(hL,"WidenPath");
		p[705] = GetProcAddress(hL,"XFORMOBJ_bApplyXform");
		p[706] = GetProcAddress(hL,"XFORMOBJ_iGetXform");
		p[707] = GetProcAddress(hL,"XLATEOBJ_cGetPalette");
		p[708] = GetProcAddress(hL,"XLATEOBJ_hGetColorTransform");
		p[709] = GetProcAddress(hL,"XLATEOBJ_iXlate");
		p[710] = GetProcAddress(hL,"XLATEOBJ_piVector");
		p[711] = GetProcAddress(hL,"bInitSystemAndFontsDirectoriesW");
		p[712] = GetProcAddress(hL,"bMakePathNameW");
		p[713] = GetProcAddress(hL,"cGetTTFFromFOT");
		p[714] = GetProcAddress(hL,"gdiPlaySpoolStream");
		p[715] = GetProcAddress(hL,(LPCSTR)"1000");
		p[716] = GetProcAddress(hL,(LPCSTR)"1001");
		p[717] = GetProcAddress(hL,(LPCSTR)"1002");
		p[718] = GetProcAddress(hL,(LPCSTR)"1003");
		p[719] = GetProcAddress(hL,(LPCSTR)"1004");
		p[720] = GetProcAddress(hL,(LPCSTR)"1005");
		p[721] = GetProcAddress(hL,(LPCSTR)"1006");
		p[722] = GetProcAddress(hL,(LPCSTR)"1007");
		p[723] = GetProcAddress(hL,(LPCSTR)"1008");
		p[724] = GetProcAddress(hL,(LPCSTR)"1009");
		p[725] = GetProcAddress(hL,(LPCSTR)"1010");
		p[726] = GetProcAddress(hL,(LPCSTR)"1011");


		}
	if (reason == DLL_PROCESS_DETACH)
		{
		FreeLibrary(hL);
		}

	return 1;
}

// AbortDoc
extern "C" __declspec(naked) void __stdcall __E__0__()
{
	log("AbortDoc");
	__asm
	{
		jmp p[0 * 4];
	}
}

// AbortPath
extern "C" __declspec(naked) void __stdcall __E__1__()
{
	log("AbortPath");
	__asm
	{
		jmp p[1 * 4];
	}
}

// AddFontMemResourceEx
extern "C" __declspec(naked) void __stdcall __E__2__()
{
	log("AddFontMemResourceEx");
	__asm
	{
		jmp p[2 * 4];
	}
}

// AddFontResourceA
extern "C" __declspec(naked) void __stdcall __E__3__()
{
	log("AddFontResourceA");
	__asm
	{
		jmp p[3 * 4];
	}
}

// AddFontResourceExA
extern "C" __declspec(naked) void __stdcall __E__4__()
{
	log("AddFontResourceExA");
	__asm
	{
		jmp p[4 * 4];
	}
}

// AddFontResourceExW
extern "C" __declspec(naked) void __stdcall __E__5__()
{
	log("AddFontResourceExW");
	__asm
	{
		jmp p[5 * 4];
	}
}

// AddFontResourceTracking
extern "C" __declspec(naked) void __stdcall __E__6__()
{
	log("AddFontResourceTracking");
	__asm
	{
		jmp p[6 * 4];
	}
}

// AddFontResourceW
extern "C" __declspec(naked) void __stdcall __E__7__()
{
	log("AddFontResourceW");
	__asm
	{
		jmp p[7 * 4];
	}
}

// AngleArc
extern "C" __declspec(naked) void __stdcall __E__8__()
{
	log("AngleArc");
	__asm
	{
		jmp p[8 * 4];
	}
}

// AnimatePalette
extern "C" __declspec(naked) void __stdcall __E__9__()
{
	log("AnimatePalette");
	__asm
	{
		jmp p[9 * 4];
	}
}

// AnyLinkedFonts
extern "C" __declspec(naked) void __stdcall __E__10__()
{
	log("AnyLinkedFonts");
	__asm
	{
		jmp p[10 * 4];
	}
}

// Arc
extern "C" __declspec(naked) void __stdcall __E__11__()
{
	log("Arc");
	__asm
	{
		jmp p[11 * 4];
	}
}

// ArcTo
extern "C" __declspec(naked) void __stdcall __E__12__()
{
	log("ArcTo");
	__asm
	{
		jmp p[12 * 4];
	}
}

// BRUSHOBJ_hGetColorTransform
extern "C" __declspec(naked) void __stdcall __E__13__()
{
	log("BRUSHOBJ_hGetColorTransform");
	__asm
	{
		jmp p[13 * 4];
	}
}

// BRUSHOBJ_pvAllocRbrush
extern "C" __declspec(naked) void __stdcall __E__14__()
{
	log("BRUSHOBJ_pvAllocRbrush");
	__asm
	{
		jmp p[14 * 4];
	}
}

// BRUSHOBJ_pvGetRbrush
extern "C" __declspec(naked) void __stdcall __E__15__()
{
	log("BRUSHOBJ_pvGetRbrush");
	__asm
	{
		jmp p[15 * 4];
	}
}

// BRUSHOBJ_ulGetBrushColor
extern "C" __declspec(naked) void __stdcall __E__16__()
{
	log("BRUSHOBJ_ulGetBrushColor");
	__asm
	{
		jmp p[16 * 4];
	}
}

// BeginGdiRendering
extern "C" __declspec(naked) void __stdcall __E__17__()
{
	log("BeginGdiRendering");
	__asm
	{
		jmp p[17 * 4];
	}
}

// BeginPath
extern "C" __declspec(naked) void __stdcall __E__18__()
{
	log("BeginPath");
	__asm
	{
		jmp p[18 * 4];
	}
}

// BitBlt
extern "C" __declspec(naked) void __stdcall __E__19__()
{
	log("BitBlt");
	__asm
	{
		jmp p[19 * 4];
	}
}

// CLIPOBJ_bEnum
extern "C" __declspec(naked) void __stdcall __E__20__()
{
	log("CLIPOBJ_bEnum");
	__asm
	{
		jmp p[20 * 4];
	}
}

// CLIPOBJ_cEnumStart
extern "C" __declspec(naked) void __stdcall __E__21__()
{
	log("CLIPOBJ_cEnumStart");
	__asm
	{
		jmp p[21 * 4];
	}
}

// CLIPOBJ_ppoGetPath
extern "C" __declspec(naked) void __stdcall __E__22__()
{
	log("CLIPOBJ_ppoGetPath");
	__asm
	{
		jmp p[22 * 4];
	}
}

// CancelDC
extern "C" __declspec(naked) void __stdcall __E__23__()
{
	log("CancelDC");
	__asm
	{
		jmp p[23 * 4];
	}
}

// CheckColorsInGamut
extern "C" __declspec(naked) void __stdcall __E__24__()
{
	log("CheckColorsInGamut");
	__asm
	{
		jmp p[24 * 4];
	}
}

// ChoosePixelFormat
extern "C" __declspec(naked) void __stdcall __E__25__()
{
	log("ChoosePixelFormat");
	__asm
	{
		jmp p[25 * 4];
	}
}

// Chord
extern "C" __declspec(naked) void __stdcall __E__26__()
{
	log("Chord");
	__asm
	{
		jmp p[26 * 4];
	}
}

// ClearBitmapAttributes
extern "C" __declspec(naked) void __stdcall __E__27__()
{
	log("ClearBitmapAttributes");
	__asm
	{
		jmp p[27 * 4];
	}
}

// ClearBrushAttributes
extern "C" __declspec(naked) void __stdcall __E__28__()
{
	log("ClearBrushAttributes");
	__asm
	{
		jmp p[28 * 4];
	}
}

// CloseEnhMetaFile
extern "C" __declspec(naked) void __stdcall __E__29__()
{
	log("CloseEnhMetaFile");
	__asm
	{
		jmp p[29 * 4];
	}
}

// CloseFigure
extern "C" __declspec(naked) void __stdcall __E__30__()
{
	log("CloseFigure");
	__asm
	{
		jmp p[30 * 4];
	}
}

// CloseMetaFile
extern "C" __declspec(naked) void __stdcall __E__31__()
{
	log("CloseMetaFile");
	__asm
	{
		jmp p[31 * 4];
	}
}

// ColorCorrectPalette
extern "C" __declspec(naked) void __stdcall __E__32__()
{
	log("ColorCorrectPalette");
	__asm
	{
		jmp p[32 * 4];
	}
}

// ColorMatchToTarget
extern "C" __declspec(naked) void __stdcall __E__33__()
{
	log("ColorMatchToTarget");
	__asm
	{
		jmp p[33 * 4];
	}
}

// CombineRgn
extern "C" __declspec(naked) void __stdcall __E__34__()
{
	log("CombineRgn");
	__asm
	{
		jmp p[34 * 4];
	}
}

// CombineTransform
extern "C" __declspec(naked) void __stdcall __E__35__()
{
	log("CombineTransform");
	__asm
	{
		jmp p[35 * 4];
	}
}

// ConfigureOPMProtectedOutput
extern "C" __declspec(naked) void __stdcall __E__36__()
{
	log("ConfigureOPMProtectedOutput");
	__asm
	{
		jmp p[36 * 4];
	}
}

// CopyEnhMetaFileA
extern "C" __declspec(naked) void __stdcall __E__37__()
{
	log("CopyEnhMetaFileA");
	__asm
	{
		jmp p[37 * 4];
	}
}

// CopyEnhMetaFileW
extern "C" __declspec(naked) void __stdcall __E__38__()
{
	log("CopyEnhMetaFileW");
	__asm
	{
		jmp p[38 * 4];
	}
}

// CopyMetaFileA
extern "C" __declspec(naked) void __stdcall __E__39__()
{
	log("CopyMetaFileA");
	__asm
	{
		jmp p[39 * 4];
	}
}

// CopyMetaFileW
extern "C" __declspec(naked) void __stdcall __E__40__()
{
	log("CopyMetaFileW");
	__asm
	{
		jmp p[40 * 4];
	}
}

// CreateBitmap
extern "C" __declspec(naked) void __stdcall __E__41__()
{
	log("CreateBitmap");
	__asm
	{
		jmp p[41 * 4];
	}
}

// CreateBitmapFromDxSurface
extern "C" __declspec(naked) void __stdcall __E__42__()
{
	log("CreateBitmapFromDxSurface");
	__asm
	{
		jmp p[42 * 4];
	}
}

// CreateBitmapIndirect
extern "C" __declspec(naked) void __stdcall __E__43__()
{
	log("CreateBitmapIndirect");
	__asm
	{
		jmp p[43 * 4];
	}
}

// CreateBrushIndirect
extern "C" __declspec(naked) void __stdcall __E__44__()
{
	log("CreateBrushIndirect");
	__asm
	{
		jmp p[44 * 4];
	}
}

// CreateColorSpaceA
extern "C" __declspec(naked) void __stdcall __E__45__()
{
	log("CreateColorSpaceA");
	__asm
	{
		jmp p[45 * 4];
	}
}

// CreateColorSpaceW
extern "C" __declspec(naked) void __stdcall __E__46__()
{
	log("CreateColorSpaceW");
	__asm
	{
		jmp p[46 * 4];
	}
}

// CreateCompatibleBitmap
extern "C" __declspec(naked) void __stdcall __E__47__()
{
	log("CreateCompatibleBitmap");
	__asm
	{
		jmp p[47 * 4];
	}
}

// CreateCompatibleDC
extern "C" __declspec(naked) void __stdcall __E__48__()
{
	log("CreateCompatibleDC");
	__asm
	{
		jmp p[48 * 4];
	}
}

// CreateDCA
extern "C" __declspec(naked) void __stdcall __E__49__()
{
	log("CreateDCA");
	__asm
	{
		jmp p[49 * 4];
	}
}

// CreateDCW
extern "C" __declspec(naked) void __stdcall __E__50__()
{
	log("CreateDCW");
	__asm
	{
		jmp p[50 * 4];
	}
}

// CreateDIBPatternBrush
extern "C" __declspec(naked) void __stdcall __E__51__()
{
	log("CreateDIBPatternBrush");
	__asm
	{
		jmp p[51 * 4];
	}
}

// CreateDIBPatternBrushPt
extern "C" __declspec(naked) void __stdcall __E__52__()
{
	log("CreateDIBPatternBrushPt");
	__asm
	{
		jmp p[52 * 4];
	}
}

// CreateDIBSection
extern "C" __declspec(naked) void __stdcall __E__53__()
{
	log("CreateDIBSection");
	__asm
	{
		jmp p[53 * 4];
	}
}

// CreateDIBitmap
extern "C" __declspec(naked) void __stdcall __E__54__()
{
	log("CreateDIBitmap");
	__asm
	{
		jmp p[54 * 4];
	}
}

// CreateDiscardableBitmap
extern "C" __declspec(naked) void __stdcall __E__55__()
{
	log("CreateDiscardableBitmap");
	__asm
	{
		jmp p[55 * 4];
	}
}

// CreateEllipticRgn
extern "C" __declspec(naked) void __stdcall __E__56__()
{
	log("CreateEllipticRgn");
	__asm
	{
		jmp p[56 * 4];
	}
}

// CreateEllipticRgnIndirect
extern "C" __declspec(naked) void __stdcall __E__57__()
{
	log("CreateEllipticRgnIndirect");
	__asm
	{
		jmp p[57 * 4];
	}
}

// CreateEnhMetaFileA
extern "C" __declspec(naked) void __stdcall __E__58__()
{
	log("CreateEnhMetaFileA");
	__asm
	{
		jmp p[58 * 4];
	}
}

// CreateEnhMetaFileW
extern "C" __declspec(naked) void __stdcall __E__59__()
{
	log("CreateEnhMetaFileW");
	__asm
	{
		jmp p[59 * 4];
	}
}

// CreateFontA
extern "C" __declspec(naked) void __stdcall __E__60__()
{
	log2("CreateFontA");
	__asm
	{
		jmp p[60 * 4];
	}
}

// CreateFontIndirectA
extern "C" __declspec(naked) void __stdcall __E__61__()
{
	log2("CreateFontIndirectA");
	__asm
	{
		jmp p[61 * 4];
	}
}

// CreateFontIndirectExA
extern "C" __declspec(naked) void __stdcall __E__62__()
{
	log2("CreateFontIndirectExA");
	__asm
	{
		jmp p[62 * 4];
	}
}

// CreateFontIndirectExW
extern "C" __declspec(naked) void __stdcall __E__63__()
{
	log2("CreateFontIndirectExW");
	__asm
	{
		jmp p[63 * 4];
	}
}

// CreateFontIndirectW
extern "C" __declspec(naked) void __stdcall __E__64__()
{
	log2("CreateFontIndirectW");
	__asm
	{
		jmp p[64 * 4];
	}
}

// CreateFontW
extern "C" __declspec(naked) void __stdcall __E__65__()
{
	log2("CreateFontW");
	__asm
	{
		jmp p[65 * 4];
	}
}

// CreateHalftonePalette
extern "C" __declspec(naked) void __stdcall __E__66__()
{
	log("CreateHalftonePalette");
	__asm
	{
		jmp p[66 * 4];
	}
}

// CreateHatchBrush
extern "C" __declspec(naked) void __stdcall __E__67__()
{
	log("CreateHatchBrush");
	__asm
	{
		jmp p[67 * 4];
	}
}

// CreateICA
extern "C" __declspec(naked) void __stdcall __E__68__()
{
	log("CreateICA");
	__asm
	{
		jmp p[68 * 4];
	}
}

// CreateICW
extern "C" __declspec(naked) void __stdcall __E__69__()
{
	log("CreateICW");
	__asm
	{
		jmp p[69 * 4];
	}
}

// CreateMetaFileA
extern "C" __declspec(naked) void __stdcall __E__70__()
{
	log("CreateMetaFileA");
	__asm
	{
		jmp p[70 * 4];
	}
}

// CreateMetaFileW
extern "C" __declspec(naked) void __stdcall __E__71__()
{
	log("CreateMetaFileW");
	__asm
	{
		jmp p[71 * 4];
	}
}

// CreateOPMProtectedOutputs
extern "C" __declspec(naked) void __stdcall __E__72__()
{
	log("CreateOPMProtectedOutputs");
	__asm
	{
		jmp p[72 * 4];
	}
}

// CreatePalette
extern "C" __declspec(naked) void __stdcall __E__73__()
{
	log("CreatePalette");
	__asm
	{
		jmp p[73 * 4];
	}
}

// CreatePatternBrush
extern "C" __declspec(naked) void __stdcall __E__74__()
{
	log("CreatePatternBrush");
	__asm
	{
		jmp p[74 * 4];
	}
}

// CreatePen
extern "C" __declspec(naked) void __stdcall __E__75__()
{
	log("CreatePen");
	__asm
	{
		jmp p[75 * 4];
	}
}

// CreatePenIndirect
extern "C" __declspec(naked) void __stdcall __E__76__()
{
	log("CreatePenIndirect");
	__asm
	{
		jmp p[76 * 4];
	}
}

// CreatePolyPolygonRgn
extern "C" __declspec(naked) void __stdcall __E__77__()
{
	log("CreatePolyPolygonRgn");
	__asm
	{
		jmp p[77 * 4];
	}
}

// CreatePolygonRgn
extern "C" __declspec(naked) void __stdcall __E__78__()
{
	log("CreatePolygonRgn");
	__asm
	{
		jmp p[78 * 4];
	}
}

// CreateRectRgn
extern "C" __declspec(naked) void __stdcall __E__79__()
{
	log("CreateRectRgn");
	__asm
	{
		jmp p[79 * 4];
	}
}

// CreateRectRgnIndirect
extern "C" __declspec(naked) void __stdcall __E__80__()
{
	log("CreateRectRgnIndirect");
	__asm
	{
		jmp p[80 * 4];
	}
}

// CreateRoundRectRgn
extern "C" __declspec(naked) void __stdcall __E__81__()
{
	log("CreateRoundRectRgn");
	__asm
	{
		jmp p[81 * 4];
	}
}

// CreateScalableFontResourceA
extern "C" __declspec(naked) void __stdcall __E__82__()
{
	log("CreateScalableFontResourceA");
	__asm
	{
		jmp p[82 * 4];
	}
}

// CreateScalableFontResourceW
extern "C" __declspec(naked) void __stdcall __E__83__()
{
	log("CreateScalableFontResourceW");
	__asm
	{
		jmp p[83 * 4];
	}
}

// CreateSolidBrush
extern "C" __declspec(naked) void __stdcall __E__84__()
{
	log("CreateSolidBrush");
	__asm
	{
		jmp p[84 * 4];
	}
}

// D3DKMTAcquireKeyedMutex
extern "C" __declspec(naked) void __stdcall __E__85__()
{
	log("D3DKMTAcquireKeyedMutex");
	__asm
	{
		jmp p[85 * 4];
	}
}

// D3DKMTCheckExclusiveOwnership
extern "C" __declspec(naked) void __stdcall __E__86__()
{
	log("D3DKMTCheckExclusiveOwnership");
	__asm
	{
		jmp p[86 * 4];
	}
}

// D3DKMTCheckMonitorPowerState
extern "C" __declspec(naked) void __stdcall __E__87__()
{
	log("D3DKMTCheckMonitorPowerState");
	__asm
	{
		jmp p[87 * 4];
	}
}

// D3DKMTCheckOcclusion
extern "C" __declspec(naked) void __stdcall __E__88__()
{
	log("D3DKMTCheckOcclusion");
	__asm
	{
		jmp p[88 * 4];
	}
}

// D3DKMTCheckSharedResourceAccess
extern "C" __declspec(naked) void __stdcall __E__89__()
{
	log("D3DKMTCheckSharedResourceAccess");
	__asm
	{
		jmp p[89 * 4];
	}
}

// D3DKMTCheckVidPnExclusiveOwnership
extern "C" __declspec(naked) void __stdcall __E__90__()
{
	log("D3DKMTCheckVidPnExclusiveOwnership");
	__asm
	{
		jmp p[90 * 4];
	}
}

// D3DKMTCloseAdapter
extern "C" __declspec(naked) void __stdcall __E__91__()
{
	log("D3DKMTCloseAdapter");
	__asm
	{
		jmp p[91 * 4];
	}
}

// D3DKMTConfigureSharedResource
extern "C" __declspec(naked) void __stdcall __E__92__()
{
	log("D3DKMTConfigureSharedResource");
	__asm
	{
		jmp p[92 * 4];
	}
}

// D3DKMTCreateAllocation
extern "C" __declspec(naked) void __stdcall __E__93__()
{
	log("D3DKMTCreateAllocation");
	__asm
	{
		jmp p[93 * 4];
	}
}

// D3DKMTCreateAllocation2
extern "C" __declspec(naked) void __stdcall __E__94__()
{
	log("D3DKMTCreateAllocation2");
	__asm
	{
		jmp p[94 * 4];
	}
}

// D3DKMTCreateContext
extern "C" __declspec(naked) void __stdcall __E__95__()
{
	log("D3DKMTCreateContext");
	__asm
	{
		jmp p[95 * 4];
	}
}

// D3DKMTCreateDCFromMemory
extern "C" __declspec(naked) void __stdcall __E__96__()
{
	log("D3DKMTCreateDCFromMemory");
	__asm
	{
		jmp p[96 * 4];
	}
}

// D3DKMTCreateDevice
extern "C" __declspec(naked) void __stdcall __E__97__()
{
	log("D3DKMTCreateDevice");
	__asm
	{
		jmp p[97 * 4];
	}
}

// D3DKMTCreateKeyedMutex
extern "C" __declspec(naked) void __stdcall __E__98__()
{
	log("D3DKMTCreateKeyedMutex");
	__asm
	{
		jmp p[98 * 4];
	}
}

// D3DKMTCreateOverlay
extern "C" __declspec(naked) void __stdcall __E__99__()
{
	log("D3DKMTCreateOverlay");
	__asm
	{
		jmp p[99 * 4];
	}
}

// D3DKMTCreateSynchronizationObject
extern "C" __declspec(naked) void __stdcall __E__100__()
{
	log("D3DKMTCreateSynchronizationObject");
	__asm
	{
		jmp p[100 * 4];
	}
}

// D3DKMTCreateSynchronizationObject2
extern "C" __declspec(naked) void __stdcall __E__101__()
{
	log("D3DKMTCreateSynchronizationObject2");
	__asm
	{
		jmp p[101 * 4];
	}
}

// D3DKMTDestroyAllocation
extern "C" __declspec(naked) void __stdcall __E__102__()
{
	log("D3DKMTDestroyAllocation");
	__asm
	{
		jmp p[102 * 4];
	}
}

// D3DKMTDestroyContext
extern "C" __declspec(naked) void __stdcall __E__103__()
{
	log("D3DKMTDestroyContext");
	__asm
	{
		jmp p[103 * 4];
	}
}

// D3DKMTDestroyDCFromMemory
extern "C" __declspec(naked) void __stdcall __E__104__()
{
	log("D3DKMTDestroyDCFromMemory");
	__asm
	{
		jmp p[104 * 4];
	}
}

// D3DKMTDestroyDevice
extern "C" __declspec(naked) void __stdcall __E__105__()
{
	log("D3DKMTDestroyDevice");
	__asm
	{
		jmp p[105 * 4];
	}
}

// D3DKMTDestroyKeyedMutex
extern "C" __declspec(naked) void __stdcall __E__106__()
{
	log("D3DKMTDestroyKeyedMutex");
	__asm
	{
		jmp p[106 * 4];
	}
}

// D3DKMTDestroyOverlay
extern "C" __declspec(naked) void __stdcall __E__107__()
{
	log("D3DKMTDestroyOverlay");
	__asm
	{
		jmp p[107 * 4];
	}
}

// D3DKMTDestroySynchronizationObject
extern "C" __declspec(naked) void __stdcall __E__108__()
{
	log("D3DKMTDestroySynchronizationObject");
	__asm
	{
		jmp p[108 * 4];
	}
}

// D3DKMTEscape
extern "C" __declspec(naked) void __stdcall __E__109__()
{
	log("D3DKMTEscape");
	__asm
	{
		jmp p[109 * 4];
	}
}

// D3DKMTFlipOverlay
extern "C" __declspec(naked) void __stdcall __E__110__()
{
	log("D3DKMTFlipOverlay");
	__asm
	{
		jmp p[110 * 4];
	}
}

// D3DKMTGetContextSchedulingPriority
extern "C" __declspec(naked) void __stdcall __E__111__()
{
	log("D3DKMTGetContextSchedulingPriority");
	__asm
	{
		jmp p[111 * 4];
	}
}

// D3DKMTGetDeviceState
extern "C" __declspec(naked) void __stdcall __E__112__()
{
	log("D3DKMTGetDeviceState");
	__asm
	{
		jmp p[112 * 4];
	}
}

// D3DKMTGetDisplayModeList
extern "C" __declspec(naked) void __stdcall __E__113__()
{
	log("D3DKMTGetDisplayModeList");
	__asm
	{
		jmp p[113 * 4];
	}
}

// D3DKMTGetMultisampleMethodList
extern "C" __declspec(naked) void __stdcall __E__114__()
{
	log("D3DKMTGetMultisampleMethodList");
	__asm
	{
		jmp p[114 * 4];
	}
}

// D3DKMTGetOverlayState
extern "C" __declspec(naked) void __stdcall __E__115__()
{
	log("D3DKMTGetOverlayState");
	__asm
	{
		jmp p[115 * 4];
	}
}

// D3DKMTGetPresentHistory
extern "C" __declspec(naked) void __stdcall __E__116__()
{
	log("D3DKMTGetPresentHistory");
	__asm
	{
		jmp p[116 * 4];
	}
}

// D3DKMTGetPresentQueueEvent
extern "C" __declspec(naked) void __stdcall __E__117__()
{
	log("D3DKMTGetPresentQueueEvent");
	__asm
	{
		jmp p[117 * 4];
	}
}

// D3DKMTGetProcessSchedulingPriorityClass
extern "C" __declspec(naked) void __stdcall __E__118__()
{
	log("D3DKMTGetProcessSchedulingPriorityClass");
	__asm
	{
		jmp p[118 * 4];
	}
}

// D3DKMTGetRuntimeData
extern "C" __declspec(naked) void __stdcall __E__119__()
{
	log("D3DKMTGetRuntimeData");
	__asm
	{
		jmp p[119 * 4];
	}
}

// D3DKMTGetScanLine
extern "C" __declspec(naked) void __stdcall __E__120__()
{
	log("D3DKMTGetScanLine");
	__asm
	{
		jmp p[120 * 4];
	}
}

// D3DKMTGetSharedPrimaryHandle
extern "C" __declspec(naked) void __stdcall __E__121__()
{
	log("D3DKMTGetSharedPrimaryHandle");
	__asm
	{
		jmp p[121 * 4];
	}
}

// D3DKMTInvalidateActiveVidPn
extern "C" __declspec(naked) void __stdcall __E__122__()
{
	log("D3DKMTInvalidateActiveVidPn");
	__asm
	{
		jmp p[122 * 4];
	}
}

// D3DKMTLock
extern "C" __declspec(naked) void __stdcall __E__123__()
{
	log("D3DKMTLock");
	__asm
	{
		jmp p[123 * 4];
	}
}

// D3DKMTOpenAdapterFromDeviceName
extern "C" __declspec(naked) void __stdcall __E__124__()
{
	log("D3DKMTOpenAdapterFromDeviceName");
	__asm
	{
		jmp p[124 * 4];
	}
}

// D3DKMTOpenAdapterFromGdiDisplayName
extern "C" __declspec(naked) void __stdcall __E__125__()
{
	log("D3DKMTOpenAdapterFromGdiDisplayName");
	__asm
	{
		jmp p[125 * 4];
	}
}

// D3DKMTOpenAdapterFromHdc
extern "C" __declspec(naked) void __stdcall __E__126__()
{
	log("D3DKMTOpenAdapterFromHdc");
	__asm
	{
		jmp p[126 * 4];
	}
}

// D3DKMTOpenKeyedMutex
extern "C" __declspec(naked) void __stdcall __E__127__()
{
	log("D3DKMTOpenKeyedMutex");
	__asm
	{
		jmp p[127 * 4];
	}
}

// D3DKMTOpenResource
extern "C" __declspec(naked) void __stdcall __E__128__()
{
	log("D3DKMTOpenResource");
	__asm
	{
		jmp p[128 * 4];
	}
}

// D3DKMTOpenResource2
extern "C" __declspec(naked) void __stdcall __E__129__()
{
	log("D3DKMTOpenResource2");
	__asm
	{
		jmp p[129 * 4];
	}
}

// D3DKMTOpenSynchronizationObject
extern "C" __declspec(naked) void __stdcall __E__130__()
{
	log("D3DKMTOpenSynchronizationObject");
	__asm
	{
		jmp p[130 * 4];
	}
}

// D3DKMTPollDisplayChildren
extern "C" __declspec(naked) void __stdcall __E__131__()
{
	log("D3DKMTPollDisplayChildren");
	__asm
	{
		jmp p[131 * 4];
	}
}

// D3DKMTPresent
extern "C" __declspec(naked) void __stdcall __E__132__()
{
	log("D3DKMTPresent");
	__asm
	{
		jmp p[132 * 4];
	}
}

// D3DKMTQueryAdapterInfo
extern "C" __declspec(naked) void __stdcall __E__133__()
{
	log("D3DKMTQueryAdapterInfo");
	__asm
	{
		jmp p[133 * 4];
	}
}

// D3DKMTQueryAllocationResidency
extern "C" __declspec(naked) void __stdcall __E__134__()
{
	log("D3DKMTQueryAllocationResidency");
	__asm
	{
		jmp p[134 * 4];
	}
}

// D3DKMTQueryResourceInfo
extern "C" __declspec(naked) void __stdcall __E__135__()
{
	log("D3DKMTQueryResourceInfo");
	__asm
	{
		jmp p[135 * 4];
	}
}

// D3DKMTQueryStatistics
extern "C" __declspec(naked) void __stdcall __E__136__()
{
	log("D3DKMTQueryStatistics");
	__asm
	{
		jmp p[136 * 4];
	}
}

// D3DKMTReleaseKeyedMutex
extern "C" __declspec(naked) void __stdcall __E__137__()
{
	log("D3DKMTReleaseKeyedMutex");
	__asm
	{
		jmp p[137 * 4];
	}
}

// D3DKMTReleaseProcessVidPnSourceOwners
extern "C" __declspec(naked) void __stdcall __E__138__()
{
	log("D3DKMTReleaseProcessVidPnSourceOwners");
	__asm
	{
		jmp p[138 * 4];
	}
}

// D3DKMTRender
extern "C" __declspec(naked) void __stdcall __E__139__()
{
	log("D3DKMTRender");
	__asm
	{
		jmp p[139 * 4];
	}
}

// D3DKMTSetAllocationPriority
extern "C" __declspec(naked) void __stdcall __E__140__()
{
	log("D3DKMTSetAllocationPriority");
	__asm
	{
		jmp p[140 * 4];
	}
}

// D3DKMTSetContextSchedulingPriority
extern "C" __declspec(naked) void __stdcall __E__141__()
{
	log("D3DKMTSetContextSchedulingPriority");
	__asm
	{
		jmp p[141 * 4];
	}
}

// D3DKMTSetDisplayMode
extern "C" __declspec(naked) void __stdcall __E__142__()
{
	log("D3DKMTSetDisplayMode");
	__asm
	{
		jmp p[142 * 4];
	}
}

// D3DKMTSetDisplayPrivateDriverFormat
extern "C" __declspec(naked) void __stdcall __E__143__()
{
	log("D3DKMTSetDisplayPrivateDriverFormat");
	__asm
	{
		jmp p[143 * 4];
	}
}

// D3DKMTSetGammaRamp
extern "C" __declspec(naked) void __stdcall __E__144__()
{
	log("D3DKMTSetGammaRamp");
	__asm
	{
		jmp p[144 * 4];
	}
}

// D3DKMTSetProcessSchedulingPriorityClass
extern "C" __declspec(naked) void __stdcall __E__145__()
{
	log("D3DKMTSetProcessSchedulingPriorityClass");
	__asm
	{
		jmp p[145 * 4];
	}
}

// D3DKMTSetQueuedLimit
extern "C" __declspec(naked) void __stdcall __E__146__()
{
	log("D3DKMTSetQueuedLimit");
	__asm
	{
		jmp p[146 * 4];
	}
}

// D3DKMTSetVidPnSourceOwner
extern "C" __declspec(naked) void __stdcall __E__147__()
{
	log("D3DKMTSetVidPnSourceOwner");
	__asm
	{
		jmp p[147 * 4];
	}
}

// D3DKMTSharedPrimaryLockNotification
extern "C" __declspec(naked) void __stdcall __E__148__()
{
	log("D3DKMTSharedPrimaryLockNotification");
	__asm
	{
		jmp p[148 * 4];
	}
}

// D3DKMTSharedPrimaryUnLockNotification
extern "C" __declspec(naked) void __stdcall __E__149__()
{
	log("D3DKMTSharedPrimaryUnLockNotification");
	__asm
	{
		jmp p[149 * 4];
	}
}

// D3DKMTSignalSynchronizationObject
extern "C" __declspec(naked) void __stdcall __E__150__()
{
	log("D3DKMTSignalSynchronizationObject");
	__asm
	{
		jmp p[150 * 4];
	}
}

// D3DKMTSignalSynchronizationObject2
extern "C" __declspec(naked) void __stdcall __E__151__()
{
	log("D3DKMTSignalSynchronizationObject2");
	__asm
	{
		jmp p[151 * 4];
	}
}

// D3DKMTUnlock
extern "C" __declspec(naked) void __stdcall __E__152__()
{
	log("D3DKMTUnlock");
	__asm
	{
		jmp p[152 * 4];
	}
}

// D3DKMTUpdateOverlay
extern "C" __declspec(naked) void __stdcall __E__153__()
{
	log("D3DKMTUpdateOverlay");
	__asm
	{
		jmp p[153 * 4];
	}
}

// D3DKMTWaitForIdle
extern "C" __declspec(naked) void __stdcall __E__154__()
{
	log("D3DKMTWaitForIdle");
	__asm
	{
		jmp p[154 * 4];
	}
}

// D3DKMTWaitForSynchronizationObject
extern "C" __declspec(naked) void __stdcall __E__155__()
{
	log("D3DKMTWaitForSynchronizationObject");
	__asm
	{
		jmp p[155 * 4];
	}
}

// D3DKMTWaitForSynchronizationObject2
extern "C" __declspec(naked) void __stdcall __E__156__()
{
	log("D3DKMTWaitForSynchronizationObject2");
	__asm
	{
		jmp p[156 * 4];
	}
}

// D3DKMTWaitForVerticalBlankEvent
extern "C" __declspec(naked) void __stdcall __E__157__()
{
	log("D3DKMTWaitForVerticalBlankEvent");
	__asm
	{
		jmp p[157 * 4];
	}
}

// DDCCIGetCapabilitiesString
extern "C" __declspec(naked) void __stdcall __E__158__()
{
	log("DDCCIGetCapabilitiesString");
	__asm
	{
		jmp p[158 * 4];
	}
}

// DDCCIGetCapabilitiesStringLength
extern "C" __declspec(naked) void __stdcall __E__159__()
{
	log("DDCCIGetCapabilitiesStringLength");
	__asm
	{
		jmp p[159 * 4];
	}
}

// DDCCIGetTimingReport
extern "C" __declspec(naked) void __stdcall __E__160__()
{
	log("DDCCIGetTimingReport");
	__asm
	{
		jmp p[160 * 4];
	}
}

// DDCCIGetVCPFeature
extern "C" __declspec(naked) void __stdcall __E__161__()
{
	log("DDCCIGetVCPFeature");
	__asm
	{
		jmp p[161 * 4];
	}
}

// DDCCISaveCurrentSettings
extern "C" __declspec(naked) void __stdcall __E__162__()
{
	log("DDCCISaveCurrentSettings");
	__asm
	{
		jmp p[162 * 4];
	}
}

// DDCCISetVCPFeature
extern "C" __declspec(naked) void __stdcall __E__163__()
{
	log("DDCCISetVCPFeature");
	__asm
	{
		jmp p[163 * 4];
	}
}

// DPtoLP
extern "C" __declspec(naked) void __stdcall __E__164__()
{
	log("DPtoLP");
	__asm
	{
		jmp p[164 * 4];
	}
}

// DdCreateFullscreenSprite
extern "C" __declspec(naked) void __stdcall __E__165__()
{
	log("DdCreateFullscreenSprite");
	__asm
	{
		jmp p[165 * 4];
	}
}

// DdDestroyFullscreenSprite
extern "C" __declspec(naked) void __stdcall __E__166__()
{
	log("DdDestroyFullscreenSprite");
	__asm
	{
		jmp p[166 * 4];
	}
}

// DdEntry0
extern "C" __declspec(naked) void __stdcall __E__167__()
{
	log("DdEntry0");
	__asm
	{
		jmp p[167 * 4];
	}
}

// DdEntry1
extern "C" __declspec(naked) void __stdcall __E__168__()
{
	log("DdEntry1");
	__asm
	{
		jmp p[168 * 4];
	}
}

// DdEntry10
extern "C" __declspec(naked) void __stdcall __E__169__()
{
	log("DdEntry10");
	__asm
	{
		jmp p[169 * 4];
	}
}

// DdEntry11
extern "C" __declspec(naked) void __stdcall __E__170__()
{
	log("DdEntry11");
	__asm
	{
		jmp p[170 * 4];
	}
}

// DdEntry12
extern "C" __declspec(naked) void __stdcall __E__171__()
{
	log("DdEntry12");
	__asm
	{
		jmp p[171 * 4];
	}
}

// DdEntry13
extern "C" __declspec(naked) void __stdcall __E__172__()
{
	log("DdEntry13");
	__asm
	{
		jmp p[172 * 4];
	}
}

// DdEntry14
extern "C" __declspec(naked) void __stdcall __E__173__()
{
	log("DdEntry14");
	__asm
	{
		jmp p[173 * 4];
	}
}

// DdEntry15
extern "C" __declspec(naked) void __stdcall __E__174__()
{
	log("DdEntry15");
	__asm
	{
		jmp p[174 * 4];
	}
}

// DdEntry16
extern "C" __declspec(naked) void __stdcall __E__175__()
{
	log("DdEntry16");
	__asm
	{
		jmp p[175 * 4];
	}
}

// DdEntry17
extern "C" __declspec(naked) void __stdcall __E__176__()
{
	log("DdEntry17");
	__asm
	{
		jmp p[176 * 4];
	}
}

// DdEntry18
extern "C" __declspec(naked) void __stdcall __E__177__()
{
	log("DdEntry18");
	__asm
	{
		jmp p[177 * 4];
	}
}

// DdEntry19
extern "C" __declspec(naked) void __stdcall __E__178__()
{
	log("DdEntry19");
	__asm
	{
		jmp p[178 * 4];
	}
}

// DdEntry2
extern "C" __declspec(naked) void __stdcall __E__179__()
{
	log("DdEntry2");
	__asm
	{
		jmp p[179 * 4];
	}
}

// DdEntry20
extern "C" __declspec(naked) void __stdcall __E__180__()
{
	log("DdEntry20");
	__asm
	{
		jmp p[180 * 4];
	}
}

// DdEntry21
extern "C" __declspec(naked) void __stdcall __E__181__()
{
	log("DdEntry21");
	__asm
	{
		jmp p[181 * 4];
	}
}

// DdEntry22
extern "C" __declspec(naked) void __stdcall __E__182__()
{
	log("DdEntry22");
	__asm
	{
		jmp p[182 * 4];
	}
}

// DdEntry23
extern "C" __declspec(naked) void __stdcall __E__183__()
{
	log("DdEntry23");
	__asm
	{
		jmp p[183 * 4];
	}
}

// DdEntry24
extern "C" __declspec(naked) void __stdcall __E__184__()
{
	log("DdEntry24");
	__asm
	{
		jmp p[184 * 4];
	}
}

// DdEntry25
extern "C" __declspec(naked) void __stdcall __E__185__()
{
	log("DdEntry25");
	__asm
	{
		jmp p[185 * 4];
	}
}

// DdEntry26
extern "C" __declspec(naked) void __stdcall __E__186__()
{
	log("DdEntry26");
	__asm
	{
		jmp p[186 * 4];
	}
}

// DdEntry27
extern "C" __declspec(naked) void __stdcall __E__187__()
{
	log("DdEntry27");
	__asm
	{
		jmp p[187 * 4];
	}
}

// DdEntry28
extern "C" __declspec(naked) void __stdcall __E__188__()
{
	log("DdEntry28");
	__asm
	{
		jmp p[188 * 4];
	}
}

// DdEntry29
extern "C" __declspec(naked) void __stdcall __E__189__()
{
	log("DdEntry29");
	__asm
	{
		jmp p[189 * 4];
	}
}

// DdEntry3
extern "C" __declspec(naked) void __stdcall __E__190__()
{
	log("DdEntry3");
	__asm
	{
		jmp p[190 * 4];
	}
}

// DdEntry30
extern "C" __declspec(naked) void __stdcall __E__191__()
{
	log("DdEntry30");
	__asm
	{
		jmp p[191 * 4];
	}
}

// DdEntry31
extern "C" __declspec(naked) void __stdcall __E__192__()
{
	log("DdEntry31");
	__asm
	{
		jmp p[192 * 4];
	}
}

// DdEntry32
extern "C" __declspec(naked) void __stdcall __E__193__()
{
	log("DdEntry32");
	__asm
	{
		jmp p[193 * 4];
	}
}

// DdEntry33
extern "C" __declspec(naked) void __stdcall __E__194__()
{
	log("DdEntry33");
	__asm
	{
		jmp p[194 * 4];
	}
}

// DdEntry34
extern "C" __declspec(naked) void __stdcall __E__195__()
{
	log("DdEntry34");
	__asm
	{
		jmp p[195 * 4];
	}
}

// DdEntry35
extern "C" __declspec(naked) void __stdcall __E__196__()
{
	log("DdEntry35");
	__asm
	{
		jmp p[196 * 4];
	}
}

// DdEntry36
extern "C" __declspec(naked) void __stdcall __E__197__()
{
	log("DdEntry36");
	__asm
	{
		jmp p[197 * 4];
	}
}

// DdEntry37
extern "C" __declspec(naked) void __stdcall __E__198__()
{
	log("DdEntry37");
	__asm
	{
		jmp p[198 * 4];
	}
}

// DdEntry38
extern "C" __declspec(naked) void __stdcall __E__199__()
{
	log("DdEntry38");
	__asm
	{
		jmp p[199 * 4];
	}
}

// DdEntry39
extern "C" __declspec(naked) void __stdcall __E__200__()
{
	log("DdEntry39");
	__asm
	{
		jmp p[200 * 4];
	}
}

// DdEntry4
extern "C" __declspec(naked) void __stdcall __E__201__()
{
	log("DdEntry4");
	__asm
	{
		jmp p[201 * 4];
	}
}

// DdEntry40
extern "C" __declspec(naked) void __stdcall __E__202__()
{
	log("DdEntry40");
	__asm
	{
		jmp p[202 * 4];
	}
}

// DdEntry41
extern "C" __declspec(naked) void __stdcall __E__203__()
{
	log("DdEntry41");
	__asm
	{
		jmp p[203 * 4];
	}
}

// DdEntry42
extern "C" __declspec(naked) void __stdcall __E__204__()
{
	log("DdEntry42");
	__asm
	{
		jmp p[204 * 4];
	}
}

// DdEntry43
extern "C" __declspec(naked) void __stdcall __E__205__()
{
	log("DdEntry43");
	__asm
	{
		jmp p[205 * 4];
	}
}

// DdEntry44
extern "C" __declspec(naked) void __stdcall __E__206__()
{
	log("DdEntry44");
	__asm
	{
		jmp p[206 * 4];
	}
}

// DdEntry45
extern "C" __declspec(naked) void __stdcall __E__207__()
{
	log("DdEntry45");
	__asm
	{
		jmp p[207 * 4];
	}
}

// DdEntry46
extern "C" __declspec(naked) void __stdcall __E__208__()
{
	log("DdEntry46");
	__asm
	{
		jmp p[208 * 4];
	}
}

// DdEntry47
extern "C" __declspec(naked) void __stdcall __E__209__()
{
	log("DdEntry47");
	__asm
	{
		jmp p[209 * 4];
	}
}

// DdEntry48
extern "C" __declspec(naked) void __stdcall __E__210__()
{
	log("DdEntry48");
	__asm
	{
		jmp p[210 * 4];
	}
}

// DdEntry49
extern "C" __declspec(naked) void __stdcall __E__211__()
{
	log("DdEntry49");
	__asm
	{
		jmp p[211 * 4];
	}
}

// DdEntry5
extern "C" __declspec(naked) void __stdcall __E__212__()
{
	log("DdEntry5");
	__asm
	{
		jmp p[212 * 4];
	}
}

// DdEntry50
extern "C" __declspec(naked) void __stdcall __E__213__()
{
	log("DdEntry50");
	__asm
	{
		jmp p[213 * 4];
	}
}

// DdEntry51
extern "C" __declspec(naked) void __stdcall __E__214__()
{
	log("DdEntry51");
	__asm
	{
		jmp p[214 * 4];
	}
}

// DdEntry52
extern "C" __declspec(naked) void __stdcall __E__215__()
{
	log("DdEntry52");
	__asm
	{
		jmp p[215 * 4];
	}
}

// DdEntry53
extern "C" __declspec(naked) void __stdcall __E__216__()
{
	log("DdEntry53");
	__asm
	{
		jmp p[216 * 4];
	}
}

// DdEntry54
extern "C" __declspec(naked) void __stdcall __E__217__()
{
	log("DdEntry54");
	__asm
	{
		jmp p[217 * 4];
	}
}

// DdEntry55
extern "C" __declspec(naked) void __stdcall __E__218__()
{
	log("DdEntry55");
	__asm
	{
		jmp p[218 * 4];
	}
}

// DdEntry56
extern "C" __declspec(naked) void __stdcall __E__219__()
{
	log("DdEntry56");
	__asm
	{
		jmp p[219 * 4];
	}
}

// DdEntry6
extern "C" __declspec(naked) void __stdcall __E__220__()
{
	log("DdEntry6");
	__asm
	{
		jmp p[220 * 4];
	}
}

// DdEntry7
extern "C" __declspec(naked) void __stdcall __E__221__()
{
	log("DdEntry7");
	__asm
	{
		jmp p[221 * 4];
	}
}

// DdEntry8
extern "C" __declspec(naked) void __stdcall __E__222__()
{
	log("DdEntry8");
	__asm
	{
		jmp p[222 * 4];
	}
}

// DdEntry9
extern "C" __declspec(naked) void __stdcall __E__223__()
{
	log("DdEntry9");
	__asm
	{
		jmp p[223 * 4];
	}
}

// DdNotifyFullscreenSpriteUpdate
extern "C" __declspec(naked) void __stdcall __E__224__()
{
	log("DdNotifyFullscreenSpriteUpdate");
	__asm
	{
		jmp p[224 * 4];
	}
}

// DdQueryVisRgnUniqueness
extern "C" __declspec(naked) void __stdcall __E__225__()
{
	log("DdQueryVisRgnUniqueness");
	__asm
	{
		jmp p[225 * 4];
	}
}

// DeleteColorSpace
extern "C" __declspec(naked) void __stdcall __E__226__()
{
	log("DeleteColorSpace");
	__asm
	{
		jmp p[226 * 4];
	}
}

// DeleteDC
extern "C" __declspec(naked) void __stdcall __E__227__()
{
	log("DeleteDC");
	__asm
	{
		jmp p[227 * 4];
	}
}

// DeleteEnhMetaFile
extern "C" __declspec(naked) void __stdcall __E__228__()
{
	log("DeleteEnhMetaFile");
	__asm
	{
		jmp p[228 * 4];
	}
}

// DeleteMetaFile
extern "C" __declspec(naked) void __stdcall __E__229__()
{
	log("DeleteMetaFile");
	__asm
	{
		jmp p[229 * 4];
	}
}

// DeleteObject
extern "C" __declspec(naked) void __stdcall __E__230__()
{
	log("DeleteObject");
	__asm
	{
		jmp p[230 * 4];
	}
}

// DescribePixelFormat
extern "C" __declspec(naked) void __stdcall __E__231__()
{
	log("DescribePixelFormat");
	__asm
	{
		jmp p[231 * 4];
	}
}

// DestroyOPMProtectedOutput
extern "C" __declspec(naked) void __stdcall __E__232__()
{
	log("DestroyOPMProtectedOutput");
	__asm
	{
		jmp p[232 * 4];
	}
}

// DestroyPhysicalMonitorInternal
extern "C" __declspec(naked) void __stdcall __E__233__()
{
	log("DestroyPhysicalMonitorInternal");
	__asm
	{
		jmp p[233 * 4];
	}
}

// DeviceCapabilitiesExA
extern "C" __declspec(naked) void __stdcall __E__234__()
{
	log("DeviceCapabilitiesExA");
	__asm
	{
		jmp p[234 * 4];
	}
}

// DeviceCapabilitiesExW
extern "C" __declspec(naked) void __stdcall __E__235__()
{
	log("DeviceCapabilitiesExW");
	__asm
	{
		jmp p[235 * 4];
	}
}

// DrawEscape
extern "C" __declspec(naked) void __stdcall __E__236__()
{
	log("DrawEscape");
	__asm
	{
		jmp p[236 * 4];
	}
}

// Ellipse
extern "C" __declspec(naked) void __stdcall __E__237__()
{
	log("Ellipse");
	__asm
	{
		jmp p[237 * 4];
	}
}

// EnableEUDC
extern "C" __declspec(naked) void __stdcall __E__238__()
{
	log("EnableEUDC");
	__asm
	{
		jmp p[238 * 4];
	}
}

// EndDoc
extern "C" __declspec(naked) void __stdcall __E__239__()
{
	log("EndDoc");
	__asm
	{
		jmp p[239 * 4];
	}
}

// EndFormPage
extern "C" __declspec(naked) void __stdcall __E__240__()
{
	log("EndFormPage");
	__asm
	{
		jmp p[240 * 4];
	}
}

// EndGdiRendering
extern "C" __declspec(naked) void __stdcall __E__241__()
{
	log("EndGdiRendering");
	__asm
	{
		jmp p[241 * 4];
	}
}

// EndPage
extern "C" __declspec(naked) void __stdcall __E__242__()
{
	log("EndPage");
	__asm
	{
		jmp p[242 * 4];
	}
}

// EndPath
extern "C" __declspec(naked) void __stdcall __E__243__()
{
	log("EndPath");
	__asm
	{
		jmp p[243 * 4];
	}
}

// EngAcquireSemaphore
extern "C" __declspec(naked) void __stdcall __E__244__()
{
	log("EngAcquireSemaphore");
	__asm
	{
		jmp p[244 * 4];
	}
}

// EngAlphaBlend
extern "C" __declspec(naked) void __stdcall __E__245__()
{
	log("EngAlphaBlend");
	__asm
	{
		jmp p[245 * 4];
	}
}

// EngAssociateSurface
extern "C" __declspec(naked) void __stdcall __E__246__()
{
	log("EngAssociateSurface");
	__asm
	{
		jmp p[246 * 4];
	}
}

// EngBitBlt
extern "C" __declspec(naked) void __stdcall __E__247__()
{
	log("EngBitBlt");
	__asm
	{
		jmp p[247 * 4];
	}
}

// EngCheckAbort
extern "C" __declspec(naked) void __stdcall __E__248__()
{
	log("EngCheckAbort");
	__asm
	{
		jmp p[248 * 4];
	}
}

// EngComputeGlyphSet
extern "C" __declspec(naked) void __stdcall __E__249__()
{
	log("EngComputeGlyphSet");
	__asm
	{
		jmp p[249 * 4];
	}
}

// EngCopyBits
extern "C" __declspec(naked) void __stdcall __E__250__()
{
	log("EngCopyBits");
	__asm
	{
		jmp p[250 * 4];
	}
}

// EngCreateBitmap
extern "C" __declspec(naked) void __stdcall __E__251__()
{
	log("EngCreateBitmap");
	__asm
	{
		jmp p[251 * 4];
	}
}

// EngCreateClip
extern "C" __declspec(naked) void __stdcall __E__252__()
{
	log("EngCreateClip");
	__asm
	{
		jmp p[252 * 4];
	}
}

// EngCreateDeviceBitmap
extern "C" __declspec(naked) void __stdcall __E__253__()
{
	log("EngCreateDeviceBitmap");
	__asm
	{
		jmp p[253 * 4];
	}
}

// EngCreateDeviceSurface
extern "C" __declspec(naked) void __stdcall __E__254__()
{
	log("EngCreateDeviceSurface");
	__asm
	{
		jmp p[254 * 4];
	}
}

// EngCreatePalette
extern "C" __declspec(naked) void __stdcall __E__255__()
{
	log("EngCreatePalette");
	__asm
	{
		jmp p[255 * 4];
	}
}

// EngCreateSemaphore
extern "C" __declspec(naked) void __stdcall __E__256__()
{
	log("EngCreateSemaphore");
	__asm
	{
		jmp p[256 * 4];
	}
}

// EngDeleteClip
extern "C" __declspec(naked) void __stdcall __E__257__()
{
	log("EngDeleteClip");
	__asm
	{
		jmp p[257 * 4];
	}
}

// EngDeletePalette
extern "C" __declspec(naked) void __stdcall __E__258__()
{
	log("EngDeletePalette");
	__asm
	{
		jmp p[258 * 4];
	}
}

// EngDeletePath
extern "C" __declspec(naked) void __stdcall __E__259__()
{
	log("EngDeletePath");
	__asm
	{
		jmp p[259 * 4];
	}
}

// EngDeleteSemaphore
extern "C" __declspec(naked) void __stdcall __E__260__()
{
	log("EngDeleteSemaphore");
	__asm
	{
		jmp p[260 * 4];
	}
}

// EngDeleteSurface
extern "C" __declspec(naked) void __stdcall __E__261__()
{
	log("EngDeleteSurface");
	__asm
	{
		jmp p[261 * 4];
	}
}

// EngEraseSurface
extern "C" __declspec(naked) void __stdcall __E__262__()
{
	log("EngEraseSurface");
	__asm
	{
		jmp p[262 * 4];
	}
}

// EngFillPath
extern "C" __declspec(naked) void __stdcall __E__263__()
{
	log("EngFillPath");
	__asm
	{
		jmp p[263 * 4];
	}
}

// EngFindResource
extern "C" __declspec(naked) void __stdcall __E__264__()
{
	log("EngFindResource");
	__asm
	{
		jmp p[264 * 4];
	}
}

// EngFreeModule
extern "C" __declspec(naked) void __stdcall __E__265__()
{
	log("EngFreeModule");
	__asm
	{
		jmp p[265 * 4];
	}
}

// EngGetCurrentCodePage
extern "C" __declspec(naked) void __stdcall __E__266__()
{
	log("EngGetCurrentCodePage");
	__asm
	{
		jmp p[266 * 4];
	}
}

// EngGetDriverName
extern "C" __declspec(naked) void __stdcall __E__267__()
{
	log("EngGetDriverName");
	__asm
	{
		jmp p[267 * 4];
	}
}

// EngGetPrinterDataFileName
extern "C" __declspec(naked) void __stdcall __E__268__()
{
	log("EngGetPrinterDataFileName");
	__asm
	{
		jmp p[268 * 4];
	}
}

// EngGradientFill
extern "C" __declspec(naked) void __stdcall __E__269__()
{
	log("EngGradientFill");
	__asm
	{
		jmp p[269 * 4];
	}
}

// EngLineTo
extern "C" __declspec(naked) void __stdcall __E__270__()
{
	log("EngLineTo");
	__asm
	{
		jmp p[270 * 4];
	}
}

// EngLoadModule
extern "C" __declspec(naked) void __stdcall __E__271__()
{
	log("EngLoadModule");
	__asm
	{
		jmp p[271 * 4];
	}
}

// EngLockSurface
extern "C" __declspec(naked) void __stdcall __E__272__()
{
	log("EngLockSurface");
	__asm
	{
		jmp p[272 * 4];
	}
}

// EngMarkBandingSurface
extern "C" __declspec(naked) void __stdcall __E__273__()
{
	log("EngMarkBandingSurface");
	__asm
	{
		jmp p[273 * 4];
	}
}

// EngMultiByteToUnicodeN
extern "C" __declspec(naked) void __stdcall __E__274__()
{
	log("EngMultiByteToUnicodeN");
	__asm
	{
		jmp p[274 * 4];
	}
}

// EngMultiByteToWideChar
extern "C" __declspec(naked) void __stdcall __E__275__()
{
	log("EngMultiByteToWideChar");
	__asm
	{
		jmp p[275 * 4];
	}
}

// EngPaint
extern "C" __declspec(naked) void __stdcall __E__276__()
{
	log("EngPaint");
	__asm
	{
		jmp p[276 * 4];
	}
}

// EngPlgBlt
extern "C" __declspec(naked) void __stdcall __E__277__()
{
	log("EngPlgBlt");
	__asm
	{
		jmp p[277 * 4];
	}
}

// EngQueryEMFInfo
extern "C" __declspec(naked) void __stdcall __E__278__()
{
	log("EngQueryEMFInfo");
	__asm
	{
		jmp p[278 * 4];
	}
}

// EngQueryLocalTime
extern "C" __declspec(naked) void __stdcall __E__279__()
{
	log("EngQueryLocalTime");
	__asm
	{
		jmp p[279 * 4];
	}
}

// EngReleaseSemaphore
extern "C" __declspec(naked) void __stdcall __E__280__()
{
	log("EngReleaseSemaphore");
	__asm
	{
		jmp p[280 * 4];
	}
}

// EngStretchBlt
extern "C" __declspec(naked) void __stdcall __E__281__()
{
	log("EngStretchBlt");
	__asm
	{
		jmp p[281 * 4];
	}
}

// EngStretchBltROP
extern "C" __declspec(naked) void __stdcall __E__282__()
{
	log("EngStretchBltROP");
	__asm
	{
		jmp p[282 * 4];
	}
}

// EngStrokeAndFillPath
extern "C" __declspec(naked) void __stdcall __E__283__()
{
	log("EngStrokeAndFillPath");
	__asm
	{
		jmp p[283 * 4];
	}
}

// EngStrokePath
extern "C" __declspec(naked) void __stdcall __E__284__()
{
	log("EngStrokePath");
	__asm
	{
		jmp p[284 * 4];
	}
}

// EngTextOut
extern "C" __declspec(naked) void __stdcall __E__285__()
{
	log("EngTextOut");
	__asm
	{
		jmp p[285 * 4];
	}
}

// EngTransparentBlt
extern "C" __declspec(naked) void __stdcall __E__286__()
{
	log("EngTransparentBlt");
	__asm
	{
		jmp p[286 * 4];
	}
}

// EngUnicodeToMultiByteN
extern "C" __declspec(naked) void __stdcall __E__287__()
{
	log("EngUnicodeToMultiByteN");
	__asm
	{
		jmp p[287 * 4];
	}
}

// EngUnlockSurface
extern "C" __declspec(naked) void __stdcall __E__288__()
{
	log("EngUnlockSurface");
	__asm
	{
		jmp p[288 * 4];
	}
}

// EngWideCharToMultiByte
extern "C" __declspec(naked) void __stdcall __E__289__()
{
	log("EngWideCharToMultiByte");
	__asm
	{
		jmp p[289 * 4];
	}
}

// EnumEnhMetaFile
extern "C" __declspec(naked) void __stdcall __E__290__()
{
	log("EnumEnhMetaFile");
	__asm
	{
		jmp p[290 * 4];
	}
}

// EnumFontFamiliesA
extern "C" __declspec(naked) void __stdcall __E__291__()
{
	log("EnumFontFamiliesA");
	__asm
	{
		jmp p[291 * 4];
	}
}

// EnumFontFamiliesExA
extern "C" __declspec(naked) void __stdcall __E__292__()
{
	log("EnumFontFamiliesExA");
	__asm
	{
		jmp p[292 * 4];
	}
}

// EnumFontFamiliesExW
extern "C" __declspec(naked) void __stdcall __E__293__()
{
	log("EnumFontFamiliesExW");
	__asm
	{
		jmp p[293 * 4];
	}
}

// EnumFontFamiliesW
extern "C" __declspec(naked) void __stdcall __E__294__()
{
	log("EnumFontFamiliesW");
	__asm
	{
		jmp p[294 * 4];
	}
}

// EnumFontsA
extern "C" __declspec(naked) void __stdcall __E__295__()
{
	log("EnumFontsA");
	__asm
	{
		jmp p[295 * 4];
	}
}

// EnumFontsW
extern "C" __declspec(naked) void __stdcall __E__296__()
{
	log("EnumFontsW");
	__asm
	{
		jmp p[296 * 4];
	}
}

// EnumICMProfilesA
extern "C" __declspec(naked) void __stdcall __E__297__()
{
	log("EnumICMProfilesA");
	__asm
	{
		jmp p[297 * 4];
	}
}

// EnumICMProfilesW
extern "C" __declspec(naked) void __stdcall __E__298__()
{
	log("EnumICMProfilesW");
	__asm
	{
		jmp p[298 * 4];
	}
}

// EnumMetaFile
extern "C" __declspec(naked) void __stdcall __E__299__()
{
	log("EnumMetaFile");
	__asm
	{
		jmp p[299 * 4];
	}
}

// EnumObjects
extern "C" __declspec(naked) void __stdcall __E__300__()
{
	log("EnumObjects");
	__asm
	{
		jmp p[300 * 4];
	}
}

// EqualRgn
extern "C" __declspec(naked) void __stdcall __E__301__()
{
	log("EqualRgn");
	__asm
	{
		jmp p[301 * 4];
	}
}

// Escape
extern "C" __declspec(naked) void __stdcall __E__302__()
{
	log("Escape");
	__asm
	{
		jmp p[302 * 4];
	}
}

// EudcLoadLinkW
extern "C" __declspec(naked) void __stdcall __E__303__()
{
	log("EudcLoadLinkW");
	__asm
	{
		jmp p[303 * 4];
	}
}

// EudcUnloadLinkW
extern "C" __declspec(naked) void __stdcall __E__304__()
{
	log("EudcUnloadLinkW");
	__asm
	{
		jmp p[304 * 4];
	}
}

// ExcludeClipRect
extern "C" __declspec(naked) void __stdcall __E__305__()
{
	log("ExcludeClipRect");
	__asm
	{
		jmp p[305 * 4];
	}
}

// ExtCreatePen
extern "C" __declspec(naked) void __stdcall __E__306__()
{
	log("ExtCreatePen");
	__asm
	{
		jmp p[306 * 4];
	}
}

// ExtCreateRegion
extern "C" __declspec(naked) void __stdcall __E__307__()
{
	log("ExtCreateRegion");
	__asm
	{
		jmp p[307 * 4];
	}
}

// ExtEscape
extern "C" __declspec(naked) void __stdcall __E__308__()
{
	log("ExtEscape");
	__asm
	{
		jmp p[308 * 4];
	}
}

// ExtFloodFill
extern "C" __declspec(naked) void __stdcall __E__309__()
{
	log("ExtFloodFill");
	__asm
	{
		jmp p[309 * 4];
	}
}

// ExtSelectClipRgn
extern "C" __declspec(naked) void __stdcall __E__310__()
{
	log("ExtSelectClipRgn");
	__asm
	{
		jmp p[310 * 4];
	}
}

// ExtTextOutA
extern "C" __declspec(naked) void __stdcall __E__311__()
{
	log("ExtTextOutA");
	__asm
	{
		jmp p[311 * 4];
	}
}

// ExtTextOutW
extern "C" __declspec(naked) void __stdcall __E__312__()
{
	log("ExtTextOutW");
	__asm
	{
		jmp p[312 * 4];
	}
}

// FONTOBJ_cGetAllGlyphHandles
extern "C" __declspec(naked) void __stdcall __E__313__()
{
	log("FONTOBJ_cGetAllGlyphHandles");
	__asm
	{
		jmp p[313 * 4];
	}
}

// FONTOBJ_cGetGlyphs
extern "C" __declspec(naked) void __stdcall __E__314__()
{
	log("FONTOBJ_cGetGlyphs");
	__asm
	{
		jmp p[314 * 4];
	}
}

// FONTOBJ_pQueryGlyphAttrs
extern "C" __declspec(naked) void __stdcall __E__315__()
{
	log("FONTOBJ_pQueryGlyphAttrs");
	__asm
	{
		jmp p[315 * 4];
	}
}

// FONTOBJ_pfdg
extern "C" __declspec(naked) void __stdcall __E__316__()
{
	log("FONTOBJ_pfdg");
	__asm
	{
		jmp p[316 * 4];
	}
}

// FONTOBJ_pifi
extern "C" __declspec(naked) void __stdcall __E__317__()
{
	log("FONTOBJ_pifi");
	__asm
	{
		jmp p[317 * 4];
	}
}

// FONTOBJ_pvTrueTypeFontFile
extern "C" __declspec(naked) void __stdcall __E__318__()
{
	log("FONTOBJ_pvTrueTypeFontFile");
	__asm
	{
		jmp p[318 * 4];
	}
}

// FONTOBJ_pxoGetXform
extern "C" __declspec(naked) void __stdcall __E__319__()
{
	log("FONTOBJ_pxoGetXform");
	__asm
	{
		jmp p[319 * 4];
	}
}

// FONTOBJ_vGetInfo
extern "C" __declspec(naked) void __stdcall __E__320__()
{
	log("FONTOBJ_vGetInfo");
	__asm
	{
		jmp p[320 * 4];
	}
}

// FillPath
extern "C" __declspec(naked) void __stdcall __E__321__()
{
	log("FillPath");
	__asm
	{
		jmp p[321 * 4];
	}
}

// FillRgn
extern "C" __declspec(naked) void __stdcall __E__322__()
{
	log("FillRgn");
	__asm
	{
		jmp p[322 * 4];
	}
}

// FixBrushOrgEx
extern "C" __declspec(naked) void __stdcall __E__323__()
{
	log("FixBrushOrgEx");
	__asm
	{
		jmp p[323 * 4];
	}
}

// FlattenPath
extern "C" __declspec(naked) void __stdcall __E__324__()
{
	log("FlattenPath");
	__asm
	{
		jmp p[324 * 4];
	}
}

// FloodFill
extern "C" __declspec(naked) void __stdcall __E__325__()
{
	log("FloodFill");
	__asm
	{
		jmp p[325 * 4];
	}
}

// FontIsLinked
extern "C" __declspec(naked) void __stdcall __E__326__()
{
	log("FontIsLinked");
	__asm
	{
		jmp p[326 * 4];
	}
}

// FrameRgn
extern "C" __declspec(naked) void __stdcall __E__327__()
{
	log("FrameRgn");
	__asm
	{
		jmp p[327 * 4];
	}
}

// GdiAddFontResourceW
extern "C" __declspec(naked) void __stdcall __E__328__()
{
	log("GdiAddFontResourceW");
	__asm
	{
		jmp p[328 * 4];
	}
}

// GdiAddGlsBounds
extern "C" __declspec(naked) void __stdcall __E__329__()
{
	log("GdiAddGlsBounds");
	__asm
	{
		jmp p[329 * 4];
	}
}

// GdiAddGlsRecord
extern "C" __declspec(naked) void __stdcall __E__330__()
{
	log("GdiAddGlsRecord");
	__asm
	{
		jmp p[330 * 4];
	}
}

// GdiAlphaBlend
extern "C" __declspec(naked) void __stdcall __E__331__()
{
	log("GdiAlphaBlend");
	__asm
	{
		jmp p[331 * 4];
	}
}

// GdiArtificialDecrementDriver
extern "C" __declspec(naked) void __stdcall __E__332__()
{
	log("GdiArtificialDecrementDriver");
	__asm
	{
		jmp p[332 * 4];
	}
}

// GdiCleanCacheDC
extern "C" __declspec(naked) void __stdcall __E__333__()
{
	log("GdiCleanCacheDC");
	__asm
	{
		jmp p[333 * 4];
	}
}

// GdiComment
extern "C" __declspec(naked) void __stdcall __E__334__()
{
	log("GdiComment");
	__asm
	{
		jmp p[334 * 4];
	}
}

// GdiConsoleTextOut
extern "C" __declspec(naked) void __stdcall __E__335__()
{
	log("GdiConsoleTextOut");
	__asm
	{
		jmp p[335 * 4];
	}
}

// GdiConvertAndCheckDC
extern "C" __declspec(naked) void __stdcall __E__336__()
{
	log("GdiConvertAndCheckDC");
	__asm
	{
		jmp p[336 * 4];
	}
}

// GdiConvertBitmap
extern "C" __declspec(naked) void __stdcall __E__337__()
{
	log("GdiConvertBitmap");
	__asm
	{
		jmp p[337 * 4];
	}
}

// GdiConvertBitmapV5
extern "C" __declspec(naked) void __stdcall __E__338__()
{
	log("GdiConvertBitmapV5");
	__asm
	{
		jmp p[338 * 4];
	}
}

// GdiConvertBrush
extern "C" __declspec(naked) void __stdcall __E__339__()
{
	log("GdiConvertBrush");
	__asm
	{
		jmp p[339 * 4];
	}
}

// GdiConvertDC
extern "C" __declspec(naked) void __stdcall __E__340__()
{
	log("GdiConvertDC");
	__asm
	{
		jmp p[340 * 4];
	}
}

// GdiConvertEnhMetaFile
extern "C" __declspec(naked) void __stdcall __E__341__()
{
	log("GdiConvertEnhMetaFile");
	__asm
	{
		jmp p[341 * 4];
	}
}

// GdiConvertFont
extern "C" __declspec(naked) void __stdcall __E__342__()
{
	log("GdiConvertFont");
	__asm
	{
		jmp p[342 * 4];
	}
}

// GdiConvertMetaFilePict
extern "C" __declspec(naked) void __stdcall __E__343__()
{
	log("GdiConvertMetaFilePict");
	__asm
	{
		jmp p[343 * 4];
	}
}

// GdiConvertPalette
extern "C" __declspec(naked) void __stdcall __E__344__()
{
	log("GdiConvertPalette");
	__asm
	{
		jmp p[344 * 4];
	}
}

// GdiConvertRegion
extern "C" __declspec(naked) void __stdcall __E__345__()
{
	log("GdiConvertRegion");
	__asm
	{
		jmp p[345 * 4];
	}
}

// GdiConvertToDevmodeW
extern "C" __declspec(naked) void __stdcall __E__346__()
{
	log("GdiConvertToDevmodeW");
	__asm
	{
		jmp p[346 * 4];
	}
}

// GdiCreateLocalEnhMetaFile
extern "C" __declspec(naked) void __stdcall __E__347__()
{
	log("GdiCreateLocalEnhMetaFile");
	__asm
	{
		jmp p[347 * 4];
	}
}

// GdiCreateLocalMetaFilePict
extern "C" __declspec(naked) void __stdcall __E__348__()
{
	log("GdiCreateLocalMetaFilePict");
	__asm
	{
		jmp p[348 * 4];
	}
}

// GdiDeleteLocalDC
extern "C" __declspec(naked) void __stdcall __E__349__()
{
	log("GdiDeleteLocalDC");
	__asm
	{
		jmp p[349 * 4];
	}
}

// GdiDeleteSpoolFileHandle
extern "C" __declspec(naked) void __stdcall __E__350__()
{
	log("GdiDeleteSpoolFileHandle");
	__asm
	{
		jmp p[350 * 4];
	}
}

// GdiDescribePixelFormat
extern "C" __declspec(naked) void __stdcall __E__351__()
{
	log("GdiDescribePixelFormat");
	__asm
	{
		jmp p[351 * 4];
	}
}

// GdiDllInitialize
extern "C" __declspec(naked) void __stdcall __E__352__()
{
	log("GdiDllInitialize");
	__asm
	{
		jmp p[352 * 4];
	}
}

// GdiDrawStream
extern "C" __declspec(naked) void __stdcall __E__353__()
{
	log("GdiDrawStream");
	__asm
	{
		jmp p[353 * 4];
	}
}

// GdiEndDocEMF
extern "C" __declspec(naked) void __stdcall __E__354__()
{
	log("GdiEndDocEMF");
	__asm
	{
		jmp p[354 * 4];
	}
}

// GdiEndPageEMF
extern "C" __declspec(naked) void __stdcall __E__355__()
{
	log("GdiEndPageEMF");
	__asm
	{
		jmp p[355 * 4];
	}
}

// GdiEntry1
extern "C" __declspec(naked) void __stdcall __E__356__()
{
	log("GdiEntry1");
	__asm
	{
		jmp p[356 * 4];
	}
}

// GdiEntry10
extern "C" __declspec(naked) void __stdcall __E__357__()
{
	log("GdiEntry10");
	__asm
	{
		jmp p[357 * 4];
	}
}

// GdiEntry11
extern "C" __declspec(naked) void __stdcall __E__358__()
{
	log("GdiEntry11");
	__asm
	{
		jmp p[358 * 4];
	}
}

// GdiEntry12
extern "C" __declspec(naked) void __stdcall __E__359__()
{
	log("GdiEntry12");
	__asm
	{
		jmp p[359 * 4];
	}
}

// GdiEntry13
extern "C" __declspec(naked) void __stdcall __E__360__()
{
	log("GdiEntry13");
	__asm
	{
		jmp p[360 * 4];
	}
}

// GdiEntry14
extern "C" __declspec(naked) void __stdcall __E__361__()
{
	log("GdiEntry14");
	__asm
	{
		jmp p[361 * 4];
	}
}

// GdiEntry15
extern "C" __declspec(naked) void __stdcall __E__362__()
{
	log("GdiEntry15");
	__asm
	{
		jmp p[362 * 4];
	}
}

// GdiEntry16
extern "C" __declspec(naked) void __stdcall __E__363__()
{
	log("GdiEntry16");
	__asm
	{
		jmp p[363 * 4];
	}
}

// GdiEntry2
extern "C" __declspec(naked) void __stdcall __E__364__()
{
	log("GdiEntry2");
	__asm
	{
		jmp p[364 * 4];
	}
}

// GdiEntry3
extern "C" __declspec(naked) void __stdcall __E__365__()
{
	log("GdiEntry3");
	__asm
	{
		jmp p[365 * 4];
	}
}

// GdiEntry4
extern "C" __declspec(naked) void __stdcall __E__366__()
{
	log("GdiEntry4");
	__asm
	{
		jmp p[366 * 4];
	}
}

// GdiEntry5
extern "C" __declspec(naked) void __stdcall __E__367__()
{
	log("GdiEntry5");
	__asm
	{
		jmp p[367 * 4];
	}
}

// GdiEntry6
extern "C" __declspec(naked) void __stdcall __E__368__()
{
	log("GdiEntry6");
	__asm
	{
		jmp p[368 * 4];
	}
}

// GdiEntry7
extern "C" __declspec(naked) void __stdcall __E__369__()
{
	log("GdiEntry7");
	__asm
	{
		jmp p[369 * 4];
	}
}

// GdiEntry8
extern "C" __declspec(naked) void __stdcall __E__370__()
{
	log("GdiEntry8");
	__asm
	{
		jmp p[370 * 4];
	}
}

// GdiEntry9
extern "C" __declspec(naked) void __stdcall __E__371__()
{
	log("GdiEntry9");
	__asm
	{
		jmp p[371 * 4];
	}
}

// GdiFixUpHandle
extern "C" __declspec(naked) void __stdcall __E__372__()
{
	log("GdiFixUpHandle");
	__asm
	{
		jmp p[372 * 4];
	}
}

// GdiFlush
extern "C" __declspec(naked) void __stdcall __E__373__()
{
	log("GdiFlush");
	__asm
	{
		jmp p[373 * 4];
	}
}

// GdiFullscreenControl
extern "C" __declspec(naked) void __stdcall __E__374__()
{
	log("GdiFullscreenControl");
	__asm
	{
		jmp p[374 * 4];
	}
}

// GdiGetBatchLimit
extern "C" __declspec(naked) void __stdcall __E__375__()
{
	log("GdiGetBatchLimit");
	__asm
	{
		jmp p[375 * 4];
	}
}

// GdiGetBitmapBitsSize
extern "C" __declspec(naked) void __stdcall __E__376__()
{
	log("GdiGetBitmapBitsSize");
	__asm
	{
		jmp p[376 * 4];
	}
}

// GdiGetCharDimensions
extern "C" __declspec(naked) void __stdcall __E__377__()
{
	log("GdiGetCharDimensions");
	__asm
	{
		jmp p[377 * 4];
	}
}

// GdiGetCodePage
extern "C" __declspec(naked) void __stdcall __E__378__()
{
	log("GdiGetCodePage");
	__asm
	{
		jmp p[378 * 4];
	}
}

// GdiGetDC
extern "C" __declspec(naked) void __stdcall __E__379__()
{
	log("GdiGetDC");
	__asm
	{
		jmp p[379 * 4];
	}
}

// GdiGetDevmodeForPage
extern "C" __declspec(naked) void __stdcall __E__380__()
{
	log("GdiGetDevmodeForPage");
	__asm
	{
		jmp p[380 * 4];
	}
}

// GdiGetLocalBrush
extern "C" __declspec(naked) void __stdcall __E__381__()
{
	log("GdiGetLocalBrush");
	__asm
	{
		jmp p[381 * 4];
	}
}

// GdiGetLocalDC
extern "C" __declspec(naked) void __stdcall __E__382__()
{
	log("GdiGetLocalDC");
	__asm
	{
		jmp p[382 * 4];
	}
}

// GdiGetLocalFont
extern "C" __declspec(naked) void __stdcall __E__383__()
{
	log("GdiGetLocalFont");
	__asm
	{
		jmp p[383 * 4];
	}
}

// GdiGetPageCount
extern "C" __declspec(naked) void __stdcall __E__384__()
{
	log("GdiGetPageCount");
	__asm
	{
		jmp p[384 * 4];
	}
}

// GdiGetPageHandle
extern "C" __declspec(naked) void __stdcall __E__385__()
{
	log("GdiGetPageHandle");
	__asm
	{
		jmp p[385 * 4];
	}
}

// GdiGetSpoolFileHandle
extern "C" __declspec(naked) void __stdcall __E__386__()
{
	log("GdiGetSpoolFileHandle");
	__asm
	{
		jmp p[386 * 4];
	}
}

// GdiGetSpoolMessage
extern "C" __declspec(naked) void __stdcall __E__387__()
{
	log("GdiGetSpoolMessage");
	__asm
	{
		jmp p[387 * 4];
	}
}

// GdiGradientFill
extern "C" __declspec(naked) void __stdcall __E__388__()
{
	log("GdiGradientFill");
	__asm
	{
		jmp p[388 * 4];
	}
}

// GdiInitSpool
extern "C" __declspec(naked) void __stdcall __E__389__()
{
	log("GdiInitSpool");
	__asm
	{
		jmp p[389 * 4];
	}
}

// GdiInitializeLanguagePack
extern "C" __declspec(naked) void __stdcall __E__390__()
{
	log("GdiInitializeLanguagePack");
	__asm
	{
		jmp p[390 * 4];
	}
}

// GdiIsMetaFileDC
extern "C" __declspec(naked) void __stdcall __E__391__()
{
	log("GdiIsMetaFileDC");
	__asm
	{
		jmp p[391 * 4];
	}
}

// GdiIsMetaPrintDC
extern "C" __declspec(naked) void __stdcall __E__392__()
{
	log("GdiIsMetaPrintDC");
	__asm
	{
		jmp p[392 * 4];
	}
}

// GdiIsPlayMetafileDC
extern "C" __declspec(naked) void __stdcall __E__393__()
{
	log("GdiIsPlayMetafileDC");
	__asm
	{
		jmp p[393 * 4];
	}
}

// GdiIsScreenDC
extern "C" __declspec(naked) void __stdcall __E__394__()
{
	log("GdiIsScreenDC");
	__asm
	{
		jmp p[394 * 4];
	}
}

// GdiLoadType1Fonts
extern "C" __declspec(naked) void __stdcall __E__395__()
{
	log("GdiLoadType1Fonts");
	__asm
	{
		jmp p[395 * 4];
	}
}

// GdiPlayDCScript
extern "C" __declspec(naked) void __stdcall __E__396__()
{
	log("GdiPlayDCScript");
	__asm
	{
		jmp p[396 * 4];
	}
}

// GdiPlayEMF
extern "C" __declspec(naked) void __stdcall __E__397__()
{
	log("GdiPlayEMF");
	__asm
	{
		jmp p[397 * 4];
	}
}

// GdiPlayJournal
extern "C" __declspec(naked) void __stdcall __E__398__()
{
	log("GdiPlayJournal");
	__asm
	{
		jmp p[398 * 4];
	}
}

// GdiPlayPageEMF
extern "C" __declspec(naked) void __stdcall __E__399__()
{
	log("GdiPlayPageEMF");
	__asm
	{
		jmp p[399 * 4];
	}
}

// GdiPlayPrivatePageEMF
extern "C" __declspec(naked) void __stdcall __E__400__()
{
	log("GdiPlayPrivatePageEMF");
	__asm
	{
		jmp p[400 * 4];
	}
}

// GdiPlayScript
extern "C" __declspec(naked) void __stdcall __E__401__()
{
	log("GdiPlayScript");
	__asm
	{
		jmp p[401 * 4];
	}
}

// GdiPrinterThunk
extern "C" __declspec(naked) void __stdcall __E__402__()
{
	log("GdiPrinterThunk");
	__asm
	{
		jmp p[402 * 4];
	}
}

// GdiProcessSetup
extern "C" __declspec(naked) void __stdcall __E__403__()
{
	log("GdiProcessSetup");
	__asm
	{
		jmp p[403 * 4];
	}
}

// GdiQueryFonts
extern "C" __declspec(naked) void __stdcall __E__404__()
{
	log("GdiQueryFonts");
	__asm
	{
		jmp p[404 * 4];
	}
}

// GdiQueryTable
extern "C" __declspec(naked) void __stdcall __E__405__()
{
	log("GdiQueryTable");
	__asm
	{
		jmp p[405 * 4];
	}
}

// GdiRealizationInfo
extern "C" __declspec(naked) void __stdcall __E__406__()
{
	log("GdiRealizationInfo");
	__asm
	{
		jmp p[406 * 4];
	}
}

// GdiReleaseDC
extern "C" __declspec(naked) void __stdcall __E__407__()
{
	log("GdiReleaseDC");
	__asm
	{
		jmp p[407 * 4];
	}
}

// GdiReleaseLocalDC
extern "C" __declspec(naked) void __stdcall __E__408__()
{
	log("GdiReleaseLocalDC");
	__asm
	{
		jmp p[408 * 4];
	}
}

// GdiResetDCEMF
extern "C" __declspec(naked) void __stdcall __E__409__()
{
	log("GdiResetDCEMF");
	__asm
	{
		jmp p[409 * 4];
	}
}

// GdiSetAttrs
extern "C" __declspec(naked) void __stdcall __E__410__()
{
	log("GdiSetAttrs");
	__asm
	{
		jmp p[410 * 4];
	}
}

// GdiSetBatchLimit
extern "C" __declspec(naked) void __stdcall __E__411__()
{
	log("GdiSetBatchLimit");
	__asm
	{
		jmp p[411 * 4];
	}
}

// GdiSetLastError
extern "C" __declspec(naked) void __stdcall __E__412__()
{
	log("GdiSetLastError");
	__asm
	{
		jmp p[412 * 4];
	}
}

// GdiSetPixelFormat
extern "C" __declspec(naked) void __stdcall __E__413__()
{
	log("GdiSetPixelFormat");
	__asm
	{
		jmp p[413 * 4];
	}
}

// GdiSetServerAttr
extern "C" __declspec(naked) void __stdcall __E__414__()
{
	log("GdiSetServerAttr");
	__asm
	{
		jmp p[414 * 4];
	}
}

// GdiStartDocEMF
extern "C" __declspec(naked) void __stdcall __E__415__()
{
	log("GdiStartDocEMF");
	__asm
	{
		jmp p[415 * 4];
	}
}

// GdiStartPageEMF
extern "C" __declspec(naked) void __stdcall __E__416__()
{
	log("GdiStartPageEMF");
	__asm
	{
		jmp p[416 * 4];
	}
}

// GdiSwapBuffers
extern "C" __declspec(naked) void __stdcall __E__417__()
{
	log("GdiSwapBuffers");
	__asm
	{
		jmp p[417 * 4];
	}
}

// GdiTransparentBlt
extern "C" __declspec(naked) void __stdcall __E__418__()
{
	log("GdiTransparentBlt");
	__asm
	{
		jmp p[418 * 4];
	}
}

// GdiValidateHandle
extern "C" __declspec(naked) void __stdcall __E__419__()
{
	log("GdiValidateHandle");
	__asm
	{
		jmp p[419 * 4];
	}
}

// GetArcDirection
extern "C" __declspec(naked) void __stdcall __E__420__()
{
	log("GetArcDirection");
	__asm
	{
		jmp p[420 * 4];
	}
}

// GetAspectRatioFilterEx
extern "C" __declspec(naked) void __stdcall __E__421__()
{
	log("GetAspectRatioFilterEx");
	__asm
	{
		jmp p[421 * 4];
	}
}

// GetBitmapAttributes
extern "C" __declspec(naked) void __stdcall __E__422__()
{
	log("GetBitmapAttributes");
	__asm
	{
		jmp p[422 * 4];
	}
}

// GetBitmapBits
extern "C" __declspec(naked) void __stdcall __E__423__()
{
	log("GetBitmapBits");
	__asm
	{
		jmp p[423 * 4];
	}
}

// GetBitmapDimensionEx
extern "C" __declspec(naked) void __stdcall __E__424__()
{
	log("GetBitmapDimensionEx");
	__asm
	{
		jmp p[424 * 4];
	}
}

// GetBkColor
extern "C" __declspec(naked) void __stdcall __E__425__()
{
	log("GetBkColor");
	__asm
	{
		jmp p[425 * 4];
	}
}

// GetBkMode
extern "C" __declspec(naked) void __stdcall __E__426__()
{
	log("GetBkMode");
	__asm
	{
		jmp p[426 * 4];
	}
}

// GetBoundsRect
extern "C" __declspec(naked) void __stdcall __E__427__()
{
	log("GetBoundsRect");
	__asm
	{
		jmp p[427 * 4];
	}
}

// GetBrushAttributes
extern "C" __declspec(naked) void __stdcall __E__428__()
{
	log("GetBrushAttributes");
	__asm
	{
		jmp p[428 * 4];
	}
}

// GetBrushOrgEx
extern "C" __declspec(naked) void __stdcall __E__429__()
{
	log("GetBrushOrgEx");
	__asm
	{
		jmp p[429 * 4];
	}
}

// GetCOPPCompatibleOPMInformation
extern "C" __declspec(naked) void __stdcall __E__430__()
{
	log("GetCOPPCompatibleOPMInformation");
	__asm
	{
		jmp p[430 * 4];
	}
}

// GetCertificate
extern "C" __declspec(naked) void __stdcall __E__431__()
{
	log("GetCertificate");
	__asm
	{
		jmp p[431 * 4];
	}
}

// GetCertificateSize
extern "C" __declspec(naked) void __stdcall __E__432__()
{
	log("GetCertificateSize");
	__asm
	{
		jmp p[432 * 4];
	}
}

// GetCharABCWidthsA
extern "C" __declspec(naked) void __stdcall __E__433__()
{
	log("GetCharABCWidthsA");
	__asm
	{
		jmp p[433 * 4];
	}
}

// GetCharABCWidthsFloatA
extern "C" __declspec(naked) void __stdcall __E__434__()
{
	log("GetCharABCWidthsFloatA");
	__asm
	{
		jmp p[434 * 4];
	}
}

// GetCharABCWidthsFloatW
extern "C" __declspec(naked) void __stdcall __E__435__()
{
	log("GetCharABCWidthsFloatW");
	__asm
	{
		jmp p[435 * 4];
	}
}

// GetCharABCWidthsI
extern "C" __declspec(naked) void __stdcall __E__436__()
{
	log("GetCharABCWidthsI");
	__asm
	{
		jmp p[436 * 4];
	}
}

// GetCharABCWidthsW
extern "C" __declspec(naked) void __stdcall __E__437__()
{
	log("GetCharABCWidthsW");
	__asm
	{
		jmp p[437 * 4];
	}
}

// GetCharWidth32A
extern "C" __declspec(naked) void __stdcall __E__438__()
{
	log("GetCharWidth32A");
	__asm
	{
		jmp p[438 * 4];
	}
}

// GetCharWidth32W
extern "C" __declspec(naked) void __stdcall __E__439__()
{
	log("GetCharWidth32W");
	__asm
	{
		jmp p[439 * 4];
	}
}

// GetCharWidthA
extern "C" __declspec(naked) void __stdcall __E__440__()
{
	log("GetCharWidthA");
	__asm
	{
		jmp p[440 * 4];
	}
}

// GetCharWidthFloatA
extern "C" __declspec(naked) void __stdcall __E__441__()
{
	log("GetCharWidthFloatA");
	__asm
	{
		jmp p[441 * 4];
	}
}

// GetCharWidthFloatW
extern "C" __declspec(naked) void __stdcall __E__442__()
{
	log("GetCharWidthFloatW");
	__asm
	{
		jmp p[442 * 4];
	}
}

// GetCharWidthI
extern "C" __declspec(naked) void __stdcall __E__443__()
{
	log("GetCharWidthI");
	__asm
	{
		jmp p[443 * 4];
	}
}

// GetCharWidthInfo
extern "C" __declspec(naked) void __stdcall __E__444__()
{
	log("GetCharWidthInfo");
	__asm
	{
		jmp p[444 * 4];
	}
}

// GetCharWidthW
extern "C" __declspec(naked) void __stdcall __E__445__()
{
	log("GetCharWidthW");
	__asm
	{
		jmp p[445 * 4];
	}
}

// GetCharacterPlacementA
extern "C" __declspec(naked) void __stdcall __E__446__()
{
	log("GetCharacterPlacementA");
	__asm
	{
		jmp p[446 * 4];
	}
}

// GetCharacterPlacementW
extern "C" __declspec(naked) void __stdcall __E__447__()
{
	log("GetCharacterPlacementW");
	__asm
	{
		jmp p[447 * 4];
	}
}

// GetClipBox
extern "C" __declspec(naked) void __stdcall __E__448__()
{
	log("GetClipBox");
	__asm
	{
		jmp p[448 * 4];
	}
}

// GetClipRgn
extern "C" __declspec(naked) void __stdcall __E__449__()
{
	log("GetClipRgn");
	__asm
	{
		jmp p[449 * 4];
	}
}

// GetColorAdjustment
extern "C" __declspec(naked) void __stdcall __E__450__()
{
	log("GetColorAdjustment");
	__asm
	{
		jmp p[450 * 4];
	}
}

// GetColorSpace
extern "C" __declspec(naked) void __stdcall __E__451__()
{
	log("GetColorSpace");
	__asm
	{
		jmp p[451 * 4];
	}
}

// GetCurrentObject
extern "C" __declspec(naked) void __stdcall __E__452__()
{
	log("GetCurrentObject");
	__asm
	{
		jmp p[452 * 4];
	}
}

// GetCurrentPositionEx
extern "C" __declspec(naked) void __stdcall __E__453__()
{
	log("GetCurrentPositionEx");
	__asm
	{
		jmp p[453 * 4];
	}
}

// GetDCBrushColor
extern "C" __declspec(naked) void __stdcall __E__454__()
{
	log("GetDCBrushColor");
	__asm
	{
		jmp p[454 * 4];
	}
}

// GetDCOrgEx
extern "C" __declspec(naked) void __stdcall __E__455__()
{
	log("GetDCOrgEx");
	__asm
	{
		jmp p[455 * 4];
	}
}

// GetDCPenColor
extern "C" __declspec(naked) void __stdcall __E__456__()
{
	log("GetDCPenColor");
	__asm
	{
		jmp p[456 * 4];
	}
}

// GetDIBColorTable
extern "C" __declspec(naked) void __stdcall __E__457__()
{
	log("GetDIBColorTable");
	__asm
	{
		jmp p[457 * 4];
	}
}

// GetDIBits
extern "C" __declspec(naked) void __stdcall __E__458__()
{
	log("GetDIBits");
	__asm
	{
		jmp p[458 * 4];
	}
}

// GetDeviceCaps
extern "C" __declspec(naked) void __stdcall __E__459__()
{
	log("GetDeviceCaps");
	__asm
	{
		jmp p[459 * 4];
	}
}

// GetDeviceGammaRamp
extern "C" __declspec(naked) void __stdcall __E__460__()
{
	log("GetDeviceGammaRamp");
	__asm
	{
		jmp p[460 * 4];
	}
}

// GetETM
extern "C" __declspec(naked) void __stdcall __E__461__()
{
	log("GetETM");
	__asm
	{
		jmp p[461 * 4];
	}
}

// GetEUDCTimeStamp
extern "C" __declspec(naked) void __stdcall __E__462__()
{
	log("GetEUDCTimeStamp");
	__asm
	{
		jmp p[462 * 4];
	}
}

// GetEUDCTimeStampExW
extern "C" __declspec(naked) void __stdcall __E__463__()
{
	log("GetEUDCTimeStampExW");
	__asm
	{
		jmp p[463 * 4];
	}
}

// GetEnhMetaFileA
extern "C" __declspec(naked) void __stdcall __E__464__()
{
	log("GetEnhMetaFileA");
	__asm
	{
		jmp p[464 * 4];
	}
}

// GetEnhMetaFileBits
extern "C" __declspec(naked) void __stdcall __E__465__()
{
	log("GetEnhMetaFileBits");
	__asm
	{
		jmp p[465 * 4];
	}
}

// GetEnhMetaFileDescriptionA
extern "C" __declspec(naked) void __stdcall __E__466__()
{
	log("GetEnhMetaFileDescriptionA");
	__asm
	{
		jmp p[466 * 4];
	}
}

// GetEnhMetaFileDescriptionW
extern "C" __declspec(naked) void __stdcall __E__467__()
{
	log("GetEnhMetaFileDescriptionW");
	__asm
	{
		jmp p[467 * 4];
	}
}

// GetEnhMetaFileHeader
extern "C" __declspec(naked) void __stdcall __E__468__()
{
	log("GetEnhMetaFileHeader");
	__asm
	{
		jmp p[468 * 4];
	}
}

// GetEnhMetaFilePaletteEntries
extern "C" __declspec(naked) void __stdcall __E__469__()
{
	log("GetEnhMetaFilePaletteEntries");
	__asm
	{
		jmp p[469 * 4];
	}
}

// GetEnhMetaFilePixelFormat
extern "C" __declspec(naked) void __stdcall __E__470__()
{
	log("GetEnhMetaFilePixelFormat");
	__asm
	{
		jmp p[470 * 4];
	}
}

// GetEnhMetaFileW
extern "C" __declspec(naked) void __stdcall __E__471__()
{
	log("GetEnhMetaFileW");
	__asm
	{
		jmp p[471 * 4];
	}
}

// GetFontAssocStatus
extern "C" __declspec(naked) void __stdcall __E__472__()
{
	log("GetFontAssocStatus");
	__asm
	{
		jmp p[472 * 4];
	}
}

// GetFontData
extern "C" __declspec(naked) void __stdcall __E__473__()
{
	log("GetFontData");
	__asm
	{
		jmp p[473 * 4];
	}
}

// GetFontFileData
extern "C" __declspec(naked) void __stdcall __E__474__()
{
	log("GetFontFileData");
	__asm
	{
		jmp p[474 * 4];
	}
}

// GetFontFileInfo
extern "C" __declspec(naked) void __stdcall __E__475__()
{
	log("GetFontFileInfo");
	__asm
	{
		jmp p[475 * 4];
	}
}

// GetFontLanguageInfo
extern "C" __declspec(naked) void __stdcall __E__476__()
{
	log("GetFontLanguageInfo");
	__asm
	{
		jmp p[476 * 4];
	}
}

// GetFontRealizationInfo
extern "C" __declspec(naked) void __stdcall __E__477__()
{
	log("GetFontRealizationInfo");
	__asm
	{
		jmp p[477 * 4];
	}
}

// GetFontResourceInfoW
extern "C" __declspec(naked) void __stdcall __E__478__()
{
	log("GetFontResourceInfoW");
	__asm
	{
		jmp p[478 * 4];
	}
}

// GetFontUnicodeRanges
extern "C" __declspec(naked) void __stdcall __E__479__()
{
	log("GetFontUnicodeRanges");
	__asm
	{
		jmp p[479 * 4];
	}
}

// GetGlyphIndicesA
extern "C" __declspec(naked) void __stdcall __E__480__()
{
	log("GetGlyphIndicesA");
	__asm
	{
		jmp p[480 * 4];
	}
}

// GetGlyphIndicesW
extern "C" __declspec(naked) void __stdcall __E__481__()
{
	log("GetGlyphIndicesW");
	__asm
	{
		jmp p[481 * 4];
	}
}

// GetGlyphOutline
extern "C" __declspec(naked) void __stdcall __E__482__()
{
	log("GetGlyphOutline");
	__asm
	{
		jmp p[482 * 4];
	}
}

// GetGlyphOutlineA
extern "C" __declspec(naked) void __stdcall __E__483__()
{
	log("GetGlyphOutlineA");
	__asm
	{
		jmp p[483 * 4];
	}
}

// GetGlyphOutlineW
extern "C" __declspec(naked) void __stdcall __E__484__()
{
	log("GetGlyphOutlineW");
	__asm
	{
		jmp p[484 * 4];
	}
}

// GetGlyphOutlineWow
extern "C" __declspec(naked) void __stdcall __E__485__()
{
	log("GetGlyphOutlineWow");
	__asm
	{
		jmp p[485 * 4];
	}
}

// GetGraphicsMode
extern "C" __declspec(naked) void __stdcall __E__486__()
{
	log("GetGraphicsMode");
	__asm
	{
		jmp p[486 * 4];
	}
}

// GetHFONT
extern "C" __declspec(naked) void __stdcall __E__487__()
{
	log("GetHFONT");
	__asm
	{
		jmp p[487 * 4];
	}
}

// GetICMProfileA
extern "C" __declspec(naked) void __stdcall __E__488__()
{
	log("GetICMProfileA");
	__asm
	{
		jmp p[488 * 4];
	}
}

// GetICMProfileW
extern "C" __declspec(naked) void __stdcall __E__489__()
{
	log("GetICMProfileW");
	__asm
	{
		jmp p[489 * 4];
	}
}

// GetKerningPairs
extern "C" __declspec(naked) void __stdcall __E__490__()
{
	log("GetKerningPairs");
	__asm
	{
		jmp p[490 * 4];
	}
}

// GetKerningPairsA
extern "C" __declspec(naked) void __stdcall __E__491__()
{
	log("GetKerningPairsA");
	__asm
	{
		jmp p[491 * 4];
	}
}

// GetKerningPairsW
extern "C" __declspec(naked) void __stdcall __E__492__()
{
	log("GetKerningPairsW");
	__asm
	{
		jmp p[492 * 4];
	}
}

// GetLayout
extern "C" __declspec(naked) void __stdcall __E__493__()
{
	log("GetLayout");
	__asm
	{
		jmp p[493 * 4];
	}
}

// GetLogColorSpaceA
extern "C" __declspec(naked) void __stdcall __E__494__()
{
	log("GetLogColorSpaceA");
	__asm
	{
		jmp p[494 * 4];
	}
}

// GetLogColorSpaceW
extern "C" __declspec(naked) void __stdcall __E__495__()
{
	log("GetLogColorSpaceW");
	__asm
	{
		jmp p[495 * 4];
	}
}

// GetMapMode
extern "C" __declspec(naked) void __stdcall __E__496__()
{
	log("GetMapMode");
	__asm
	{
		jmp p[496 * 4];
	}
}

// GetMetaFileA
extern "C" __declspec(naked) void __stdcall __E__497__()
{
	log("GetMetaFileA");
	__asm
	{
		jmp p[497 * 4];
	}
}

// GetMetaFileBitsEx
extern "C" __declspec(naked) void __stdcall __E__498__()
{
	log("GetMetaFileBitsEx");
	__asm
	{
		jmp p[498 * 4];
	}
}

// GetMetaFileW
extern "C" __declspec(naked) void __stdcall __E__499__()
{
	log("GetMetaFileW");
	__asm
	{
		jmp p[499 * 4];
	}
}

// GetMetaRgn
extern "C" __declspec(naked) void __stdcall __E__500__()
{
	log("GetMetaRgn");
	__asm
	{
		jmp p[500 * 4];
	}
}

// GetMiterLimit
extern "C" __declspec(naked) void __stdcall __E__501__()
{
	log("GetMiterLimit");
	__asm
	{
		jmp p[501 * 4];
	}
}

// GetNearestColor
extern "C" __declspec(naked) void __stdcall __E__502__()
{
	log("GetNearestColor");
	__asm
	{
		jmp p[502 * 4];
	}
}

// GetNearestPaletteIndex
extern "C" __declspec(naked) void __stdcall __E__503__()
{
	log("GetNearestPaletteIndex");
	__asm
	{
		jmp p[503 * 4];
	}
}

// GetNumberOfPhysicalMonitors
extern "C" __declspec(naked) void __stdcall __E__504__()
{
	log("GetNumberOfPhysicalMonitors");
	__asm
	{
		jmp p[504 * 4];
	}
}

// GetOPMInformation
extern "C" __declspec(naked) void __stdcall __E__505__()
{
	log("GetOPMInformation");
	__asm
	{
		jmp p[505 * 4];
	}
}

// GetOPMRandomNumber
extern "C" __declspec(naked) void __stdcall __E__506__()
{
	log("GetOPMRandomNumber");
	__asm
	{
		jmp p[506 * 4];
	}
}

// GetObjectA
extern "C" __declspec(naked) void __stdcall __E__507__()
{
	log("GetObjectA");
	__asm
	{
		jmp p[507 * 4];
	}
}

// GetObjectType
extern "C" __declspec(naked) void __stdcall __E__508__()
{
	log("GetObjectType");
	__asm
	{
		jmp p[508 * 4];
	}
}

// GetObjectW
extern "C" __declspec(naked) void __stdcall __E__509__()
{
	log("GetObjectW");
	__asm
	{
		jmp p[509 * 4];
	}
}

// GetOutlineTextMetricsA
extern "C" __declspec(naked) void __stdcall __E__510__()
{
	log("GetOutlineTextMetricsA");
	__asm
	{
		jmp p[510 * 4];
	}
}

// GetOutlineTextMetricsW
extern "C" __declspec(naked) void __stdcall __E__511__()
{
	log("GetOutlineTextMetricsW");
	__asm
	{
		jmp p[511 * 4];
	}
}

// GetPaletteEntries
extern "C" __declspec(naked) void __stdcall __E__512__()
{
	log("GetPaletteEntries");
	__asm
	{
		jmp p[512 * 4];
	}
}

// GetPath
extern "C" __declspec(naked) void __stdcall __E__513__()
{
	log("GetPath");
	__asm
	{
		jmp p[513 * 4];
	}
}

// GetPhysicalMonitorDescription
extern "C" __declspec(naked) void __stdcall __E__514__()
{
	log("GetPhysicalMonitorDescription");
	__asm
	{
		jmp p[514 * 4];
	}
}

// GetPhysicalMonitors
extern "C" __declspec(naked) void __stdcall __E__515__()
{
	log("GetPhysicalMonitors");
	__asm
	{
		jmp p[515 * 4];
	}
}

// GetPixel
extern "C" __declspec(naked) void __stdcall __E__516__()
{
	log("GetPixel");
	__asm
	{
		jmp p[516 * 4];
	}
}

// GetPixelFormat
extern "C" __declspec(naked) void __stdcall __E__517__()
{
	log("GetPixelFormat");
	__asm
	{
		jmp p[517 * 4];
	}
}

// GetPolyFillMode
extern "C" __declspec(naked) void __stdcall __E__518__()
{
	log("GetPolyFillMode");
	__asm
	{
		jmp p[518 * 4];
	}
}

// GetROP2
extern "C" __declspec(naked) void __stdcall __E__519__()
{
	log("GetROP2");
	__asm
	{
		jmp p[519 * 4];
	}
}

// GetRandomRgn
extern "C" __declspec(naked) void __stdcall __E__520__()
{
	log("GetRandomRgn");
	__asm
	{
		jmp p[520 * 4];
	}
}

// GetRasterizerCaps
extern "C" __declspec(naked) void __stdcall __E__521__()
{
	log("GetRasterizerCaps");
	__asm
	{
		jmp p[521 * 4];
	}
}

// GetRegionData
extern "C" __declspec(naked) void __stdcall __E__522__()
{
	log("GetRegionData");
	__asm
	{
		jmp p[522 * 4];
	}
}

// GetRelAbs
extern "C" __declspec(naked) void __stdcall __E__523__()
{
	log("GetRelAbs");
	__asm
	{
		jmp p[523 * 4];
	}
}

// GetRgnBox
extern "C" __declspec(naked) void __stdcall __E__524__()
{
	log("GetRgnBox");
	__asm
	{
		jmp p[524 * 4];
	}
}

// GetStockObject
extern "C" __declspec(naked) void __stdcall __E__525__()
{
	log("GetStockObject");
	__asm
	{
		jmp p[525 * 4];
	}
}

// GetStretchBltMode
extern "C" __declspec(naked) void __stdcall __E__526__()
{
	log("GetStretchBltMode");
	__asm
	{
		jmp p[526 * 4];
	}
}

// GetStringBitmapA
extern "C" __declspec(naked) void __stdcall __E__527__()
{
	log("GetStringBitmapA");
	__asm
	{
		jmp p[527 * 4];
	}
}

// GetStringBitmapW
extern "C" __declspec(naked) void __stdcall __E__528__()
{
	log("GetStringBitmapW");
	__asm
	{
		jmp p[528 * 4];
	}
}

// GetSuggestedOPMProtectedOutputArraySize
extern "C" __declspec(naked) void __stdcall __E__529__()
{
	log("GetSuggestedOPMProtectedOutputArraySize");
	__asm
	{
		jmp p[529 * 4];
	}
}

// GetSystemPaletteEntries
extern "C" __declspec(naked) void __stdcall __E__530__()
{
	log("GetSystemPaletteEntries");
	__asm
	{
		jmp p[530 * 4];
	}
}

// GetSystemPaletteUse
extern "C" __declspec(naked) void __stdcall __E__531__()
{
	log("GetSystemPaletteUse");
	__asm
	{
		jmp p[531 * 4];
	}
}

// GetTextAlign
extern "C" __declspec(naked) void __stdcall __E__532__()
{
	log("GetTextAlign");
	__asm
	{
		jmp p[532 * 4];
	}
}

// GetTextCharacterExtra
extern "C" __declspec(naked) void __stdcall __E__533__()
{
	log("GetTextCharacterExtra");
	__asm
	{
		jmp p[533 * 4];
	}
}

// GetTextCharset
extern "C" __declspec(naked) void __stdcall __E__534__()
{
	log("GetTextCharset");
	__asm
	{
		jmp p[534 * 4];
	}
}

// GetTextCharsetInfo
extern "C" __declspec(naked) void __stdcall __E__535__()
{
	log("GetTextCharsetInfo");
	__asm
	{
		jmp p[535 * 4];
	}
}

// GetTextColor
extern "C" __declspec(naked) void __stdcall __E__536__()
{
	log("GetTextColor");
	__asm
	{
		jmp p[536 * 4];
	}
}

// GetTextExtentExPointA
extern "C" __declspec(naked) void __stdcall __E__537__()
{
	log("GetTextExtentExPointA");
	__asm
	{
		jmp p[537 * 4];
	}
}

// GetTextExtentExPointI
extern "C" __declspec(naked) void __stdcall __E__538__()
{
	log("GetTextExtentExPointI");
	__asm
	{
		jmp p[538 * 4];
	}
}

// GetTextExtentExPointW
extern "C" __declspec(naked) void __stdcall __E__539__()
{
	log("GetTextExtentExPointW");
	__asm
	{
		jmp p[539 * 4];
	}
}

// GetTextExtentExPointWPri
extern "C" __declspec(naked) void __stdcall __E__540__()
{
	log("GetTextExtentExPointWPri");
	__asm
	{
		jmp p[540 * 4];
	}
}

// GetTextExtentPoint32A
extern "C" __declspec(naked) void __stdcall __E__541__()
{
	log("GetTextExtentPoint32A");
	__asm
	{
		jmp p[541 * 4];
	}
}

// GetTextExtentPoint32W
extern "C" __declspec(naked) void __stdcall __E__542__()
{
	log("GetTextExtentPoint32W");
	__asm
	{
		jmp p[542 * 4];
	}
}

// GetTextExtentPointA
extern "C" __declspec(naked) void __stdcall __E__543__()
{
	log("GetTextExtentPointA");
	__asm
	{
		jmp p[543 * 4];
	}
}

// GetTextExtentPointI
extern "C" __declspec(naked) void __stdcall __E__544__()
{
	log("GetTextExtentPointI");
	__asm
	{
		jmp p[544 * 4];
	}
}

// GetTextExtentPointW
extern "C" __declspec(naked) void __stdcall __E__545__()
{
	log("GetTextExtentPointW");
	__asm
	{
		jmp p[545 * 4];
	}
}

// GetTextFaceA
extern "C" __declspec(naked) void __stdcall __E__546__()
{
	log("GetTextFaceA");
	__asm
	{
		jmp p[546 * 4];
	}
}

// GetTextFaceAliasW
extern "C" __declspec(naked) void __stdcall __E__547__()
{
	log("GetTextFaceAliasW");
	__asm
	{
		jmp p[547 * 4];
	}
}

// GetTextFaceW
extern "C" __declspec(naked) void __stdcall __E__548__()
{
	log("GetTextFaceW");
	__asm
	{
		jmp p[548 * 4];
	}
}

// GetTextMetricsA
extern "C" __declspec(naked) void __stdcall __E__549__()
{
	log("GetTextMetricsA");
	__asm
	{
		jmp p[549 * 4];
	}
}

// GetTextMetricsW
extern "C" __declspec(naked) void __stdcall __E__550__()
{
	log("GetTextMetricsW");
	__asm
	{
		jmp p[550 * 4];
	}
}

// GetTransform
extern "C" __declspec(naked) void __stdcall __E__551__()
{
	log("GetTransform");
	__asm
	{
		jmp p[551 * 4];
	}
}

// GetViewportExtEx
extern "C" __declspec(naked) void __stdcall __E__552__()
{
	log("GetViewportExtEx");
	__asm
	{
		jmp p[552 * 4];
	}
}

// GetViewportOrgEx
extern "C" __declspec(naked) void __stdcall __E__553__()
{
	log("GetViewportOrgEx");
	__asm
	{
		jmp p[553 * 4];
	}
}

// GetWinMetaFileBits
extern "C" __declspec(naked) void __stdcall __E__554__()
{
	log("GetWinMetaFileBits");
	__asm
	{
		jmp p[554 * 4];
	}
}

// GetWindowExtEx
extern "C" __declspec(naked) void __stdcall __E__555__()
{
	log("GetWindowExtEx");
	__asm
	{
		jmp p[555 * 4];
	}
}

// GetWindowOrgEx
extern "C" __declspec(naked) void __stdcall __E__556__()
{
	log("GetWindowOrgEx");
	__asm
	{
		jmp p[556 * 4];
	}
}

// GetWorldTransform
extern "C" __declspec(naked) void __stdcall __E__557__()
{
	log("GetWorldTransform");
	__asm
	{
		jmp p[557 * 4];
	}
}

// HT_Get8BPPFormatPalette
extern "C" __declspec(naked) void __stdcall __E__558__()
{
	log("HT_Get8BPPFormatPalette");
	__asm
	{
		jmp p[558 * 4];
	}
}

// HT_Get8BPPMaskPalette
extern "C" __declspec(naked) void __stdcall __E__559__()
{
	log("HT_Get8BPPMaskPalette");
	__asm
	{
		jmp p[559 * 4];
	}
}

// IntersectClipRect
extern "C" __declspec(naked) void __stdcall __E__560__()
{
	log("IntersectClipRect");
	__asm
	{
		jmp p[560 * 4];
	}
}

// InvertRgn
extern "C" __declspec(naked) void __stdcall __E__561__()
{
	log("InvertRgn");
	__asm
	{
		jmp p[561 * 4];
	}
}

// IsValidEnhMetaRecord
extern "C" __declspec(naked) void __stdcall __E__562__()
{
	log("IsValidEnhMetaRecord");
	__asm
	{
		jmp p[562 * 4];
	}
}

// IsValidEnhMetaRecordOffExt
extern "C" __declspec(naked) void __stdcall __E__563__()
{
	log("IsValidEnhMetaRecordOffExt");
	__asm
	{
		jmp p[563 * 4];
	}
}

// LPtoDP
extern "C" __declspec(naked) void __stdcall __E__564__()
{
	log("LPtoDP");
	__asm
	{
		jmp p[564 * 4];
	}
}

// LineDDA
extern "C" __declspec(naked) void __stdcall __E__565__()
{
	log("LineDDA");
	__asm
	{
		jmp p[565 * 4];
	}
}

// LineTo
extern "C" __declspec(naked) void __stdcall __E__566__()
{
	log("LineTo");
	__asm
	{
		jmp p[566 * 4];
	}
}

// MaskBlt
extern "C" __declspec(naked) void __stdcall __E__567__()
{
	log("MaskBlt");
	__asm
	{
		jmp p[567 * 4];
	}
}

// MirrorRgn
extern "C" __declspec(naked) void __stdcall __E__568__()
{
	log("MirrorRgn");
	__asm
	{
		jmp p[568 * 4];
	}
}

// ModifyWorldTransform
extern "C" __declspec(naked) void __stdcall __E__569__()
{
	log("ModifyWorldTransform");
	__asm
	{
		jmp p[569 * 4];
	}
}

// MoveToEx
extern "C" __declspec(naked) void __stdcall __E__570__()
{
	log("MoveToEx");
	__asm
	{
		jmp p[570 * 4];
	}
}

// NamedEscape
extern "C" __declspec(naked) void __stdcall __E__571__()
{
	log("NamedEscape");
	__asm
	{
		jmp p[571 * 4];
	}
}

// OffsetClipRgn
extern "C" __declspec(naked) void __stdcall __E__572__()
{
	log("OffsetClipRgn");
	__asm
	{
		jmp p[572 * 4];
	}
}

// OffsetRgn
extern "C" __declspec(naked) void __stdcall __E__573__()
{
	log("OffsetRgn");
	__asm
	{
		jmp p[573 * 4];
	}
}

// OffsetViewportOrgEx
extern "C" __declspec(naked) void __stdcall __E__574__()
{
	log("OffsetViewportOrgEx");
	__asm
	{
		jmp p[574 * 4];
	}
}

// OffsetWindowOrgEx
extern "C" __declspec(naked) void __stdcall __E__575__()
{
	log("OffsetWindowOrgEx");
	__asm
	{
		jmp p[575 * 4];
	}
}

// PATHOBJ_bEnum
extern "C" __declspec(naked) void __stdcall __E__576__()
{
	log("PATHOBJ_bEnum");
	__asm
	{
		jmp p[576 * 4];
	}
}

// PATHOBJ_bEnumClipLines
extern "C" __declspec(naked) void __stdcall __E__577__()
{
	log("PATHOBJ_bEnumClipLines");
	__asm
	{
		jmp p[577 * 4];
	}
}

// PATHOBJ_vEnumStart
extern "C" __declspec(naked) void __stdcall __E__578__()
{
	log("PATHOBJ_vEnumStart");
	__asm
	{
		jmp p[578 * 4];
	}
}

// PATHOBJ_vEnumStartClipLines
extern "C" __declspec(naked) void __stdcall __E__579__()
{
	log("PATHOBJ_vEnumStartClipLines");
	__asm
	{
		jmp p[579 * 4];
	}
}

// PATHOBJ_vGetBounds
extern "C" __declspec(naked) void __stdcall __E__580__()
{
	log("PATHOBJ_vGetBounds");
	__asm
	{
		jmp p[580 * 4];
	}
}

// PaintRgn
extern "C" __declspec(naked) void __stdcall __E__581__()
{
	log("PaintRgn");
	__asm
	{
		jmp p[581 * 4];
	}
}

// PatBlt
extern "C" __declspec(naked) void __stdcall __E__582__()
{
	log("PatBlt");
	__asm
	{
		jmp p[582 * 4];
	}
}

// PathToRegion
extern "C" __declspec(naked) void __stdcall __E__583__()
{
	log("PathToRegion");
	__asm
	{
		jmp p[583 * 4];
	}
}

// Pie
extern "C" __declspec(naked) void __stdcall __E__584__()
{
	log("Pie");
	__asm
	{
		jmp p[584 * 4];
	}
}

// PlayEnhMetaFile
extern "C" __declspec(naked) void __stdcall __E__585__()
{
	log("PlayEnhMetaFile");
	__asm
	{
		jmp p[585 * 4];
	}
}

// PlayEnhMetaFileRecord
extern "C" __declspec(naked) void __stdcall __E__586__()
{
	log("PlayEnhMetaFileRecord");
	__asm
	{
		jmp p[586 * 4];
	}
}

// PlayMetaFile
extern "C" __declspec(naked) void __stdcall __E__587__()
{
	log("PlayMetaFile");
	__asm
	{
		jmp p[587 * 4];
	}
}

// PlayMetaFileRecord
extern "C" __declspec(naked) void __stdcall __E__588__()
{
	log("PlayMetaFileRecord");
	__asm
	{
		jmp p[588 * 4];
	}
}

// PlgBlt
extern "C" __declspec(naked) void __stdcall __E__589__()
{
	log("PlgBlt");
	__asm
	{
		jmp p[589 * 4];
	}
}

// PolyBezier
extern "C" __declspec(naked) void __stdcall __E__590__()
{
	log("PolyBezier");
	__asm
	{
		jmp p[590 * 4];
	}
}

// PolyBezierTo
extern "C" __declspec(naked) void __stdcall __E__591__()
{
	log("PolyBezierTo");
	__asm
	{
		jmp p[591 * 4];
	}
}

// PolyDraw
extern "C" __declspec(naked) void __stdcall __E__592__()
{
	log("PolyDraw");
	__asm
	{
		jmp p[592 * 4];
	}
}

// PolyPatBlt
extern "C" __declspec(naked) void __stdcall __E__593__()
{
	log("PolyPatBlt");
	__asm
	{
		jmp p[593 * 4];
	}
}

// PolyPolygon
extern "C" __declspec(naked) void __stdcall __E__594__()
{
	log("PolyPolygon");
	__asm
	{
		jmp p[594 * 4];
	}
}

// PolyPolyline
extern "C" __declspec(naked) void __stdcall __E__595__()
{
	log("PolyPolyline");
	__asm
	{
		jmp p[595 * 4];
	}
}

// PolyTextOutA
extern "C" __declspec(naked) void __stdcall __E__596__()
{
	log("PolyTextOutA");
	__asm
	{
		jmp p[596 * 4];
	}
}

// PolyTextOutW
extern "C" __declspec(naked) void __stdcall __E__597__()
{
	log("PolyTextOutW");
	__asm
	{
		jmp p[597 * 4];
	}
}

// Polygon
extern "C" __declspec(naked) void __stdcall __E__598__()
{
	log("Polygon");
	__asm
	{
		jmp p[598 * 4];
	}
}

// Polyline
extern "C" __declspec(naked) void __stdcall __E__599__()
{
	log("Polyline");
	__asm
	{
		jmp p[599 * 4];
	}
}

// PolylineTo
extern "C" __declspec(naked) void __stdcall __E__600__()
{
	log("PolylineTo");
	__asm
	{
		jmp p[600 * 4];
	}
}

// PtInRegion
extern "C" __declspec(naked) void __stdcall __E__601__()
{
	log("PtInRegion");
	__asm
	{
		jmp p[601 * 4];
	}
}

// PtVisible
extern "C" __declspec(naked) void __stdcall __E__602__()
{
	log("PtVisible");
	__asm
	{
		jmp p[602 * 4];
	}
}

// QueryFontAssocStatus
extern "C" __declspec(naked) void __stdcall __E__603__()
{
	log("QueryFontAssocStatus");
	__asm
	{
		jmp p[603 * 4];
	}
}

// RealizePalette
extern "C" __declspec(naked) void __stdcall __E__604__()
{
	log("RealizePalette");
	__asm
	{
		jmp p[604 * 4];
	}
}

// RectInRegion
extern "C" __declspec(naked) void __stdcall __E__605__()
{
	log("RectInRegion");
	__asm
	{
		jmp p[605 * 4];
	}
}

// RectVisible
extern "C" __declspec(naked) void __stdcall __E__606__()
{
	log("RectVisible");
	__asm
	{
		jmp p[606 * 4];
	}
}

// Rectangle
extern "C" __declspec(naked) void __stdcall __E__607__()
{
	log("Rectangle");
	__asm
	{
		jmp p[607 * 4];
	}
}

// RemoveFontMemResourceEx
extern "C" __declspec(naked) void __stdcall __E__608__()
{
	log("RemoveFontMemResourceEx");
	__asm
	{
		jmp p[608 * 4];
	}
}

// RemoveFontResourceA
extern "C" __declspec(naked) void __stdcall __E__609__()
{
	log("RemoveFontResourceA");
	__asm
	{
		jmp p[609 * 4];
	}
}

// RemoveFontResourceExA
extern "C" __declspec(naked) void __stdcall __E__610__()
{
	log("RemoveFontResourceExA");
	__asm
	{
		jmp p[610 * 4];
	}
}

// RemoveFontResourceExW
extern "C" __declspec(naked) void __stdcall __E__611__()
{
	log("RemoveFontResourceExW");
	__asm
	{
		jmp p[611 * 4];
	}
}

// RemoveFontResourceTracking
extern "C" __declspec(naked) void __stdcall __E__612__()
{
	log("RemoveFontResourceTracking");
	__asm
	{
		jmp p[612 * 4];
	}
}

// RemoveFontResourceW
extern "C" __declspec(naked) void __stdcall __E__613__()
{
	log("RemoveFontResourceW");
	__asm
	{
		jmp p[613 * 4];
	}
}

// ResetDCA
extern "C" __declspec(naked) void __stdcall __E__614__()
{
	log("ResetDCA");
	__asm
	{
		jmp p[614 * 4];
	}
}

// ResetDCW
extern "C" __declspec(naked) void __stdcall __E__615__()
{
	log("ResetDCW");
	__asm
	{
		jmp p[615 * 4];
	}
}

// ResizePalette
extern "C" __declspec(naked) void __stdcall __E__616__()
{
	log("ResizePalette");
	__asm
	{
		jmp p[616 * 4];
	}
}

// RestoreDC
extern "C" __declspec(naked) void __stdcall __E__617__()
{
	log("RestoreDC");
	__asm
	{
		jmp p[617 * 4];
	}
}

// RoundRect
extern "C" __declspec(naked) void __stdcall __E__618__()
{
	log("RoundRect");
	__asm
	{
		jmp p[618 * 4];
	}
}

// STROBJ_bEnum
extern "C" __declspec(naked) void __stdcall __E__619__()
{
	log("STROBJ_bEnum");
	__asm
	{
		jmp p[619 * 4];
	}
}

// STROBJ_bEnumPositionsOnly
extern "C" __declspec(naked) void __stdcall __E__620__()
{
	log("STROBJ_bEnumPositionsOnly");
	__asm
	{
		jmp p[620 * 4];
	}
}

// STROBJ_bGetAdvanceWidths
extern "C" __declspec(naked) void __stdcall __E__621__()
{
	log("STROBJ_bGetAdvanceWidths");
	__asm
	{
		jmp p[621 * 4];
	}
}

// STROBJ_dwGetCodePage
extern "C" __declspec(naked) void __stdcall __E__622__()
{
	log("STROBJ_dwGetCodePage");
	__asm
	{
		jmp p[622 * 4];
	}
}

// STROBJ_vEnumStart
extern "C" __declspec(naked) void __stdcall __E__623__()
{
	log("STROBJ_vEnumStart");
	__asm
	{
		jmp p[623 * 4];
	}
}

// SaveDC
extern "C" __declspec(naked) void __stdcall __E__624__()
{
	log("SaveDC");
	__asm
	{
		jmp p[624 * 4];
	}
}

// ScaleViewportExtEx
extern "C" __declspec(naked) void __stdcall __E__625__()
{
	log("ScaleViewportExtEx");
	__asm
	{
		jmp p[625 * 4];
	}
}

// ScaleWindowExtEx
extern "C" __declspec(naked) void __stdcall __E__626__()
{
	log("ScaleWindowExtEx");
	__asm
	{
		jmp p[626 * 4];
	}
}

// SelectBrushLocal
extern "C" __declspec(naked) void __stdcall __E__627__()
{
	log("SelectBrushLocal");
	__asm
	{
		jmp p[627 * 4];
	}
}

// SelectClipPath
extern "C" __declspec(naked) void __stdcall __E__628__()
{
	log("SelectClipPath");
	__asm
	{
		jmp p[628 * 4];
	}
}

// SelectClipRgn
extern "C" __declspec(naked) void __stdcall __E__629__()
{
	log("SelectClipRgn");
	__asm
	{
		jmp p[629 * 4];
	}
}

// SelectFontLocal
extern "C" __declspec(naked) void __stdcall __E__630__()
{
	log("SelectFontLocal");
	__asm
	{
		jmp p[630 * 4];
	}
}

// SelectObject
extern "C" __declspec(naked) void __stdcall __E__631__()
{
	log("SelectObject");
	__asm
	{
		jmp p[631 * 4];
	}
}

// SelectPalette
extern "C" __declspec(naked) void __stdcall __E__632__()
{
	log("SelectPalette");
	__asm
	{
		jmp p[632 * 4];
	}
}

// SetAbortProc
extern "C" __declspec(naked) void __stdcall __E__633__()
{
	log("SetAbortProc");
	__asm
	{
		jmp p[633 * 4];
	}
}

// SetArcDirection
extern "C" __declspec(naked) void __stdcall __E__634__()
{
	log("SetArcDirection");
	__asm
	{
		jmp p[634 * 4];
	}
}

// SetBitmapAttributes
extern "C" __declspec(naked) void __stdcall __E__635__()
{
	log("SetBitmapAttributes");
	__asm
	{
		jmp p[635 * 4];
	}
}

// SetBitmapBits
extern "C" __declspec(naked) void __stdcall __E__636__()
{
	log("SetBitmapBits");
	__asm
	{
		jmp p[636 * 4];
	}
}

// SetBitmapDimensionEx
extern "C" __declspec(naked) void __stdcall __E__637__()
{
	log("SetBitmapDimensionEx");
	__asm
	{
		jmp p[637 * 4];
	}
}

// SetBkColor
extern "C" __declspec(naked) void __stdcall __E__638__()
{
	log("SetBkColor");
	__asm
	{
		jmp p[638 * 4];
	}
}

// SetBkMode
extern "C" __declspec(naked) void __stdcall __E__639__()
{
	log("SetBkMode");
	__asm
	{
		jmp p[639 * 4];
	}
}

// SetBoundsRect
extern "C" __declspec(naked) void __stdcall __E__640__()
{
	log("SetBoundsRect");
	__asm
	{
		jmp p[640 * 4];
	}
}

// SetBrushAttributes
extern "C" __declspec(naked) void __stdcall __E__641__()
{
	log("SetBrushAttributes");
	__asm
	{
		jmp p[641 * 4];
	}
}

// SetBrushOrgEx
extern "C" __declspec(naked) void __stdcall __E__642__()
{
	log("SetBrushOrgEx");
	__asm
	{
		jmp p[642 * 4];
	}
}

// SetColorAdjustment
extern "C" __declspec(naked) void __stdcall __E__643__()
{
	log("SetColorAdjustment");
	__asm
	{
		jmp p[643 * 4];
	}
}

// SetColorSpace
extern "C" __declspec(naked) void __stdcall __E__644__()
{
	log("SetColorSpace");
	__asm
	{
		jmp p[644 * 4];
	}
}

// SetDCBrushColor
extern "C" __declspec(naked) void __stdcall __E__645__()
{
	log("SetDCBrushColor");
	__asm
	{
		jmp p[645 * 4];
	}
}

// SetDCPenColor
extern "C" __declspec(naked) void __stdcall __E__646__()
{
	log("SetDCPenColor");
	__asm
	{
		jmp p[646 * 4];
	}
}

// SetDIBColorTable
extern "C" __declspec(naked) void __stdcall __E__647__()
{
	log("SetDIBColorTable");
	__asm
	{
		jmp p[647 * 4];
	}
}

// SetDIBits
extern "C" __declspec(naked) void __stdcall __E__648__()
{
	log("SetDIBits");
	__asm
	{
		jmp p[648 * 4];
	}
}

// SetDIBitsToDevice
extern "C" __declspec(naked) void __stdcall __E__649__()
{
	log("SetDIBitsToDevice");
	__asm
	{
		jmp p[649 * 4];
	}
}

// SetDeviceGammaRamp
extern "C" __declspec(naked) void __stdcall __E__650__()
{
	log("SetDeviceGammaRamp");
	__asm
	{
		jmp p[650 * 4];
	}
}

// SetEnhMetaFileBits
extern "C" __declspec(naked) void __stdcall __E__651__()
{
	log("SetEnhMetaFileBits");
	__asm
	{
		jmp p[651 * 4];
	}
}

// SetFontEnumeration
extern "C" __declspec(naked) void __stdcall __E__652__()
{
	log("SetFontEnumeration");
	__asm
	{
		jmp p[652 * 4];
	}
}

// SetGraphicsMode
extern "C" __declspec(naked) void __stdcall __E__653__()
{
	log("SetGraphicsMode");
	__asm
	{
		jmp p[653 * 4];
	}
}

// SetICMMode
extern "C" __declspec(naked) void __stdcall __E__654__()
{
	log("SetICMMode");
	__asm
	{
		jmp p[654 * 4];
	}
}

// SetICMProfileA
extern "C" __declspec(naked) void __stdcall __E__655__()
{
	log("SetICMProfileA");
	__asm
	{
		jmp p[655 * 4];
	}
}

// SetICMProfileW
extern "C" __declspec(naked) void __stdcall __E__656__()
{
	log("SetICMProfileW");
	__asm
	{
		jmp p[656 * 4];
	}
}

// SetLayout
extern "C" __declspec(naked) void __stdcall __E__657__()
{
	log("SetLayout");
	__asm
	{
		jmp p[657 * 4];
	}
}

// SetLayoutWidth
extern "C" __declspec(naked) void __stdcall __E__658__()
{
	log("SetLayoutWidth");
	__asm
	{
		jmp p[658 * 4];
	}
}

// SetMagicColors
extern "C" __declspec(naked) void __stdcall __E__659__()
{
	log("SetMagicColors");
	__asm
	{
		jmp p[659 * 4];
	}
}

// SetMapMode
extern "C" __declspec(naked) void __stdcall __E__660__()
{
	log("SetMapMode");
	__asm
	{
		jmp p[660 * 4];
	}
}

// SetMapperFlags
extern "C" __declspec(naked) void __stdcall __E__661__()
{
	log("SetMapperFlags");
	__asm
	{
		jmp p[661 * 4];
	}
}

// SetMetaFileBitsEx
extern "C" __declspec(naked) void __stdcall __E__662__()
{
	log("SetMetaFileBitsEx");
	__asm
	{
		jmp p[662 * 4];
	}
}

// SetMetaRgn
extern "C" __declspec(naked) void __stdcall __E__663__()
{
	log("SetMetaRgn");
	__asm
	{
		jmp p[663 * 4];
	}
}

// SetMiterLimit
extern "C" __declspec(naked) void __stdcall __E__664__()
{
	log("SetMiterLimit");
	__asm
	{
		jmp p[664 * 4];
	}
}

// SetOPMSigningKeyAndSequenceNumbers
extern "C" __declspec(naked) void __stdcall __E__665__()
{
	log("SetOPMSigningKeyAndSequenceNumbers");
	__asm
	{
		jmp p[665 * 4];
	}
}

// SetPaletteEntries
extern "C" __declspec(naked) void __stdcall __E__666__()
{
	log("SetPaletteEntries");
	__asm
	{
		jmp p[666 * 4];
	}
}

// SetPixel
extern "C" __declspec(naked) void __stdcall __E__667__()
{
	log("SetPixel");
	__asm
	{
		jmp p[667 * 4];
	}
}

// SetPixelFormat
extern "C" __declspec(naked) void __stdcall __E__668__()
{
	log("SetPixelFormat");
	__asm
	{
		jmp p[668 * 4];
	}
}

// SetPixelV
extern "C" __declspec(naked) void __stdcall __E__669__()
{
	log("SetPixelV");
	__asm
	{
		jmp p[669 * 4];
	}
}

// SetPolyFillMode
extern "C" __declspec(naked) void __stdcall __E__670__()
{
	log("SetPolyFillMode");
	__asm
	{
		jmp p[670 * 4];
	}
}

// SetROP2
extern "C" __declspec(naked) void __stdcall __E__671__()
{
	log("SetROP2");
	__asm
	{
		jmp p[671 * 4];
	}
}

// SetRectRgn
extern "C" __declspec(naked) void __stdcall __E__672__()
{
	log("SetRectRgn");
	__asm
	{
		jmp p[672 * 4];
	}
}

// SetRelAbs
extern "C" __declspec(naked) void __stdcall __E__673__()
{
	log("SetRelAbs");
	__asm
	{
		jmp p[673 * 4];
	}
}

// SetStretchBltMode
extern "C" __declspec(naked) void __stdcall __E__674__()
{
	log("SetStretchBltMode");
	__asm
	{
		jmp p[674 * 4];
	}
}

// SetSystemPaletteUse
extern "C" __declspec(naked) void __stdcall __E__675__()
{
	log("SetSystemPaletteUse");
	__asm
	{
		jmp p[675 * 4];
	}
}

// SetTextAlign
extern "C" __declspec(naked) void __stdcall __E__676__()
{
	log("SetTextAlign");
	__asm
	{
		jmp p[676 * 4];
	}
}

// SetTextCharacterExtra
extern "C" __declspec(naked) void __stdcall __E__677__()
{
	log("SetTextCharacterExtra");
	__asm
	{
		jmp p[677 * 4];
	}
}

// SetTextColor
extern "C" __declspec(naked) void __stdcall __E__678__()
{
	log("SetTextColor");
	__asm
	{
		jmp p[678 * 4];
	}
}

// SetTextJustification
extern "C" __declspec(naked) void __stdcall __E__679__()
{
	log("SetTextJustification");
	__asm
	{
		jmp p[679 * 4];
	}
}

// SetViewportExtEx
extern "C" __declspec(naked) void __stdcall __E__680__()
{
	log("SetViewportExtEx");
	__asm
	{
		jmp p[680 * 4];
	}
}

// SetViewportOrgEx
extern "C" __declspec(naked) void __stdcall __E__681__()
{
	log("SetViewportOrgEx");
	__asm
	{
		jmp p[681 * 4];
	}
}

// SetVirtualResolution
extern "C" __declspec(naked) void __stdcall __E__682__()
{
	log("SetVirtualResolution");
	__asm
	{
		jmp p[682 * 4];
	}
}

// SetWinMetaFileBits
extern "C" __declspec(naked) void __stdcall __E__683__()
{
	log("SetWinMetaFileBits");
	__asm
	{
		jmp p[683 * 4];
	}
}

// SetWindowExtEx
extern "C" __declspec(naked) void __stdcall __E__684__()
{
	log("SetWindowExtEx");
	__asm
	{
		jmp p[684 * 4];
	}
}

// SetWindowOrgEx
extern "C" __declspec(naked) void __stdcall __E__685__()
{
	log("SetWindowOrgEx");
	__asm
	{
		jmp p[685 * 4];
	}
}

// SetWorldTransform
extern "C" __declspec(naked) void __stdcall __E__686__()
{
	log("SetWorldTransform");
	__asm
	{
		jmp p[686 * 4];
	}
}

// StartDocA
extern "C" __declspec(naked) void __stdcall __E__687__()
{
	log("StartDocA");
	__asm
	{
		jmp p[687 * 4];
	}
}

// StartDocW
extern "C" __declspec(naked) void __stdcall __E__688__()
{
	log("StartDocW");
	__asm
	{
		jmp p[688 * 4];
	}
}

// StartFormPage
extern "C" __declspec(naked) void __stdcall __E__689__()
{
	log("StartFormPage");
	__asm
	{
		jmp p[689 * 4];
	}
}

// StartPage
extern "C" __declspec(naked) void __stdcall __E__690__()
{
	log("StartPage");
	__asm
	{
		jmp p[690 * 4];
	}
}

// StretchBlt
extern "C" __declspec(naked) void __stdcall __E__691__()
{
	log("StretchBlt");
	__asm
	{
		jmp p[691 * 4];
	}
}

// StretchDIBits
extern "C" __declspec(naked) void __stdcall __E__692__()
{
	log("StretchDIBits");
	__asm
	{
		jmp p[692 * 4];
	}
}

// StrokeAndFillPath
extern "C" __declspec(naked) void __stdcall __E__693__()
{
	log("StrokeAndFillPath");
	__asm
	{
		jmp p[693 * 4];
	}
}

// StrokePath
extern "C" __declspec(naked) void __stdcall __E__694__()
{
	log("StrokePath");
	__asm
	{
		jmp p[694 * 4];
	}
}

// SwapBuffers
extern "C" __declspec(naked) void __stdcall __E__695__()
{
	log("SwapBuffers");
	__asm
	{
		jmp p[695 * 4];
	}
}

// TextOutA
extern "C" __declspec(naked) void __stdcall __E__696__()
{
	log("TextOutA");
	__asm
	{
		jmp p[696 * 4];
	}
}

// TextOutW
extern "C" __declspec(naked) void __stdcall __E__697__()
{
	log("TextOutW");
	__asm
	{
		jmp p[697 * 4];
	}
}

// TranslateCharsetInfo
extern "C" __declspec(naked) void __stdcall __E__698__()
{
	log("TranslateCharsetInfo");
	__asm
	{
		jmp p[698 * 4];
	}
}

// UnloadNetworkFonts
extern "C" __declspec(naked) void __stdcall __E__699__()
{
	log("UnloadNetworkFonts");
	__asm
	{
		jmp p[699 * 4];
	}
}

// UnrealizeObject
extern "C" __declspec(naked) void __stdcall __E__700__()
{
	log("UnrealizeObject");
	__asm
	{
		jmp p[700 * 4];
	}
}

// UpdateColors
extern "C" __declspec(naked) void __stdcall __E__701__()
{
	log("UpdateColors");
	__asm
	{
		jmp p[701 * 4];
	}
}

// UpdateICMRegKeyA
extern "C" __declspec(naked) void __stdcall __E__702__()
{
	log("UpdateICMRegKeyA");
	__asm
	{
		jmp p[702 * 4];
	}
}

// UpdateICMRegKeyW
extern "C" __declspec(naked) void __stdcall __E__703__()
{
	log("UpdateICMRegKeyW");
	__asm
	{
		jmp p[703 * 4];
	}
}

// WidenPath
extern "C" __declspec(naked) void __stdcall __E__704__()
{
	log("WidenPath");
	__asm
	{
		jmp p[704 * 4];
	}
}

// XFORMOBJ_bApplyXform
extern "C" __declspec(naked) void __stdcall __E__705__()
{
	log("XFORMOBJ_bApplyXform");
	__asm
	{
		jmp p[705 * 4];
	}
}

// XFORMOBJ_iGetXform
extern "C" __declspec(naked) void __stdcall __E__706__()
{
	log("XFORMOBJ_iGetXform");
	__asm
	{
		jmp p[706 * 4];
	}
}

// XLATEOBJ_cGetPalette
extern "C" __declspec(naked) void __stdcall __E__707__()
{
	log("XLATEOBJ_cGetPalette");
	__asm
	{
		jmp p[707 * 4];
	}
}

// XLATEOBJ_hGetColorTransform
extern "C" __declspec(naked) void __stdcall __E__708__()
{
	log("XLATEOBJ_hGetColorTransform");
	__asm
	{
		jmp p[708 * 4];
	}
}

// XLATEOBJ_iXlate
extern "C" __declspec(naked) void __stdcall __E__709__()
{
	log("XLATEOBJ_iXlate");
	__asm
	{
		jmp p[709 * 4];
	}
}

// XLATEOBJ_piVector
extern "C" __declspec(naked) void __stdcall __E__710__()
{
	log("XLATEOBJ_piVector");
	__asm
	{
		jmp p[710 * 4];
	}
}

// bInitSystemAndFontsDirectoriesW
extern "C" __declspec(naked) void __stdcall __E__711__()
{
	log("bInitSystemAndFontsDirectoriesW");
	__asm
	{
		jmp p[711 * 4];
	}
}

// bMakePathNameW
extern "C" __declspec(naked) void __stdcall __E__712__()
{
	log("bMakePathNameW");
	__asm
	{
		jmp p[712 * 4];
	}
}

// cGetTTFFromFOT
extern "C" __declspec(naked) void __stdcall __E__713__()
{
	log("cGetTTFFromFOT");
	__asm
	{
		jmp p[713 * 4];
	}
}

// gdiPlaySpoolStream
extern "C" __declspec(naked) void __stdcall __E__714__()
{
	log("gdiPlaySpoolStream");
	__asm
	{
		jmp p[714 * 4];
	}
}

// ___XXX___716
extern "C" __declspec(naked) void __stdcall __E__715__()
{
	log("___XXX___716");
	__asm
	{
		jmp p[715 * 4];
	}
}

// ___XXX___717
extern "C" __declspec(naked) void __stdcall __E__716__()
{
	log("___XXX___717");
	__asm
	{
		jmp p[716 * 4];
	}
}

// ___XXX___718
extern "C" __declspec(naked) void __stdcall __E__717__()
{
	log("___XXX___718");
	__asm
	{
		jmp p[717 * 4];
	}
}

// ___XXX___719
extern "C" __declspec(naked) void __stdcall __E__718__()
{
	log("___XXX___719");
	__asm
	{
		jmp p[718 * 4];
	}
}

// ___XXX___720
extern "C" __declspec(naked) void __stdcall __E__719__()
{
	log("___XXX___720");
	__asm
	{
		jmp p[719 * 4];
	}
}

// ___XXX___721
extern "C" __declspec(naked) void __stdcall __E__720__()
{
	log("___XXX___721");
	__asm
	{
		jmp p[720 * 4];
	}
}

// ___XXX___722
extern "C" __declspec(naked) void __stdcall __E__721__()
{
	log("___XXX___722");
	__asm
	{
		jmp p[721 * 4];
	}
}

// ___XXX___723
extern "C" __declspec(naked) void __stdcall __E__722__()
{
	log("___XXX___723");
	__asm
	{
		jmp p[722 * 4];
	}
}

// ___XXX___724
extern "C" __declspec(naked) void __stdcall __E__723__()
{
	log("___XXX___724");
	__asm
	{
		jmp p[723 * 4];
	}
}

// ___XXX___725
extern "C" __declspec(naked) void __stdcall __E__724__()
{
	log("___XXX___725");
	__asm
	{
		jmp p[724 * 4];
	}
}

// ___XXX___726
extern "C" __declspec(naked) void __stdcall __E__725__()
{
	log("___XXX___726");
	__asm
	{
		jmp p[725 * 4];
	}
}

// ___XXX___727
extern "C" __declspec(naked) void __stdcall __E__726__()
{
	log("___XXX___727");
	__asm
	{
		jmp p[726 * 4];
	}
}

