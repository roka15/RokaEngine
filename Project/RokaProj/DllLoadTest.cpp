#include "pch.h"
#include <TestCopy/interface.h>
#include "define.h"
#include <Windows.h>
#include <crtdbg.h>

//#pragma comment(lib,"RokaSTL\\RokaSTL_Lib.lib")





int main()
{
	MemoryLeakCheck

	//Dll Test
	HMODULE testDll = LoadLibrary(L"..\\..\\External\\Dll\\GenericLib\\Debug\\GenericLib.dll");
	if (testDll == NULL)
		int a = 0;

	//using InstanceFunc = MyClass & (*)();
	//InstanceFunc getInstance = (InstanceFunc)GetProcAddress(testDll, "Instance");
	//MyClass& MyInstance = Singleton<MyClass>::Instance();
	MTestClass_PFUNC testfunc = (MTestClass_PFUNC)GetProcAddress(testDll, "GetMTestClassInst");
	IManager* testptr = testfunc();
	testptr->Print();
	MGeneric_PFUNC func = (MGeneric_PFUNC)GetProcAddress(testDll, "GetMGenericInst");
	IManager* ptr = func();
	ptr->Print();

	testptr->Destroy();
	ptr->Destroy();


	FreeLibrary(testDll);
}