#pragma once
#include "pch.h"
class MainManager : public rokaStl::Singleton<MainManager>
{
	SINGLETON(MainManager)
public:
	static RKEngine::CRKEngine* m_Engine;
};

