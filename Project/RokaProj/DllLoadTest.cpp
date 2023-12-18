#include "pch.h"
#include <TestCopy/interface.h>
//#include "..//GenericLib//GenericManager.h"
#include <RokaSTL/define.h>
#include "operators.h"
#include <Windows.h>
#include <crtdbg.h>






int main()
{
	MemoryLeakCheck

	//Dll Test
	HMODULE testDll = LoadLibrary(L"..\\..\\External\\Dll\\Debug\\GenericLib\\GenericLib.dll");
	if (testDll == NULL)
		int a = 0;
	
	//using InstanceFunc = MyClass & (*)();
	//InstanceFunc getInstance = (InstanceFunc)GetProcAddress(testDll, "Instance");
	//MyClass& MyInstance = Singleton<MyClass>::Instance();
	
	ManagerLife_PFUNC M_GenericCreate = (ManagerLife_PFUNC)GetProcAddress(testDll, "CreateManager");
	M_GenericCreate(EGenericManagerType::TYPE1);
	ManagerGetInst_PFUNC M_GenericInst = (ManagerGetInst_PFUNC)GetProcAddress(testDll, "GetManagerInstance");

	IManager* testptr = M_GenericInst(EGenericManagerType::TYPE1);
	testptr->Initialize();

	IManager* ptr = M_GenericInst(EGenericManagerType::TYPE2);
	ptr->Initialize();
	
	testptr->Release();
	ptr->Release();
	
	ManagerLife_PFUNC M_GenericDestroy = (ManagerLife_PFUNC)GetProcAddress(testDll, "DestroyManager");
	M_GenericDestroy(EGenericManagerType::TYPE1);
	//FreeLibrary(testDll);
}