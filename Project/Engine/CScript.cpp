#include "pch.h"
#include "CScript.h"

CScript::CScript(unsigned int _type)
	:CComponent(EComponentType::SCRIPT),
	 m_ScriptType(_type),
	 m_ScriptParams{}
{
}
CScript::CScript(const CScript& _ref)
	:CComponent(_ref),
	m_ScriptType(_ref.m_ScriptType),
	m_ScriptParams(_ref.m_ScriptParams)
{
}
CScript::~CScript()
{

}
void CScript::Print()
{
	 std::cout << "CScript Print" << std::endl; 
}
