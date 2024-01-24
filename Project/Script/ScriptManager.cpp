#include "pch.h"
#include "ScriptManager.h"
#include "CTestScript.h"
namespace Script
{
	ScriptManager::ScriptManager()
	{
	}
	ScriptManager::~ScriptManager()
	{
	}
	void  ScriptManager::Initialize()
	{
	}
	void ScriptManager::Release()
	{
	}
	void ScriptManager::GetScriptsInfo(std::vector<const TCHAR*>& _vec)
	{
		_vec.push_back(TEXT("CTestScript"));
	}
	RKEngine::CScript* ScriptManager::GetScript(unsigned int _ScriptType)
	{
		EScriptType eType = (EScriptType)_ScriptType;
		switch (eType)
		{
		case EScriptType::CTestScript:
			return new CTestScript(TYPETOINT(EScriptType::CTestScript));
			break;
		}
		return nullptr;
	}
	RKEngine::CScript* ScriptManager::GetScript(const TCHAR* _ScriptName)
	{
		if (_tcscmp(_ScriptName, TEXT("CTestScript")) == 0)
			return new CTestScript(TYPETOINT(EScriptType::CTestScript));
		return nullptr;
	}
	const wchar_t* ScriptManager::GetScriptName(RKEngine::CScript* _pScript)
	{
		EScriptType eType = (EScriptType)_pScript->GetScriptType();
		switch (eType)
		{
		case EScriptType::CTestScript:
			return TEXT("CTestScript");
			break;
		}
		return nullptr;
	}
}

