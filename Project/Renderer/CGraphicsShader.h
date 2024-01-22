#pragma once
#include "Shader.h"
namespace Renderer
{
	class CGraphicsShader :
		public CShader
	{
	private:
		Microsoft::WRL::ComPtr<ID3DBlob> mVertexBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHullBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDomainBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGeometryBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPixelBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHullShader;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDomainShader;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGeometryShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
	  
		Microsoft::WRL::ComPtr<ID3D11InputLayout> mVertexLayout;
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
	public:
		CGraphicsShader();
		~CGraphicsShader();
	private:
		void CreateVertexShader(const TCHAR* _ShaderFileName, const char* _MainName, const char* _ShaderVer);
		void CreatePixelShader(const TCHAR* _ShaderFileName, const char* _MainName, const char* _ShaderVer);
		virtual void UpdateData();

	};
}


