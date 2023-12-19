#include "pch.h"
#include <Script/external.h>
#include <Script/ScriptManager.h>
#include <Script/CTestScript.h>

int main()
{
	MemoryLeakCheck
		//Dll Test
	HMODULE EngineDll = LoadLibrary(L"..\\..\\External\\Dll\\Debug\\Engine\\Engine.dll");
	HMODULE ScriptDll = LoadLibrary(L"..\\..\\External\\Dll\\Debug\\Script\\Script.dll");

	if (ScriptDll == NULL)
	{
		HRESULT result = GetLastError();
		int a = 0;
	}


	M_ScriptLife_PFUNC MScriptCreate = (M_ScriptLife_PFUNC)GetProcAddress(ScriptDll, "CreateManager");
	MScriptCreate();

	M_ScriptGetInst_PFUNC MScriptInst = (M_ScriptGetInst_PFUNC)GetProcAddress(ScriptDll, "GetManagerInstance");
	rokaStl::IManager* inst = MScriptInst();

	ScriptManager* MScript = dynamic_cast<ScriptManager*>(inst);
	MScript->Initialize();
	CScript* script = MScript->GetScript(TYPETOINT(EScriptType::TEST));
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
}