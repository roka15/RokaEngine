#pragma once
#include "pch.h" 
#include <RokaSTL/SingleTon.h>
class CScript;
#ifdef SCRIPTDLL_EXPORTS 
#define SCRIPTDLL_DECLSPEC __declspec(dllexport) 
#else 
#define SCRIPTDLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS
enum class SCRIPTDLL_DECLSPEC EScriptType
{
		NONE,
		CSecondScript,
		CTestScript,
		END,
};
class SCRIPTDLL_DECLSPEC ScriptManager:public rokaStl::IScriptManager,public rokaStl::Singleton<ScriptManager>
{
		SINGLETON(ScriptManager)
		MANAGER
private:
public:
		virtual void GetScriptsInfo(wchar_t** _vec)override;
		virtual CScript* GetScript(unsigned int _ScriptType)override;
		virtual CScript* GetScript(const wchar_t* _ScriptName)override;
		virtual const wchar_t* GetScriptName(CScript* _pScript)override;
};
extern "C"
{
		SCRIPTDLL_DECLSPEC void ScriptManagerCreate();
		SCRIPTDLL_DECLSPEC void ScriptManagerDestory();
		SCRIPTDLL_DECLSPEC ScriptManager* GetScriptManager();
}

