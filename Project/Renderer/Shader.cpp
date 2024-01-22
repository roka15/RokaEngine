#include "pch.h"
#include "Shader.h"

namespace Renderer
{
	CShader::CShader(EResourceType _eType)
		:CResource(_eType, true),
		mErrorBlob(nullptr)
	{
	}

	CShader::~CShader()
	{
	}
}

