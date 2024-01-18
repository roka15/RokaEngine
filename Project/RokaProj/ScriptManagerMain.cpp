#include "pch.h"
#include <Script/external.h>
#include <Script/ScriptManager.h>
#include <Script/CTestScript.h>

int main()
{
	MemoryLeakCheck
		//Dll Test
	HMODULE EngineDll = LoadLibrary(L"..\\..\\External\\Dll\\Engine\\Debug\\Engine.dll");
	HMODULE ScriptDll = LoadLibrary(L"..\\..\\External\\Dll\\Script\\Debug\\Script.dll");
	if (EngineDll == NULL)
	{
		return 0;
	}
	if (ScriptDll == NULL)
	{
		HRESULT result = GetLastError();
		return 0;
	}


	M_ScriptLife_PFUNC MScriptCreate = (M_ScriptLife_PFUNC)GetProcAddress(ScriptDll, "CreateManager");
	MScriptCreate();

	M_ScriptGetInst_PFUNC MScriptInst = (M_ScriptGetInst_PFUNC)GetProcAddress(ScriptDll, "GetManagerInstance");
	rokaStl::IManager* inst = MScriptInst();

	ScriptManager* MScript = dynamic_cast<ScriptManager*>(inst);
	MScript->Initialize();
	CScript* script = MScript->GetScript(TYPETOINT(EScriptType::CTestScript));
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

	FreeLibrary(EngineDll);
	

}