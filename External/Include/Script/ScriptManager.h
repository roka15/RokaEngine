#pragma once
#include <RokaSTL/SingleTon.h>


#ifdef SCRIPTDLL_EXPORTS 
#define SCRIPTDLL_DECLSPEC __declspec(dllexport) 
#else 
#define SCRIPTDLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

namespace RKEngine
{
	class CScript;
}
namespace Script
{
	enum class SCRIPTDLL_DECLSPEC EScriptType
	{
		NONE,
		CTestScript,
		END,
	};
	class SCRIPTDLL_DECLSPEC ScriptManager :public rokaStl::IScriptManager, public rokaStl::Singleton<ScriptManager>
	{
		SINGLETON(ScriptManager)
			MANAGER
	private:
	public:
		virtual void GetScriptsInfo(std::vector<const TCHAR*>& _vec)override;
		virtual RKEngine::CScript* GetScript(unsigned int _ScriptType)override;
		virtual RKEngine::CScript* GetScript(const TCHAR* _ScriptName)override;
		virtual const wchar_t* GetScriptName(RKEngine::CScript* _pScript)override;
	};
}



