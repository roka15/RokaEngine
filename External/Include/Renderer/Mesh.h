#pragma once
namespace Renderer
{
	class CMesh : public General::CResource
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_VB;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_IB;
		D3D11_BUFFER_DESC m_VBDesc;
		D3D11_BUFFER_DESC m_IBDesc;
		UINT m_VertexCnt;
		UINT m_IndexCnt;

	public:
		CMesh(bool _bEngine);
		~CMesh();

		void Create(void* _pVtxList, UINT _uiVtxCnt, void* _pIdxList, UINT _uiIdxCnt);
		void Render();
	private:
		virtual void UpdateData()override;
		
	};
}


