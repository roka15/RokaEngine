#pragma once
#include "pch.h"

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS


namespace RKEngine
{
	class CScriptReLoad;
	typedef rokaStl::CDllLoader*const& PCR_DllLoad;
	typedef rokaStl::FileManager* const& PCR_FileManager;
	class DLL_DECLSPEC CRKEngine :public rokaStl::IManager, public rokaStl::Singleton<CRKEngine>
	{
		SINGLETON(CRKEngine)
			MANAGER
	private:
		bool m_bFocus;
		bool m_bBeforFocus;
		std::vector<HWND> m_hWnds;
		Vec2 m_v2WinSize;
		rokaStl::CDllLoader* m_DllLoader;
		rokaStl::FileManager* m_M_File;

		CScriptReLoad* m_M_ScriptReLoad;
	public:
		virtual void SetHWND(HWND _hWnd, EHwndType _eType) { m_hWnds[TYPETOINT(_eType)] = _hWnd; }
		virtual void SetLMDll(PCR_DllLoad _pcr_dllload) { m_DllLoader = _pcr_dllload; }
		virtual void SetFileManager(PCR_FileManager _pcr_file_manager) { m_M_File = _pcr_file_manager; }

		virtual rokaStl::FileManager* GetFileManager() { return m_M_File; }
		virtual void LoadDll();
		virtual void FreeDll();

		PROPERTY(GetFileManager, SetFileManager) rokaStl::FileManager* M_File;
	private:
		void ScriptMonitor();
		void WindowMonitor();
		bool WindowSizeMonitor();
		bool WindowFocusMonitor();
	};
}

typedef void (*ENGINE_LIFE_FUNC)(void);
typedef void*const&(*ENGINE_INST_FUNC)(void);

extern "C"
{
	DLL_DECLSPEC void CreateEngine();
	DLL_DECLSPEC void DestroyEngine();
	DLL_DECLSPEC RKEngine::CRKEngine*const& GetInstEngine();
}


