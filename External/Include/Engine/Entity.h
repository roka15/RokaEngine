#pragma once
#include "pch.h"
class CEntity
{
private:
	static unsigned int g_NextID;
private:
	std::wstring m_Name;
    const unsigned int m_ID;
public:
	CEntity(); 
	CEntity(const CEntity& _ref);
	virtual ~CEntity();
public:
	virtual CEntity* Copy() = 0;

public:
	void SetName(const std::wstring _name) { m_Name = _name; }
	const std::wstring& GetName() { return m_Name; }
	const unsigned int& GetID() { return m_ID; }
};

