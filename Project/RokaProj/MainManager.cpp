#include "pch.h"
#include "MainManager.h"
RKEngine::CRKEngine* MainManager::m_Engine = nullptr;
MainManager::MainManager()
{
	LM_DLL->Create();
	LM_DLL->Initialize();
	LM_DLL->LoadDll(EDllType::ENGINE);
	HMODULE& engine_dll =  LM_DLL->GetDLL(EDllType::ENGINE);
	if (engine_dll == NULL)
	{
		Assert(engine_dll != NULL, L"EngineDll Load Error : null ");
	}
	
	ENGINE_LIFE_FUNC engine_create = (ENGINE_LIFE_FUNC)GetProcAddress(engine_dll, "CreateEngine");
	ENGINE_INST_FUNC engine_inst = (ENGINE_INST_FUNC)GetProcAddress(engine_dll, "GetInstEngine");

	engine_create();
	m_Engine = reinterpret_cast<RKEngine::CRKEngine*const>(engine_inst());
	m_Engine->SetLMDll(LM_DLL);
	m_Engine->Initialize();
}
MainManager::~MainManager()
{
	HMODULE& engine_dll = LM_DLL->GetDLL(EDllType::ENGINE);
	if (engine_dll == NULL)
	{
		Assert(engine_dll != NULL, L"EngineDll Load Error : null ");
	}

	m_Engine->Release();
	
	ENGINE_LIFE_FUNC engine_destroy = (ENGINE_LIFE_FUNC)GetProcAddress(engine_dll, "DestroyEngine");
	engine_destroy();
	m_Engine = nullptr;
	LM_DLL->FreeDll(EDllType::ENGINE);
	
	LM_DLL->Release();
	LM_DLL->Destroy();
}
