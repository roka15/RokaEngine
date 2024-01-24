#include "pch.h"
#include <Script/external.h>
#include <Renderer/external.h>
#include <Script/ScriptManager.h>
#include <Script/CTestScript.h>
#include <Renderer/CDevice.h>



int main()
{
	MemoryLeakCheck

		//Test1 - reload test
		 /*LM_DLL->LoadDll(EDllType::RENDER);
			 LM_DLL->LoadDll(EDllType::SCRIPT);
			 HMODULE RenderDll = LM_DLL->GetDLL(EDllType::RENDER);
			 HMODULE ScriptDll = LM_DLL->GetDLL(EDllType::SCRIPT);

			 RENDERER_LIFE_FUNC renderCreate = (RENDERER_LIFE_FUNC)GetProcAddress(RenderDll, "CreateDXDevice");
			 RENDERER_LIFE_FUNC renderDestroy = (RENDERER_LIFE_FUNC)GetProcAddress(RenderDll, "DestroyDXDevice");
			 renderCreate();

			 RENDERER_INST_FUNC renderInst = (RENDERER_INST_FUNC)GetProcAddress(RenderDll, "GetDXDevice");
			 Renderer::CDevice* Device = renderInst();
			 Device->InitDevice(engine);


			 M_ScriptLife_PFUNC MScriptCreate = (M_ScriptLife_PFUNC)GetProcAddress(ScriptDll, "CreateManager");
			 MScriptCreate();

			 M_ScriptGetInst_PFUNC MScriptInst = (M_ScriptGetInst_PFUNC)GetProcAddress(ScriptDll, "GetManagerInstance");
			 rokaStl::IManager* inst = MScriptInst();

			 Script::ScriptManager* MScript = dynamic_cast<Script::ScriptManager*>(inst);
			 MScript->Initialize();
			 CScript* script = MScript->GetScript(TYPETOINT(Script::EScriptType::CTestScript));
			 script->Print();
			 script->Start();
			 script->Update();
			 script->SaveToSceneMetaFile();
			 script->LoadToSceneMetaFile();
			 CTestScript* testScript = dynamic_cast<CTestScript*>(script);
			 CTestScript* copyScript = (CTestScript*)testScript->Copy();

			 testScript->SetData(1);
			 copyScript->SetData(2);

			 delete testScript;
			 delete copyScript;
			 M_ScriptLife_PFUNC MScriptDestroy = (M_ScriptLife_PFUNC)GetProcAddress(ScriptDll, "DestroyManager");
			 MScriptDestroy();


			 FreeLibrary(ScriptDll);
			 TCHAR path[255] = {};
			 GetCurrentDirectory(255, path);
			 Sleep(2);
			 int result = system("rmdir /s /q D:\\3DRKEngine\\External\\Dll\\Script\\Debug");
			 result = system("cd /D D:\\3DRKEngine\\Project\\Script\\build && cmake .. && cmake --build ./");
			 if (result != 0)
				 int a = 0;
			 */
			 //Test2
	LM_DLL->Create();
	LM_DLL->Initialize();
	General::CDllLoader* inst = General::CDllLoader::GetInstance();
	LM_DLL->LoadDll(EDllType::RENDER);
	HMODULE render_dll = LM_DLL->GetDLL(EDllType::RENDER);
	RENDERER_CREATE_FUNC renderCreate = (RENDERER_CREATE_FUNC)GetProcAddress(render_dll, "CreateDevice");
	DWORD error = GetLastError();
	renderCreate(Renderer::EDeviceType::Dx11Device);
	RENDERER_INST_FUNC renderInst = (RENDERER_INST_FUNC)GetProcAddress(render_dll, "GetDevice");
	Renderer::CDevice* Device = (Renderer::CDevice*)renderInst();

	LM_DLL->LoadDll(EDllType::ENGINE);

	HMODULE EngineDll = LM_DLL->GetDLL(EDllType::ENGINE);
	ENGINE_LIFE_FUNC engineCreate = (ENGINE_LIFE_FUNC)GetProcAddress(EngineDll, "CreateEngine");
	ENGINE_LIFE_FUNC engineDestroy = (ENGINE_LIFE_FUNC)GetProcAddress(EngineDll, "DestroyEngine");
	engineCreate();
	ENGINE_INST_FUNC engineInst = (ENGINE_INST_FUNC)GetProcAddress(EngineDll, "GetInstEngine");
	RKEngine::CRKEngine* engine = engineInst();
	engine->SetLMDll(LM_DLL);
	engine->Initialize();

	HMODULE ScriptDll = LM_DLL->GetDLL(EDllType::SCRIPT);

	M_ScriptLife_PFUNC MScriptCreate = (M_ScriptLife_PFUNC)GetProcAddress(ScriptDll, "CreateManager");
	MScriptCreate();

	M_ScriptGetInst_PFUNC MScriptInst = (M_ScriptGetInst_PFUNC)GetProcAddress(ScriptDll, "GetManagerInstance");
	rokaStl::IManager* Scriptinst = MScriptInst();

	//Script ReLoad Test - Engine CReLoadScript.cpp private : ScriptsCompile() 와 동일 기능.
	{
	LM_DLL->FreeDll(EDllType::SCRIPT);
	TCHAR path[255] = {};
	GetCurrentDirectory(255, path);
	Sleep(2);
	int result = system("rmdir /s /q D:\\3DRKEngine\\External\\Dll\\Script\\Debug");
	result = system("cd /D D:\\3DRKEngine\\Project\\Script\\build && cmake .. && cmake --build ./");
	if (result != 0)
		int a = 0;
	LM_DLL->LoadDll(EDllType::SCRIPT);
	ScriptDll = LM_DLL->GetDLL(EDllType::SCRIPT);
	if (ScriptDll == nullptr)
		Assert(nullptr, TEXT("ReLoad GetDll Error!"));
	}


	Device->InitDevice(engine);
	engine->SetRenderDevice(Device);


	engine->Release();
	engineDestroy();
	engine = nullptr;
	LM_DLL->FreeDll(EDllType::ENGINE);

	RENDERER_DESTROY_FUNC renderDestroy = (RENDERER_DESTROY_FUNC)GetProcAddress(render_dll, "DestroyDevice");
	renderDestroy();
	LM_DLL->FreeDll(EDllType::RENDER);

	LM_DLL->Release();
	LM_DLL->Destroy();
}