#include "pch.h"
#include "RKEngine.h"
#include "ScriptReLoad.h"
#include <Renderer/CDevice.h>
#include <Renderer/ResourceManager.h>
#include <Script/ScriptManager.h>
namespace RKEngine
{
	CRKEngine::CRKEngine()
		:m_bFocus(true),
		m_bBeforFocus(true),
		m_hWnds{},
		mMDllLoader(nullptr),
		mMFile(nullptr),
		mMScriptReLoad(nullptr),
		mMResource(nullptr),
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
		CreateManager();
		InitManager();
	}
	void CRKEngine::Loop()
	{
		WindowMonitor();
		ScriptMonitor();
		mMDevice->Render();
	}
	void CRKEngine::Release()
	{
		delete mMScriptReLoad;
		delete mtRendererData;
		
		FreeDll();
		mMResource->Release();

		mMDllLoader = nullptr;
		mMFile = nullptr;
		mMScriptReLoad = nullptr;
		mMScript = nullptr;
		mMResource = nullptr;

		Renderer::CResourceManager::Destroy();
		General::FileManager::Destroy();
	}
	void CRKEngine::SetHWND(HWND _hWnd, EHwndType _eType)
	{
		 m_hWnds[TYPETOINT(_eType)] = _hWnd; 
		 if (_eType == EHwndType::MAIN)
			 WindowSizeMonitor();
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
		mMDllLoader->LoadDll(EDllType::SCRIPT);
	}
	void CRKEngine::FreeDll()
	{
		HMODULE scriptModule = mMDllLoader->GetDLL(EDllType::SCRIPT);
		if (scriptModule == nullptr)
			return;
		M_ScriptLife_PFUNC scriptDestroy = (M_ScriptLife_PFUNC)GetProcAddress(scriptModule, "DestroyManager");
		
		scriptDestroy();
	
		mMDllLoader->FreeDll(EDllType::SCRIPT);
	}
	HMODULE CRKEngine::GetDll(EDllType eType)
	{
		return 	mMDllLoader->GetDLL(eType);
	}
	void CRKEngine::LoadDll(EDllType eType)
	{
		mMDllLoader->LoadDll(eType);
	}
	void CRKEngine::FreeDll(EDllType eType)
	{
		mMDllLoader->FreeDll(eType);
	}
	void CRKEngine::CreateManager()
	{
		General::FileManager::Create();
		Renderer::CResourceManager::Create();
		mMFile = General::FileManager::GetInstance();
		mMScriptReLoad = new CScriptReLoad(this);
		mMResource = Renderer::CResourceManager::GetInstance();

		HMODULE scriptModule = mMDllLoader->GetDLL(EDllType::SCRIPT);
		M_ScriptLife_PFUNC scriptCreate = (M_ScriptLife_PFUNC)GetProcAddress(scriptModule, "CreateManager");
		scriptCreate();
		M_ScriptGetInst_PFUNC scriptInst = (M_ScriptGetInst_PFUNC)GetProcAddress(scriptModule, "GetManagerInstance");
		mMScript = (Script::ScriptManager*)scriptInst();
	}
	void CRKEngine::InitManager()
	{
		mMScript->Initialize();
		mMResource->Initialize();
	}
	void CRKEngine::ScriptMonitor()
	{
		bool bCurFlag = m_bFocus;
		bool bBeforFlag = m_bBeforFocus;
		m_bBeforFocus = bCurFlag;

		if (bCurFlag == true && bBeforFlag == false)
		{
			//����
			int a = 0;
			//imgui ������ loading â ����
			// 1. Script ������ �ִ��� Ȯ��
			//  1-1. ������ ������ loading ����.
			//  1-2. ������ ������ loading ��� �Ϸ�.
			//�Ϸ�ɶ����� block ����
			bool bChangeScript = mMScriptReLoad->TimeStempMonitor();
			if (bChangeScript)
			{
				mMScriptReLoad->ScriptsCompile();
			}
			else
			{
				//���߿� ���� �ϼ��� �� ���� ������ ������ �� �κ� ����� ��.
				mMScriptReLoad->ScriptsCompile();
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
	// input manager �����Ŀ��� �̺κ� �ٲ۴�.
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
