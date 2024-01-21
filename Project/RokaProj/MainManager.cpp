#include "pch.h"
#include "MainManager.h"
#include <Renderer/external.h>
#include <Renderer/CDxDevice.h>
RKEngine::CRKEngine* MainManager::m_Engine = nullptr;
MainManager::MainManager()
{
	M_FILE->Create();
	LM_DLL->Create();
	LM_DLL->Initialize();
	LM_DLL->LoadDll(EDllType::RENDER);
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
	m_Engine->SetFileManager(M_FILE);
	m_Engine->Initialize();

	HMODULE& render_dll = LM_DLL->GetDLL(EDllType::RENDER);
	RENDERER_LIFE_FUNC renderCreate = (RENDERER_LIFE_FUNC)GetProcAddress(render_dll, "CreateDXDevice");
	renderCreate();
	RENDERER_INST_FUNC renderInst = (RENDERER_INST_FUNC)GetProcAddress(render_dll, "GetDXDevice");
	Renderer::CDxDevice* Device = (Renderer::CDxDevice*)renderInst();

	//Device->InitDevice(m_Engine);
	m_Engine->SetRenderDevice(Device);
}
MainManager::~MainManager()
{
	HMODULE& engine_dll = LM_DLL->GetDLL(EDllType::ENGINE);
	if (engine_dll == NULL)
	{
		Assert(engine_dll != NULL, L"EngineDll Load Error : null ");
	}
	HMODULE& render_dll = LM_DLL->GetDLL(EDllType::RENDER);
	if (render_dll == NULL)
	{
		Assert(render_dll != NULL, L"RendererDll Load Error : null ");
	}
	m_Engine->Release();
	
	ENGINE_LIFE_FUNC engine_destroy = (ENGINE_LIFE_FUNC)GetProcAddress(engine_dll, "DestroyEngine");
	engine_destroy();
	m_Engine = nullptr;
	LM_DLL->FreeDll(EDllType::ENGINE);
	RENDERER_LIFE_FUNC renderDestroy = (RENDERER_LIFE_FUNC)GetProcAddress(render_dll, "DestroyDXDevice");
	renderDestroy();
	LM_DLL->FreeDll(EDllType::RENDER);
	LM_DLL->Release();
	LM_DLL->Destroy();
	M_FILE->Destroy();
}
