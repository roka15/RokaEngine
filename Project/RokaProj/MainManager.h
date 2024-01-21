#pragma once
#include "pch.h"
class MainManager : public rokaStl::Singleton<MainManager>
{
	SINGLETON(MainManager)
public:
	void Initialize(HWND _hwnd);
	void Release();
	RKEngine::CRKEngine* m_Engine;
};

