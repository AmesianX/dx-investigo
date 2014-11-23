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
#include "ProxyD3DX.h"
#include "ProxyID3DXEffect.h"

#include "..\ProxyDX\InvestigoApplicationInterface.h"

// ID3DXBaseEffect
HRESULT __stdcall ProxyID3DXEffect::QueryInterface(REFIID iid, LPVOID *ppv)
{
	*ppv = NULL;

	HRESULT result = m_pOriginal->QueryInterface(iid, ppv);
	if (result == S_OK)
	{
		*ppv = this;
	}

	return result;
}

ULONG __stdcall ProxyID3DXEffect::AddRef()
{
	return m_pOriginal->AddRef();
}

ULONG __stdcall ProxyID3DXEffect::Release()
{
	ULONG count = m_pOriginal->Release();

	if (count == 0)
	{		
		delete(this);
	}

	return (count);
}

// Descs
HRESULT __stdcall ProxyID3DXEffect::GetDesc(D3DXEFFECT_DESC* pDesc)
{
	return m_pOriginal->GetDesc(pDesc);
}

HRESULT __stdcall ProxyID3DXEffect::GetParameterDesc(D3DXHANDLE hParameter, D3DXPARAMETER_DESC* pDesc)
{
	return m_pOriginal->GetParameterDesc(hParameter, pDesc);
}

HRESULT __stdcall ProxyID3DXEffect::GetTechniqueDesc(D3DXHANDLE hTechnique, D3DXTECHNIQUE_DESC* pDesc)
{
	return m_pOriginal->GetTechniqueDesc(hTechnique, pDesc);
}

HRESULT __stdcall ProxyID3DXEffect::GetPassDesc(D3DXHANDLE hPass, D3DXPASS_DESC* pDesc)
{
	return m_pOriginal->GetPassDesc(hPass, pDesc);
}

HRESULT __stdcall ProxyID3DXEffect::GetFunctionDesc(D3DXHANDLE hShader, D3DXFUNCTION_DESC* pDesc)
{
	return m_pOriginal->GetFunctionDesc(hShader, pDesc);
}


// Handle operations
D3DXHANDLE __stdcall ProxyID3DXEffect::GetParameter(D3DXHANDLE hParameter, UINT Index)
{
	return m_pOriginal->GetParameter(hParameter, Index);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetParameterByName(D3DXHANDLE hParameter, LPCSTR pName)
{
	return m_pOriginal->GetParameterByName(hParameter, pName);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetParameterBySemantic(D3DXHANDLE hParameter, LPCSTR pSemantic)
{
	return m_pOriginal->GetParameterBySemantic(hParameter, pSemantic);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetParameterElement(D3DXHANDLE hParameter, UINT Index)
{
	return m_pOriginal->GetParameterElement(hParameter, Index);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetTechnique(UINT Index)
{
	return m_pOriginal->GetTechnique(Index);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetTechniqueByName(LPCSTR pName)
{
	return m_pOriginal->GetTechniqueByName(pName);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetPass(D3DXHANDLE hTechnique, UINT Index)
{
	return m_pOriginal->GetPass(hTechnique, Index);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetPassByName(D3DXHANDLE hTechnique, LPCSTR pName)
{
	return m_pOriginal->GetPassByName(hTechnique, pName);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetFunction(UINT Index)
{
	return m_pOriginal->GetFunction(Index);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetFunctionByName(LPCSTR pName)
{
	return m_pOriginal->GetFunctionByName(pName);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetAnnotation(D3DXHANDLE hObject, UINT Index)
{
	return m_pOriginal->GetAnnotation(hObject, Index);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetAnnotationByName(D3DXHANDLE hObject, LPCSTR pName)
{
	return m_pOriginal->GetAnnotationByName(hObject, pName);
}


// Get/Set Parameters
HRESULT __stdcall ProxyID3DXEffect::SetValue(D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes)
{
	return m_pOriginal->SetValue(hParameter, pData, Bytes);
}

HRESULT __stdcall ProxyID3DXEffect::GetValue(D3DXHANDLE hParameter, LPVOID pData, UINT Bytes)
{
	return m_pOriginal->GetValue(hParameter, pData, Bytes);
}

HRESULT __stdcall ProxyID3DXEffect::SetBool(D3DXHANDLE hParameter, BOOL b)
{
	return m_pOriginal->SetBool(hParameter, b);
}

HRESULT __stdcall ProxyID3DXEffect::GetBool(D3DXHANDLE hParameter, BOOL* pb)
{
	return m_pOriginal->GetBool(hParameter, pb);
}

HRESULT __stdcall ProxyID3DXEffect::SetBoolArray(D3DXHANDLE hParameter, CONST BOOL* pb, UINT Count)
{
	return m_pOriginal->SetBoolArray(hParameter, pb, Count);
}

HRESULT __stdcall ProxyID3DXEffect::GetBoolArray(D3DXHANDLE hParameter, BOOL* pb, UINT Count)
{
	return m_pOriginal->GetBoolArray(hParameter, pb, Count);
}

HRESULT __stdcall ProxyID3DXEffect::SetInt(D3DXHANDLE hParameter, INT n)
{
	return m_pOriginal->SetInt(hParameter, n);
}

HRESULT __stdcall ProxyID3DXEffect::GetInt(D3DXHANDLE hParameter, INT* pn)
{
	return m_pOriginal->GetInt(hParameter, pn);
}

HRESULT __stdcall ProxyID3DXEffect::SetIntArray(D3DXHANDLE hParameter, CONST INT* pn, UINT Count)
{
	return m_pOriginal->SetIntArray(hParameter, pn, Count);
}

HRESULT __stdcall ProxyID3DXEffect::GetIntArray(D3DXHANDLE hParameter, INT* pn, UINT Count)
{
	return m_pOriginal->GetIntArray(hParameter, pn, Count);
}

HRESULT __stdcall ProxyID3DXEffect::SetFloat(D3DXHANDLE hParameter, FLOAT f)
{
	return m_pOriginal->SetFloat(hParameter, f);
}

HRESULT __stdcall ProxyID3DXEffect::GetFloat(D3DXHANDLE hParameter, FLOAT* pf)
{
	return m_pOriginal->GetFloat(hParameter, pf);
}

HRESULT __stdcall ProxyID3DXEffect::SetFloatArray(D3DXHANDLE hParameter, CONST FLOAT* pf, UINT Count)
{
	return m_pOriginal->SetFloatArray(hParameter, pf, Count);
}

HRESULT __stdcall ProxyID3DXEffect::GetFloatArray(D3DXHANDLE hParameter, FLOAT* pf, UINT Count)
{
	return m_pOriginal->GetFloatArray(hParameter, pf, Count);
}

HRESULT __stdcall ProxyID3DXEffect::SetVector(D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector)
{
	return m_pOriginal->SetVector(hParameter, pVector);
}

HRESULT __stdcall ProxyID3DXEffect::GetVector(D3DXHANDLE hParameter, D3DXVECTOR4* pVector)
{
	return m_pOriginal->GetVector(hParameter, pVector);
}

HRESULT __stdcall ProxyID3DXEffect::SetVectorArray(D3DXHANDLE hParameter, CONST D3DXVECTOR4* pVector, UINT Count)
{
	return m_pOriginal->SetVectorArray(hParameter, pVector, Count);
}

HRESULT __stdcall ProxyID3DXEffect::GetVectorArray(D3DXHANDLE hParameter, D3DXVECTOR4* pVector, UINT Count)
{
	return m_pOriginal->GetVectorArray(hParameter, pVector, Count);
}

HRESULT __stdcall ProxyID3DXEffect::SetMatrix(D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix)
{
	return m_pOriginal->SetMatrix(hParameter, pMatrix);
}

HRESULT __stdcall ProxyID3DXEffect::GetMatrix(D3DXHANDLE hParameter, D3DXMATRIX* pMatrix)
{
	return m_pOriginal->GetMatrix(hParameter, pMatrix);
}

HRESULT __stdcall ProxyID3DXEffect::SetMatrixArray(D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count)
{
	return m_pOriginal->SetMatrixArray(hParameter, pMatrix, Count);
}

HRESULT __stdcall ProxyID3DXEffect::GetMatrixArray(D3DXHANDLE hParameter, D3DXMATRIX* pMatrix, UINT Count)
{
	return m_pOriginal->GetMatrixArray(hParameter, pMatrix, Count);
}

HRESULT __stdcall ProxyID3DXEffect::SetMatrixPointerArray(D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count)
{
	return m_pOriginal->SetMatrixPointerArray(hParameter, ppMatrix, Count);
}

HRESULT __stdcall ProxyID3DXEffect::GetMatrixPointerArray(D3DXHANDLE hParameter, D3DXMATRIX** ppMatrix, UINT Count)
{
	return GetMatrixPointerArray(hParameter, ppMatrix, Count);
}

HRESULT __stdcall ProxyID3DXEffect::SetMatrixTranspose(D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix)
{
	return m_pOriginal->SetMatrixTranspose(hParameter, pMatrix);
}

HRESULT __stdcall ProxyID3DXEffect::GetMatrixTranspose(D3DXHANDLE hParameter, D3DXMATRIX* pMatrix)
{
	return m_pOriginal->GetMatrixTranspose(hParameter, pMatrix);
}

HRESULT __stdcall ProxyID3DXEffect::SetMatrixTransposeArray(D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count)
{
	return m_pOriginal->SetMatrixTransposeArray(hParameter, pMatrix, Count);
}

HRESULT __stdcall ProxyID3DXEffect::GetMatrixTransposeArray(D3DXHANDLE hParameter, D3DXMATRIX* pMatrix, UINT Count)
{
	return m_pOriginal->GetMatrixTransposeArray(hParameter, pMatrix, Count);
}

HRESULT __stdcall ProxyID3DXEffect::SetMatrixTransposePointerArray(D3DXHANDLE hParameter, CONST D3DXMATRIX** ppMatrix, UINT Count)
{
	return m_pOriginal->SetMatrixTransposePointerArray(hParameter, ppMatrix, Count);
}

HRESULT __stdcall ProxyID3DXEffect::GetMatrixTransposePointerArray(D3DXHANDLE hParameter, D3DXMATRIX** ppMatrix, UINT Count)
{
	return m_pOriginal->GetMatrixTransposePointerArray(hParameter, ppMatrix, Count);
}

HRESULT __stdcall ProxyID3DXEffect::SetString(D3DXHANDLE hParameter, LPCSTR pString)
{
	return m_pOriginal->SetString(hParameter, pString);
}

HRESULT __stdcall ProxyID3DXEffect::GetString(D3DXHANDLE hParameter, LPCSTR* ppString)
{
	return m_pOriginal->GetString(hParameter, ppString);
}

HRESULT __stdcall ProxyID3DXEffect::SetTexture(D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture)
{
	return m_pOriginal->SetTexture(hParameter, pTexture);
}

HRESULT __stdcall ProxyID3DXEffect::GetTexture(D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 *ppTexture)
{
	return m_pOriginal->GetTexture(hParameter, ppTexture);
}

HRESULT __stdcall ProxyID3DXEffect::GetPixelShader(D3DXHANDLE hParameter, LPDIRECT3DPIXELSHADER9 *ppPShader)
{
	return m_pOriginal->GetPixelShader(hParameter, ppPShader);
}

HRESULT __stdcall ProxyID3DXEffect::GetVertexShader(D3DXHANDLE hParameter, LPDIRECT3DVERTEXSHADER9 *ppVShader)
{
	return m_pOriginal->GetVertexShader(hParameter, ppVShader);
}


//Set Range of an Array to pass to device
//Usefull for sending only a subrange of an array down to the device
HRESULT __stdcall ProxyID3DXEffect::SetArrayRange(D3DXHANDLE hParameter, UINT uStart, UINT uEnd)
{
	return m_pOriginal->SetArrayRange(hParameter, uStart, uEnd);
}

// ID3DXBaseEffect
    
    
// Pool
HRESULT __stdcall ProxyID3DXEffect::GetPool(LPD3DXEFFECTPOOL* ppPool)
{
	return m_pOriginal->GetPool(ppPool);
}


// Selecting and setting a technique
HRESULT __stdcall ProxyID3DXEffect::SetTechnique(D3DXHANDLE hTechnique)
{
	m_CurTechnique = hTechnique;
	return m_pOriginal->SetTechnique(hTechnique);
}

D3DXHANDLE __stdcall ProxyID3DXEffect::GetCurrentTechnique()
{
	return m_pOriginal->GetCurrentTechnique();
}

HRESULT __stdcall ProxyID3DXEffect::ValidateTechnique(D3DXHANDLE hTechnique)
{
	return m_pOriginal->ValidateTechnique(hTechnique);
}

HRESULT __stdcall ProxyID3DXEffect::FindNextValidTechnique(D3DXHANDLE hTechnique, D3DXHANDLE *pTechnique)
{
	return m_pOriginal->FindNextValidTechnique(hTechnique, pTechnique);
}

BOOL __stdcall ProxyID3DXEffect::IsParameterUsed(D3DXHANDLE hParameter, D3DXHANDLE hTechnique)
{
	return m_pOriginal->IsParameterUsed(hParameter, hTechnique);
}


// Using current technique
// Begin           starts active technique
// BeginPass       begins a pass
// CommitChanges   updates changes to any set calls in the pass. This should be called before
//                 any DrawPrimitive call to d3d
// EndPass         ends a pass
// End             ends active technique.
HRESULT __stdcall ProxyID3DXEffect::Begin(UINT *pPasses, DWORD Flags)
{
	if (m_CurTechnique == NULL)
	{
        Investigo::TechniqueBegin("null");
	}
	else
	{
		D3DXTECHNIQUE_DESC desc;
		m_pOriginal->GetTechniqueDesc(m_CurTechnique, &desc);
		Investigo::TechniqueBegin(desc.Name);
	}

	return m_pOriginal->Begin(pPasses, Flags);
}

HRESULT __stdcall ProxyID3DXEffect::BeginPass(UINT Pass)
{
	return m_pOriginal->BeginPass(Pass);
}

HRESULT __stdcall ProxyID3DXEffect::CommitChanges()
{
	return m_pOriginal->CommitChanges();
}

HRESULT __stdcall ProxyID3DXEffect::EndPass()
{
	HRESULT result = m_pOriginal->EndPass();
	Investigo::TechniqueEnd();
	return result;
}

HRESULT __stdcall ProxyID3DXEffect::End()
{
	return m_pOriginal->End();
}

// Managing D3D Device
HRESULT __stdcall ProxyID3DXEffect::GetDevice(LPDIRECT3DDEVICE9* ppDevice)
{
	return m_pOriginal->GetDevice(ppDevice);
}

HRESULT __stdcall ProxyID3DXEffect::OnLostDevice()
{
	return m_pOriginal->OnLostDevice();
}

HRESULT __stdcall ProxyID3DXEffect::OnResetDevice()
{
	return m_pOriginal->OnResetDevice();
}

// Logging device calls
HRESULT __stdcall ProxyID3DXEffect::SetStateManager(LPD3DXEFFECTSTATEMANAGER pManager)
{
	return m_pOriginal->SetStateManager(pManager);
}

HRESULT __stdcall ProxyID3DXEffect::GetStateManager(LPD3DXEFFECTSTATEMANAGER *ppManager)
{
	return m_pOriginal->GetStateManager(ppManager);
}

// Parameter blocks
HRESULT __stdcall ProxyID3DXEffect::BeginParameterBlock()
{
	return m_pOriginal->BeginParameterBlock();
}

D3DXHANDLE __stdcall ProxyID3DXEffect::EndParameterBlock()
{
	return m_pOriginal->EndParameterBlock();
}

HRESULT __stdcall ProxyID3DXEffect::ApplyParameterBlock(D3DXHANDLE hParameterBlock)
{
	return m_pOriginal->ApplyParameterBlock(hParameterBlock);
}

HRESULT __stdcall ProxyID3DXEffect::DeleteParameterBlock(D3DXHANDLE hParameterBlock)
{
	return m_pOriginal->DeleteParameterBlock(hParameterBlock);
}

// Cloning
HRESULT __stdcall ProxyID3DXEffect::CloneEffect(LPDIRECT3DDEVICE9 pDevice, LPD3DXEFFECT* ppEffect)
{
	return m_pOriginal->CloneEffect(pDevice, ppEffect); //todo: wrap.
}
    
// Fast path for setting variables directly in ID3DXEffect
HRESULT __stdcall ProxyID3DXEffect::SetRawValue(D3DXHANDLE hParameter, LPCVOID pData, UINT ByteOffset, UINT Bytes)
{
	return m_pOriginal->SetRawValue(hParameter, pData, ByteOffset, Bytes);
}
