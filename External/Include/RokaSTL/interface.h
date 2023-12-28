#pragma once

class CScript;
namespace rokaStl
{
	class IManager
	{
	public:
		virtual void Initialize() = 0;
		virtual void Loop() = 0;
		virtual void Release() = 0;
	};


	class IScriptManager : public IManager
	{
	public:
		virtual void Initialize() = 0;
		virtual void Release() = 0;
		virtual void GetScriptsInfo(std::vector<const TCHAR*>& _vec) = 0;
		virtual CScript* GetScript(unsigned int _ScriptType) = 0;
		virtual CScript* GetScript(const wchar_t* _ScriptName) = 0;
		virtual const wchar_t* GetScriptName(CScript* _pScript)=0;
	};

}
