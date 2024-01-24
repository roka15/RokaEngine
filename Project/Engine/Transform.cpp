#include "pch.h"
#include "Transform.h"

namespace RKEngine
{
	CTransform::CTransform():CComponent(EComponentType::TRANSFORM)
	{
	}

	CTransform::CTransform(const CTransform& _ref):CComponent(_ref)
	{
	}

	CTransform::~CTransform()
	{
	}

	void CTransform::Start()
	{
	}

	void CTransform::Update()
	{
	}

	void CTransform::LateUpdate()
	{
	}

	void CTransform::SaveToSceneMetaFile()
	{
	}

	void CTransform::LoadToSceneMetaFile()
	{
	}
}

