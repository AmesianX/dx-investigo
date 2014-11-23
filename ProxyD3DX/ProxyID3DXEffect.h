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

class ProxyID3DXEffect : public ID3DXEffect
{
public:
	ProxyID3DXEffect(ID3DXEffect* pOriginal) :
	  m_pOriginal(pOriginal),
	  m_CurTechnique(NULL) {}

	  virtual ~ProxyID3DXEffect() {}

    // ID3DXBaseEffect
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv);
    STDMETHOD_(ULONG, AddRef)(THIS);
    STDMETHOD_(ULONG, Release)(THIS);

    // Descs
    STDMETHOD(GetDesc)(THIS_ D3DXEFFECT_DESC* pDesc);
    STDMETHOD(GetParameterDesc)(THIS_ D3DXHANDLE hParameter, D3DXPARAMETER_DESC* pDesc);
    STDMETHOD(GetTechniqueDesc)(THIS_ D3DXHANDLE hTechnique, D3DXTECHNIQUE_DESC* pDesc);
    STDMETHOD(GetPassDesc)(THIS_ D3DXHANDLE hPass, D3DXPASS_DESC* pDesc);
    STDMETHOD(GetFunctionDesc)(THIS_ D3DXHANDLE hShader, D3DXFUNCTION_DESC* pDesc);

    // Handle operations
    STDMETHOD_(D3DXHANDLE, GetParameter)(THIS_ D3DXHANDLE hParameter, UINT Index);
    STDMETHOD_(D3DXHANDLE, GetParameterByName)(THIS_ D3DXHANDLE hParameter, LPCSTR pName);
    STDMETHOD_(D3DXHANDLE, GetParameterBySemantic)(THIS_ D3DXHANDLE hParameter, LPCSTR pSemantic);
    STDMETHOD_(D3DXHANDLE, GetParameterElement)(THIS_ D3DXHANDLE hParameter, UINT Index);
    STDMETHOD_(D3DXHANDLE, GetTechnique)(THIS_ UINT Index);
    STDMETHOD_(D3DXHANDLE, GetTechniqueByName)(THIS_ LPCSTR pName);
    STDMETHOD_(D3DXHANDLE, GetPass)(THIS_ D3DXHANDLE hTechnique, UINT Index);
    STDMETHOD_(D3DXHANDLE, GetPassByName)(THIS_ D3DXHANDLE hTechnique, LPCSTR pName);
    STDMETHOD_(D3DXHANDLE, GetFunction)(THIS_ UINT Index);
    STDMETHOD_(D3DXHANDLE, GetFunctionByName)(THIS_ LPCSTR pName);
    STDMETHOD_(D3DXHANDLE, GetAnnotation)(THIS_ D3DXHANDLE hObject, UINT Index);
    STDMETHOD_(D3DXHANDLE, GetAnnotationByName)(THIS_ D3DXHANDLE hObject, LPCSTR pName);

    // Get/Set Parameters
    STDMETHOD(SetValue)(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes);
    STDMETHOD(GetValue)(THIS_ D3DXHANDLE hParameter, LPVOID pData, UINT Bytes);
    STDMETHOD(SetBool)(THIS_ D3DXHANDLE hParameter, BOOL b);
    STDMETHOD(GetBool)(THIS_ D3DXHANDLE hParameter, BOOL* pb);
    STDMETHOD(SetBoolArray)(THIS_ D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count);
    STDMETHOD(GetBoolArray)(THIS_ D3DXHANDLE hParameter, BOOL* pb, UINT Count);
    STDMETHOD(SetInt)(THIS_ D3DXHANDLE hParameter, INT n);
    STDMETHOD(GetInt)(THIS_ D3DXHANDLE hParameter, INT* pn);
    STDMETHOD(SetIntArray)(THIS_ D3DXHANDLE hParameter, CONST INT* pn, UINT Count);
    STDMETHOD(GetIntArray)(THIS_ D3DXHANDLE hParameter, INT* pn, UINT Count);
    STDMETHOD(SetFloat)(THIS_ D3DXHANDLE hParameter, FLOAT f);
    STDMETHOD(GetFloat)(THIS_ D3DXHANDLE hParameter, FLOAT* pf);
    STDMETHOD(SetFloatArray)(THIS_ D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count);
    STDMETHOD(GetFloatArray)(THIS_ D3DXHANDLE hParameter, FLOAT* pf, UINT Count);
    STDMETHOD(SetVector)(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector);
    STDMETHOD(GetVector)(THIS_ D3DXHANDLE hParameter, D3DXVECTOR4* pVector);
    STDMETHOD(SetVectorArray)(THIS_ D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count);
    STDMETHOD(GetVectorArray)(THIS_ D3DXHANDLE hParameter, D3DXVECTOR4* pVector, UINT Count);
    STDMETHOD(SetMatrix)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
    STDMETHOD(GetMatrix)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX* pMatrix);
    STDMETHOD(SetMatrixArray)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
    STDMETHOD(GetMatrixArray)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX* pMatrix, UINT Count);
    STDMETHOD(SetMatrixPointerArray)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
    STDMETHOD(GetMatrixPointerArray)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX** ppMatrix, UINT Count);
    STDMETHOD(SetMatrixTranspose)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix);
    STDMETHOD(GetMatrixTranspose)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX* pMatrix);
    STDMETHOD(SetMatrixTransposeArray)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count);
    STDMETHOD(GetMatrixTransposeArray)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX* pMatrix, UINT Count);
    STDMETHOD(SetMatrixTransposePointerArray)(THIS_ D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count);
    STDMETHOD(GetMatrixTransposePointerArray)(THIS_ D3DXHANDLE hParameter, D3DXMATRIX** ppMatrix, UINT Count);
    STDMETHOD(SetString)(THIS_ D3DXHANDLE hParameter, LPCSTR pString);
    STDMETHOD(GetString)(THIS_ D3DXHANDLE hParameter, LPCSTR* ppString);
    STDMETHOD(SetTexture)(THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture);
    STDMETHOD(GetTexture)(THIS_ D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 *ppTexture);
    STDMETHOD(GetPixelShader)(THIS_ D3DXHANDLE hParameter, LPDIRECT3DPIXELSHADER9 *ppPShader);
    STDMETHOD(GetVertexShader)(THIS_ D3DXHANDLE hParameter, LPDIRECT3DVERTEXSHADER9 *ppVShader);

	//Set Range of an Array to pass to device
	//Usefull for sending only a subrange of an array down to the device
	STDMETHOD(SetArrayRange)(THIS_ D3DXHANDLE hParameter, UINT uStart, UINT uEnd); 
	// ID3DXBaseEffect
    
    
    // Pool
    STDMETHOD(GetPool)(THIS_ LPD3DXEFFECTPOOL* ppPool);

    // Selecting and setting a technique
    STDMETHOD(SetTechnique)(THIS_ D3DXHANDLE hTechnique);
    STDMETHOD_(D3DXHANDLE, GetCurrentTechnique)(THIS);
    STDMETHOD(ValidateTechnique)(THIS_ D3DXHANDLE hTechnique);
    STDMETHOD(FindNextValidTechnique)(THIS_ D3DXHANDLE hTechnique, D3DXHANDLE *pTechnique);
    STDMETHOD_(BOOL, IsParameterUsed)(THIS_ D3DXHANDLE hParameter, D3DXHANDLE hTechnique);

    // Using current technique
    // Begin           starts active technique
    // BeginPass       begins a pass
    // CommitChanges   updates changes to any set calls in the pass. This should be called before
    //                 any DrawPrimitive call to d3d
    // EndPass         ends a pass
    // End             ends active technique
    STDMETHOD(Begin)(THIS_ UINT *pPasses, DWORD Flags);
    STDMETHOD(BeginPass)(THIS_ UINT Pass);
    STDMETHOD(CommitChanges)(THIS);
    STDMETHOD(EndPass)(THIS);
    STDMETHOD(End)(THIS);

    // Managing D3D Device
    STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE9* ppDevice);
    STDMETHOD(OnLostDevice)(THIS);
    STDMETHOD(OnResetDevice)(THIS);

    // Logging device calls
    STDMETHOD(SetStateManager)(THIS_ LPD3DXEFFECTSTATEMANAGER pManager);
    STDMETHOD(GetStateManager)(THIS_ LPD3DXEFFECTSTATEMANAGER *ppManager);

    // Parameter blocks
    STDMETHOD(BeginParameterBlock)(THIS);
    STDMETHOD_(D3DXHANDLE, EndParameterBlock)(THIS);
    STDMETHOD(ApplyParameterBlock)(THIS_ D3DXHANDLE hParameterBlock);
    STDMETHOD(DeleteParameterBlock)(THIS_ D3DXHANDLE hParameterBlock);

    // Cloning
    STDMETHOD(CloneEffect)(THIS_ LPDIRECT3DDEVICE9 pDevice, LPD3DXEFFECT* ppEffect);
    
    // Fast path for setting variables directly in ID3DXEffect
    STDMETHOD(SetRawValue)(THIS_ D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes);

	ID3DXEffect* m_pOriginal;
	D3DXHANDLE m_CurTechnique;
};

