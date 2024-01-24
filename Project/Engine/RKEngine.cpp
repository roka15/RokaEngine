#include "pch.h"
#include "RKEngine.h"
#include "ScriptReLoad.h"
#include <Renderer/CDevice.h>


namespace RKEngine
{
	CRKEngine::CRKEngine()
		:m_bFocus(true),
		m_bBeforFocus(true),
		m_hWnds{},
		m_DllLoader(nullptr),
		m_M_File(nullptr),
		mtRendererData(new Renderer::t_RendererData())
	{
		UINT eType = TYPETOINT(EHwndType::END);
		m_hWnds.resize(eType);
	}
	CRKEngine::~CRKEngine()
	{
	}
	void CRKEngine::Initialize()
	{
		WindowSizeMonitor();
		LoadDll();
		m_M_ScriptReLoad = new CScriptReLoad(this);
	}
	void CRKEngine::Loop()
	{
		WindowMonitor();
		ScriptMonitor();
		mDevice->Render();
	}
	void CRKEngine::Release()
	{
		delete m_M_ScriptReLoad;
		delete mtRendererData;
		m_M_ScriptReLoad = nullptr;

		FreeDll();
		m_DllLoader = nullptr;
	}
	const Vec2& CRKEngine::GetResolution()
	{ 
		return mtRendererData->Resolution;
	}
	Renderer::t_RendererData CRKEngine::GetRenderData()
	{
		return *mtRendererData;
	}
	void CRKEngine::LoadDll()
	{
		m_DllLoader->LoadDll(EDllType::SCRIPT);
		HMODULE scriptModule = m_DllLoader->GetDLL(EDllType::SCRIPT);
		
		M_ScriptLife_PFUNC scriptCreate = (M_ScriptLife_PFUNC)GetProcAddress(scriptModule, "CreateManager");
		scriptCreate();
		M_ScriptGetInst_PFUNC scriptInst = (M_ScriptGetInst_PFUNC)GetProcAddress(scriptModule, "GetManagerInstance");
		mScriptMgr = (Script::ScriptManager*)scriptInst();
	}
	void CRKEngine::FreeDll()
	{
		HMODULE scriptModule = m_DllLoader->GetDLL(EDllType::SCRIPT);
		if (scriptModule == nullptr)
			return;
		M_ScriptLife_PFUNC scriptDestroy = (M_ScriptLife_PFUNC)GetProcAddress(scriptModule, "DestroyManager");
		
		scriptDestroy();
	
		m_DllLoader->FreeDll(EDllType::SCRIPT);
	}
	HMODULE CRKEngine::GetDll(EDllType eType)
	{
		return 	m_DllLoader->GetDLL(eType);
	}
	void CRKEngine::LoadDll(EDllType eType)
	{
		m_DllLoader->LoadDll(eType);
	}
	void CRKEngine::FreeDll(EDllType eType)
	{
		m_DllLoader->FreeDll(eType);
	}
	void CRKEngine::ScriptMonitor()
	{
		bool bCurFlag = m_bFocus;
		bool bBeforFlag = m_bBeforFocus;
		m_bBeforFocus = bCurFlag;

		if (bCurFlag == true && bBeforFlag == false)
		{
			//감시
			int a = 0;
			//imgui 연동시 loading 창 띄우기
			// 1. Script 변경점 있는지 확인
			//  1-1. 변경점 있으면 loading 시작.
			//  1-2. 변경점 없으면 loading 즉시 완료.
			//완료될때까지 block 상태
			bool bChangeScript = m_M_ScriptReLoad->TimeStempMonitor();
			if (bChangeScript)
			{
				m_M_ScriptReLoad->ScriptsCompile();
			}
			else
			{
				//나중에 거의 완성될 때 오류 완전히 없으면 이 부분 지우면 됨.
				m_M_ScriptReLoad->ScriptsCompile();
			}
			
		}
	}
	void CRKEngine::WindowMonitor()
	{
		WindowSizeMonitor();
		WindowFocusMonitor();
	}
	bool CRKEngine::WindowSizeMonitor()
	{
		float beforeWidth = mtRendererData->Resolution.x;
		float beforeHeight = mtRendererData->Resolution.y;
		RECT clientRect = {};
		UINT eType = TYPETOINT(EHwndType::MAIN);
		GetClientRect(m_hWnds[eType], &clientRect);
		mtRendererData->Resolution.x = clientRect.right - clientRect.left;
		mtRendererData->Resolution.y = clientRect.bottom - clientRect.top;

		if (beforeWidth == mtRendererData->Resolution.x && beforeHeight == mtRendererData->Resolution.y)
			return false;

		return true;
	}
	bool CRKEngine::WindowFocusMonitor()
	{
		//LBTN Down
	///////////////
	// input manager 만든후에는 이부분 바꾼다.
	///////////////
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			POINT cursorPos;
			GetCursorPos(&cursorPos);

			//HWND foregroundWindow = GetForegroundWindow();
			for (auto itr = m_hWnds.begin(); itr != m_hWnds.end(); itr++)
			{
				HWND hWnd = *itr;
				HWND windowUnderCursor = WindowFromPoint(cursorPos);

				if (windowUnderCursor == hWnd)
				{
					m_bFocus = true;
					return true;
				}
				else
				{
					m_bFocus = false;
				}
			}
		}
		return false;
	}
}

DLL_DECLSPEC void CreateEngine()
{
	RKEngine::CRKEngine::Create();
	return;
}

DLL_DECLSPEC void DestroyEngine()
{
	RKEngine::CRKEngine::Destroy();
	return;
}

DLL_DECLSPEC RKEngine::CRKEngine* const& GetInstEngine()
{
	return RKEngine::CRKEngine::GetInstance();
}
