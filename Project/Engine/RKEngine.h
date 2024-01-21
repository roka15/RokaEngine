#pragma once

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

namespace Renderer
{
	class CDxDevice;
	struct t_RendererData;
}
namespace Script
{
	class ScriptManager;
}

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

		rokaStl::CDllLoader* m_DllLoader;
		rokaStl::FileManager* m_M_File;
		CScriptReLoad* m_M_ScriptReLoad;
		//////////////////////////
		//    Script Data     //
		//////////////////////////
		Script::ScriptManager* mScriptMgr;
		//////////////////////////
		//    Renderer Data     //
		//////////////////////////
		Renderer::CDxDevice* mDevice;
		Renderer::t_RendererData*const mRendererData;
	public:
		virtual void SetHWND(HWND _hWnd, EHwndType _eType) { m_hWnds[TYPETOINT(_eType)] = _hWnd; }
		virtual void SetLMDll(PCR_DllLoad _pcr_dllload) { m_DllLoader = _pcr_dllload; }
		virtual void SetFileManager(PCR_FileManager _pcr_file_manager) { m_M_File = _pcr_file_manager; }
		virtual void SetRenderDevice(Renderer::CDxDevice* _device) { mDevice = _device; }
		virtual HWND GetHWND(EHwndType _type) { return m_hWnds[TYPETOINT(_type)]; }
		virtual rokaStl::FileManager* GetFileManager() { return m_M_File; }
		virtual const Vec2& GetResolution(); 
		virtual Renderer::t_RendererData GetRenderData();
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
typedef RKEngine::CRKEngine* const& (*ENGINE_INST_FUNC)(void);

extern "C"
{
	DLL_DECLSPEC void CreateEngine();
	DLL_DECLSPEC void DestroyEngine();
	DLL_DECLSPEC RKEngine::CRKEngine*const& GetInstEngine();
}


