#pragma once


#define MemoryLeakCheck _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#define SINGLETON(type) private: type();~type();friend class rokaStl::Singleton<type>;
#define MCreate(type) type::Create();
#define MDestroy(type) type::Destroy();
#define GetInstance(type) type::GetInstance();

#define TYPETOINT(type) (UINT)(type)
