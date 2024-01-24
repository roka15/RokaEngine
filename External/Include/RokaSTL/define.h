#pragma once


#define MemoryLeakCheck _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#define MemoryLeakNumber(number) _CrtSetBreakAlloc(number);
#define SINGLETON(type) private: type();virtual ~type();friend class rokaStl::Singleton<type>;
#define MANAGER public: virtual void Initialize()override;virtual void Release()override;
#define MANAGERLOOP MANAGER void Loop()override;
#define MCreate(type) type::Create();
#define MDestroy(type) type::Destroy();
#define GetInst(type) type::GetInstance();

#define TYPETOINT(type) (UINT)(type)

#define Assert(expression,message) assert(expression && message)

#define CLASS_COPY(type) public: virtual type* Copy()override{return new type(*this);} 
#define CLASS_NOCOPY(type) public: virtual type* Copy(){return nullptr;Assert(nullptr,TEXT("Copy가 지원되지 않는 Class 입니다."));}
#define PROPERTY(_get,_set) _declspec(property(get=_get,put=_set))
#define SET_PROPERTY(_set) _declspec(property(put=_set))
#define GET_PROPERTY(_get) _declspec(property(get=_get))


#define LM_DLL General::CDllLoader::GetInstance()
#define M_FILE General::FileManager::GetInstance()

#define MAXPATH 255
#define MAXEXTEN 50
#define MAXTXT 260
#ifdef UNICODE
#define STR_LENGTH_MULTIPLIER 2
#else
#define STR_LENGTH_MULTIPLIER 1
#endif

