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
#include "ProxyIDirect3DVertexDeclaration9.h"
#include "ProxyIDirect3DDevice9.h"

ProxyIDirect3DVertexDeclaration9::ProxyIDirect3DVertexDeclaration9(IDirect3DVertexDeclaration9* _original, ProxyIDirect3DDevice9* proxyDevice, const std::string& resourceName) :
	InvestigoResource(proxyDevice, resourceName),
	original(_original) 
{
}

ProxyIDirect3DVertexDeclaration9::~ProxyIDirect3DVertexDeclaration9()
{
	GetProxyDevice()->ClearVertexDecl(this);
}

/*** IUnknown methods ***/
HRESULT __stdcall ProxyIDirect3DVertexDeclaration9::QueryInterface(REFIID riid, void** ppvObj) 
{
	return original->QueryInterface(riid, ppvObj);
}

ULONG __stdcall ProxyIDirect3DVertexDeclaration9::AddRef()
{
	return original->AddRef();
}

ULONG __stdcall ProxyIDirect3DVertexDeclaration9::Release()
{
	ULONG count = original->Release();
	if (count == 0)
	{
		original = NULL;
		delete this;
	}

	return count;
}

/*** IDirect3DVertexDeclaration9 methods ***/
HRESULT __stdcall ProxyIDirect3DVertexDeclaration9::GetDevice(IDirect3DDevice9** ppDevice)
{
	return original->GetDevice(ppDevice);
}

HRESULT __stdcall ProxyIDirect3DVertexDeclaration9::GetDeclaration(D3DVERTEXELEMENT9* pElement,UINT* pNumElements)
{
	return original->GetDeclaration(pElement,pNumElements);
}
