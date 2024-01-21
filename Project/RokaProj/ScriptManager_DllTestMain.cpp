#include "pch.h"
#include <Script/external.h>
#include <Renderer/external.h>
#include <Script/ScriptManager.h>
#include <Script/CTestScript.h>
#include <Renderer/CDxDevice.h>



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
			 Renderer::CDxDevice* Device = renderInst();
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
	
	M_FILE->Create();
	LM_DLL->Create();
	LM_DLL->Initialize();
	rokaStl::CDllLoader* inst = rokaStl::CDllLoader::GetInstance();
	LM_DLL->LoadDll(EDllType::RENDER);
	HMODULE render_dll = LM_DLL->GetDLL(EDllType::RENDER);
	RENDERER_LIFE_FUNC renderCreate = (RENDERER_LIFE_FUNC)GetProcAddress(render_dll, "CreateDXDevice");
	DWORD error = GetLastError();
	renderCreate();
	RENDERER_INST_FUNC renderInst = (RENDERER_INST_FUNC)GetProcAddress(render_dll, "GetDXDevice");
	Renderer::CDxDevice* Device = (Renderer::CDxDevice*)renderInst();

	LM_DLL->LoadDll(EDllType::ENGINE);

	HMODULE EngineDll = LM_DLL->GetDLL(EDllType::ENGINE);
	ENGINE_LIFE_FUNC engineCreate = (ENGINE_LIFE_FUNC)GetProcAddress(EngineDll, "CreateEngine");
	ENGINE_LIFE_FUNC engineDestroy = (ENGINE_LIFE_FUNC)GetProcAddress(EngineDll, "DestroyEngine");
	engineCreate();
	ENGINE_INST_FUNC engineInst = (ENGINE_INST_FUNC)GetProcAddress(EngineDll, "GetInstEngine");
	RKEngine::CRKEngine* engine = engineInst();
	engine->SetLMDll(LM_DLL);
	engine->SetFileManager(M_FILE);
	engine->Initialize();

	

	Device->InitDevice(engine);
	engine->SetRenderDevice(Device);


	engine->Release();
	engineDestroy();
	engine = nullptr;
	LM_DLL->FreeDll(EDllType::ENGINE);

	RENDERER_LIFE_FUNC renderDestroy = (RENDERER_LIFE_FUNC)GetProcAddress(render_dll, "DestroyDXDevice");
	renderDestroy();
	LM_DLL->FreeDll(EDllType::RENDER);

	LM_DLL->Release();
	LM_DLL->Destroy();
	M_FILE->Destroy();

}