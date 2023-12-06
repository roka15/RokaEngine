#pragma once

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

class GenericManager;
class TestClass;

class IManager
{
public:
	virtual DLL_DECLSPEC void Print() = 0;
	virtual DLL_DECLSPEC void Destroy() = 0;
};

typedef  IManager* (*MGeneric_PFUNC)();
typedef  IManager* (*MTestClass_PFUNC)();

extern IManager* testInst;

extern "C"
{
	DLL_DECLSPEC IManager* GetMGenericInst();
	DLL_DECLSPEC IManager* GetMTestClassInst();
}
//
//class MyClass;
//template <typename T>
//class Singleton
//{
//public:
//	static T& Instance();
//};
//
//template DLL_DECLSPEC MyClass& Singleton<MyClass>::Instance();
//
//
