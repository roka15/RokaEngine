#pragma once

namespace RKEngine
{
	class CScript;
}
namespace rokaStl
{
	class IManager
	{
	public:
		virtual void Initialize() = 0;
		virtual void Release() = 0;
	};
	class IManagerLoop : public IManager
	{
	public:
		virtual void Loop() = 0;
	};
	class IScriptManager : public IManager
	{
	public:
		virtual void Initialize() = 0;
		virtual void Release() = 0;
		virtual void GetScriptsInfo(std::vector<const TCHAR*>& _vec) = 0;
		virtual RKEngine::CScript* GetScript(unsigned int _ScriptType) = 0;
		virtual RKEngine::CScript* GetScript(const wchar_t* _ScriptName) = 0;
		virtual const wchar_t* GetScriptName(RKEngine::CScript* _pScript)=0;
	};

}
