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
	virtual DLL_DECLSPEC void Initialize() = 0;
	virtual DLL_DECLSPEC void Release() = 0;
};

enum class DLL_DECLSPEC EGenericManagerType
{
	TYPE1,
	TYPE2,
	END
};
typedef void (*ManagerLife_PFUNC)(EGenericManagerType);
typedef  IManager* (*ManagerGetInst_PFUNC)(EGenericManagerType);

extern IManager* testInst;


extern "C"
{
	DLL_DECLSPEC void CreateManager(EGenericManagerType type);
	DLL_DECLSPEC void DestroyManager(EGenericManagerType type);
	DLL_DECLSPEC IManager* GetManagerInstance(EGenericManagerType type);
}

IManager* GetMGenericInst();
IManager* GetMTestClassInst();
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
