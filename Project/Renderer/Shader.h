#pragma once
namespace Renderer
{
	class CShader : public General::CResource
	{
	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> mErrorBlob;
	public:
		CShader(EResourceType _eType);
		virtual ~CShader();
	};
}

