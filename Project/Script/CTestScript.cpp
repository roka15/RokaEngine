#include "pch.h"
#include "CTestScript.h"

//void CTestScript::Print()
//{
//	CScript::Print();
//}

CTestScript::CTestScript(unsigned int _type)
	:CScript(_type)
{
}

CTestScript::~CTestScript()
{
}

void CTestScript::Print()
{
	std::cout << "CTestScript Print" << std::endl;
	CScript::Print();
}

