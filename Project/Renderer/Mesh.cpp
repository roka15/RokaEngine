#include "pch.h"
#include "Mesh.h"
#include "DxDevice.h"
namespace Renderer
{
	CMesh::CMesh(bool _bEngine)
		:CResource(EResourceType::Mesh, _bEngine),
		m_VB(nullptr),
		m_IB(nullptr),
		m_VBDesc{},
		m_IBDesc{},
		m_VertexCnt(0),
		m_IndexCnt(0)
	{
	}
	CMesh::~CMesh()
	{
	}
	void CMesh::Create(void* _pVtxList, UINT _uiVtxCnt, void* _pIdxList, UINT _uiIdxCnt)
	{
		ID3D11DeviceContext* context = DX11_PCONTEXT;

		m_VertexCnt = _uiVtxCnt;
		m_IndexCnt = _uiIdxCnt;

		m_VBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		m_VBDesc.ByteWidth = sizeof(t_VertexData)* m_VertexCnt;
		m_VBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		m_VBDesc.CPUAccessFlags = 0;
		m_VBDesc.MiscFlags = 0;
		m_VBDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA Mem = {};
		Mem.pSysMem = _pVtxList;

		HRESULT hr = S_OK;
#ifdef VER_DX11
		hr = DX11_PDEVICE->CreateBuffer(&m_VBDesc, &Mem, m_VB.GetAddressOf());
#endif
		if (FAILED(hr))
			return;
		
		m_IBDesc.ByteWidth = sizeof(UINT) * m_IndexCnt;
		m_IBDesc.CPUAccessFlags = 0;
		m_IBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		m_IBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		m_IBDesc.MiscFlags = 0;
		m_IBDesc.StructureByteStride = 0;

		Mem = {};
		Mem.pSysMem = _pIdxList;
#ifdef VER_DX11
		hr = DX11_PDEVICE->CreateBuffer(&m_IBDesc, &Mem, m_IB.GetAddressOf());
#endif
		if (FAILED(hr))
			return;
	}
	void CMesh::UpdateData()
	{
		UINT stride = sizeof(t_VertexData);
		UINT offset = 0;

#ifdef  VER_DX11
		DX11_PCONTEXT->IASetVertexBuffers(0,1,m_VB.GetAddressOf(),&stride,&offset);
		DX11_PCONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
#endif
	}
	void CMesh::Render()
	{
		UpdateData();
#ifdef  VER_DX11
		DX11_PCONTEXT->DrawIndexed(m_IndexCnt, 0, 0);
#endif
	}
}