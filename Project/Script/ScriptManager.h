#pragma once
#include "pch.h"
#include <RokaSTL/SingleTon.h>
class CScript;
enum class DLL_DECLSPEC EScriptType
{
	NONE,
	TEST,
	END,
};
class DLL_DECLSPEC ScriptManager:public rokaStl::IScriptManager,public rokaStl::Singleton<ScriptManager>
{
	SINGLETON(ScriptManager)
public:
	virtual void Initialize()override;
	virtual void Release()override;
	virtual void GetScriptsInfo(wchar_t** _vec)override;
	virtual CScript* GetScript(unsigned int _ScriptType)override;
	virtual CScript* GetScript(const wchar_t* _ScriptName)override;
	virtual const wchar_t* GetScriptName(CScript* _pScript)override;
};

extern "C"
{
	DLL_DECLSPEC void ScriptManagerCreate();
	DLL_DECLSPEC void ScriptManagerDestory();
	DLL_DECLSPEC ScriptManager* GetScriptManager();
}