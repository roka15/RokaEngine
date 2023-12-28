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
		CTestScript,
		END,
};
class SCRIPTDLL_DECLSPEC ScriptManager:public rokaStl::IScriptManager,public rokaStl::Singleton<ScriptManager>
{
		SINGLETON(ScriptManager)
		MANAGER
private:
public:
		virtual void GetScriptsInfo(std::vector<const TCHAR*>& _vec)override;
		virtual CScript* GetScript(unsigned int _ScriptType)override;
		virtual CScript* GetScript(const TCHAR* _ScriptName)override;
		virtual const wchar_t* GetScriptName(CScript* _pScript)override;
};
extern "C"
{
		SCRIPTDLL_DECLSPEC void ScriptManagerCreate();
		SCRIPTDLL_DECLSPEC void ScriptManagerDestory();
		SCRIPTDLL_DECLSPEC ScriptManager* GetScriptManager();
}

