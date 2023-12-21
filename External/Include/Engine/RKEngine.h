#pragma once
#include "pch.h"

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

namespace RKEngine
{
	typedef rokaStl::CDllLoader*const& PCR_DllLoad;
	class DLL_DECLSPEC CRKEngine :public rokaStl::IManager, public rokaStl::Singleton<CRKEngine>
	{
		SINGLETON(CRKEngine)
			MANAGER
	private:
		bool m_bFocus;
		bool m_bBeforFocus;
		std::vector<HWND> m_hWnds;
		Vec2 m_v2WinSize;
	public:
		virtual void SetHWND(HWND _hWnd, EHwndType _eType) { m_hWnds[TYPETOINT(_eType)] = _hWnd; }
		virtual void LoadDll(PCR_DllLoad _pcr_dllload);
		virtual void FreeDll(PCR_DllLoad _pcr_dllload);
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


