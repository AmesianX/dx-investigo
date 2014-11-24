#pragma once

#include <d3dx9.h>

class ProxyID3DXFont : public ID3DXFont
{
public:
	ProxyID3DXFont(ID3DXFont* pOriginal) :
		original(pOriginal) {}

	virtual ~ProxyID3DXFont() {}

	// IUnknown
	STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv);
	STDMETHOD_(ULONG, AddRef)(THIS);
	STDMETHOD_(ULONG, Release)(THIS);

	// ID3DXFont
	STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE9 *ppDevice) ;
	STDMETHOD(GetDescA)(THIS_ D3DXFONT_DESCA *pDesc) ;
	STDMETHOD(GetDescW)(THIS_ D3DXFONT_DESCW *pDesc) ;
	STDMETHOD_(BOOL, GetTextMetricsA)(THIS_ TEXTMETRICA *pTextMetrics) ;
	STDMETHOD_(BOOL, GetTextMetricsW)(THIS_ TEXTMETRICW *pTextMetrics) ;

	STDMETHOD_(HDC, GetDC)(THIS);
	STDMETHOD(GetGlyphData)(THIS_ UINT Glyph, LPDIRECT3DTEXTURE9 *ppTexture, RECT *pBlackBox, POINT *pCellInc) ;

	STDMETHOD(PreloadCharacters)(THIS_ UINT First, UINT Last) ;
	STDMETHOD(PreloadGlyphs)(THIS_ UINT First, UINT Last) ;
	STDMETHOD(PreloadTextA)(THIS_ LPCSTR pString, INT Count) ;
	STDMETHOD(PreloadTextW)(THIS_ LPCWSTR pString, INT Count) ;

	STDMETHOD_(INT, DrawTextA)(THIS_ LPD3DXSPRITE pSprite, LPCSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color) ;
	STDMETHOD_(INT, DrawTextW)(THIS_ LPD3DXSPRITE pSprite, LPCWSTR pString, INT Count, LPRECT pRect, DWORD Format, D3DCOLOR Color) ;

	STDMETHOD(OnLostDevice)(THIS);
	STDMETHOD(OnResetDevice)(THIS);

	ID3DXFont* original;
};

