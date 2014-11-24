#include "ProxyD3DX.h"
#include "ProxyID3DXFont.h"

HRESULT __stdcall ProxyID3DXFont::QueryInterface(REFIID iid, LPVOID *ppv)
{
	return original->QueryInterface(iid, ppv);
}

ULONG __stdcall ProxyID3DXFont::AddRef() {
	return original->AddRef();
}
ULONG __stdcall ProxyID3DXFont::Release() {
	return original->Release();
}

// ID3DXFont
HRESULT __stdcall ProxyID3DXFont::GetDevice(LPDIRECT3DDEVICE9 *ppDevice) {
	return original->GetDevice(ppDevice);
}
HRESULT __stdcall ProxyID3DXFont::GetDescA(D3DXFONT_DESCA *pDesc) {
	return original->GetDescA(pDesc);
}
HRESULT __stdcall ProxyID3DXFont::GetDescW(D3DXFONT_DESCW *pDesc) {
	return original->GetDescW(pDesc);
}
BOOL __stdcall ProxyID3DXFont::GetTextMetricsA(TEXTMETRICA *pTextMetrics) {
	return original->GetTextMetricsA(pTextMetrics);
}
BOOL __stdcall ProxyID3DXFont::GetTextMetricsW(TEXTMETRICW *pTextMetrics) {
	return original->GetTextMetricsW(pTextMetrics);
}

HDC __stdcall ProxyID3DXFont::GetDC() {
	return original->GetDC();
}
HRESULT __stdcall ProxyID3DXFont::GetGlyphData(UINT Glyph, LPDIRECT3DTEXTURE9 *ppTexture, RECT *pBlackBox, POINT *pCellInc) {
	return original->GetGlyphData(Glyph, ppTexture, pBlackBox, pCellInc);
}

HRESULT __stdcall ProxyID3DXFont::PreloadCharacters(UINT First, UINT Last) {
	return original->PreloadCharacters(First, Last);
}
HRESULT __stdcall ProxyID3DXFont::PreloadGlyphs(UINT First, UINT Last)  {
	return original->PreloadGlyphs(First, Last);
}
HRESULT __stdcall ProxyID3DXFont::PreloadTextA(LPCSTR pString, INT Count) {
	return original->PreloadTextA(pString, Count);
}
HRESULT __stdcall ProxyID3DXFont::PreloadTextW(LPCWSTR pString, INT Count) {
	return original->PreloadTextW(pString, Count);
}
INT __stdcall ProxyID3DXFont::DrawTextA(LPD3DXSPRITE pSprite, LPCSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color) {
	return original->DrawTextA(pSprite, pString, Count, pRect, Format, Color);
}
INT __stdcall ProxyID3DXFont::DrawTextW(LPD3DXSPRITE pSprite, LPCWSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color) {
	return original->DrawTextW(pSprite, pString, Count, pRect, Format, Color);
}

HRESULT __stdcall ProxyID3DXFont::OnLostDevice() {
	return original->OnLostDevice();
}
HRESULT __stdcall ProxyID3DXFont::OnResetDevice() {
	return original->OnResetDevice();
}
