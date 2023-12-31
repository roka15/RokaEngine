#include "pch.h"
#include "ScriptManager.h"
#include "CTestScript.h"
ScriptManager::ScriptManager()
{
}
ScriptManager::~ScriptManager()
{
}
void  ScriptManager::Initialize()
{
}
void ScriptManager::Loop()
{
}
void ScriptManager::Release()
{
}
void ScriptManager::GetScriptsInfo(std::vector<const TCHAR*>& _vec)
{
		_vec.push_back(TEXT("CTestScript"));
}
CScript* ScriptManager::GetScript(unsigned int _ScriptType)
{
		EScriptType eType = (EScriptType)_ScriptType;
		switch(eType)
		{
		case EScriptType::CTestScript:
			return new CTestScript(TYPETOINT(EScriptType::CTestScript));
			break;
		}
		return nullptr;
}
CScript* ScriptManager::GetScript(const TCHAR* _ScriptName)
{
		if(_tcscmp(_ScriptName , TEXT("CTestScript")) == 0)
			return new CTestScript(TYPETOINT(EScriptType::CTestScript));
		return nullptr;
}
const wchar_t* ScriptManager::GetScriptName(CScript* _pScript)
{
		EScriptType eType =  (EScriptType)_pScript->GetScriptType();
		switch (eType)
		{
		case EScriptType::CTestScript:
			return TEXT("CTestScript");
			break;
		}
		return nullptr;
}
SCRIPTDLL_DECLSPEC void ScriptManagerCreate()
{
		return MCreate(ScriptManager);
}
SCRIPTDLL_DECLSPEC void ScriptManagerDestory()
{
		return MDestroy(ScriptManager);
}
SCRIPTDLL_DECLSPEC ScriptManager* GetScriptManager()
{
		 return GetInst(ScriptManager);
}

