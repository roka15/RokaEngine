#pragma once
#include "Resource.h"
namespace Renderer
{
	class CShader : public CResource
	{
	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> mErrorBlob;
	public:
		CShader(EResourceType _eType);
		virtual ~CShader();
	};
}

