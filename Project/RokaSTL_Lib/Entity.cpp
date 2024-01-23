#include "pch.h"
#include "Entity.h"
namespace General
{
	UINT CEntity::g_NextID = 0;
	CEntity::CEntity()
		:m_ID(g_NextID++)
	{
	}

	CEntity::CEntity(const CEntity& _ref)
		: m_ID(g_NextID++),
		m_Name(_ref.m_Name)
	{
	}

	CEntity::~CEntity()
	{
	}
}
