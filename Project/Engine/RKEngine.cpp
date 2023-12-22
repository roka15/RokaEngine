#include "pch.h"
#include "RKEngine.h"

namespace RKEngine
{
	CRKEngine::CRKEngine()
		:m_bFocus(true),
		m_bBeforFocus(true),
		m_hWnds{},
		m_v2WinSize{},
		m_DllLoader(nullptr)
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
	}
	void CRKEngine::Loop()
	{
		WindowMonitor();
		ScriptMonitor();
	}
	void CRKEngine::Release()
	{
		FreeDll();
		m_DllLoader = nullptr;
	}
	void CRKEngine::LoadDll()
	{
		//_pcr_dllload->LoadDll(EDllType::RENDER);
		m_DllLoader->LoadDll(EDllType::SCRIPT);
	}
	void CRKEngine::FreeDll()
	{
		//_pcr_dllload->FreeDll(EDllType::RENDER);
		m_DllLoader->FreeDll(EDllType::SCRIPT);
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
		}
	}
	void CRKEngine::WindowMonitor()
	{
		WindowSizeMonitor();
		WindowFocusMonitor();
	}
	bool CRKEngine::WindowSizeMonitor()
	{
		float beforeWidth = m_v2WinSize.x;
		float beforeHeight = m_v2WinSize.y;
		RECT clientRect = {};
		UINT eType = TYPETOINT(EHwndType::MAIN);
		GetClientRect(m_hWnds[eType], &clientRect);
		m_v2WinSize.x = clientRect.right - clientRect.left;
		m_v2WinSize.y = clientRect.bottom - clientRect.top;

		if (beforeWidth == m_v2WinSize.x && beforeHeight == m_v2WinSize.y)
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
