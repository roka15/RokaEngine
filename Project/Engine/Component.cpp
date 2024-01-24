#include "pch.h"
#include "Component.h"

namespace RKEngine
{
	CComponent::CComponent(EComponentType _type)
		:CEntity(),
		m_ComType(_type),
		m_Owner(nullptr)
	{
	}

	CComponent::CComponent(const CComponent& _ref)
		:CEntity(_ref),
		m_ComType(_ref.m_ComType),
		m_Owner(nullptr)
	{
	}

	CComponent::~CComponent()
	{
	}
}

