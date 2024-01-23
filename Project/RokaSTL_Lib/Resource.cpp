#include "pch.h"
#include "Resource.h"

namespace General
{
	CResource::CResource(Renderer::EResourceType _eType, bool _bEngine) :
		m_eType(_eType),
		m_bEngineRes(_bEngine),
		m_strKey(),
		m_strPath(),
		m_uiRefCnt(0)
	{

	}
	CResource::CResource(const CResource& _ref):
		CEntity(_ref),
		m_eType(_ref.m_eType),
		m_bEngineRes(_ref.m_bEngineRes),
		m_strKey(_ref.m_strKey),
		m_strPath(_ref.m_strPath),
		m_uiRefCnt(_ref.m_uiRefCnt)
	{
	}
	CResource::~CResource()
	{
	}
	void CResource::Release()
	{
		--m_uiRefCnt;
		if (m_uiRefCnt == 0)
		{
			delete this;
		}
	}
}