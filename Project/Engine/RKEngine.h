#pragma once

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

namespace Renderer
{
	class CDevice;
	struct t_RendererData;
	class CResourceManager;
}
namespace Script
{
	class ScriptManager;
}

namespace RKEngine
{
	class CScriptReLoad;
	typedef General::CDllLoader*const& PCR_DllLoad;
	typedef General::FileManager* const& PCR_FileManager;
	class DLL_DECLSPEC CRKEngine :public rokaStl::IManagerLoop, public rokaStl::Singleton<CRKEngine>
	{
		SINGLETON(CRKEngine)
		MANAGERLOOP
	private:
		bool m_bFocus;
		bool m_bBeforFocus;
		std::vector<HWND> m_hWnds;
		//////////////////////////
		//   Manager            //
		//////////////////////////
		General::CDllLoader* mMDllLoader;
		General::FileManager* mMFile;
		CScriptReLoad* mMScriptReLoad;
		Script::ScriptManager* mMScript;
		Renderer::CResourceManager* mMResource;
		//////////////////////////
		//    Renderer Data     //
		//////////////////////////
		Renderer::CDevice* mMDevice;
		Renderer::t_RendererData*const mtRendererData;
	public:
		//Manager
		virtual void SetLMDll(PCR_DllLoad _pcr_dllload) { mMDllLoader = _pcr_dllload; }
		virtual void SetRenderDevice(Renderer::CDevice* _device) { mMDevice = _device; }
		virtual General::FileManager* GetFileManager() { return mMFile; }
		virtual Script::ScriptManager* GetScriptManager() { return mMScript; }
		virtual Renderer::CResourceManager* GetResourceManager() { return mMResource; }
	public:
		virtual void SetHWND(HWND _hWnd, EHwndType _eType);
		virtual HWND GetHWND(EHwndType _type) { return m_hWnds[TYPETOINT(_type)]; }
	
		virtual const Vec2& GetResolution(); 
		virtual Renderer::t_RendererData GetRenderData();
		virtual void LoadDll();
		virtual void FreeDll();
		virtual HMODULE GetDll(EDllType eType);
		virtual void LoadDll(EDllType eType);
		virtual void FreeDll(EDllType eType);
	private:
		void CreateManager();
		void InitManager();
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


