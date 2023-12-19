#pragma once

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif

#define CLASS_COPY(type) public: virtual type* Copy(){return new type(*this);} 
#define PROPERTY(_get,_set) _declspec(property(get=_get,put=_set))
#define SET_PROPERTY(_set) _declspec(property(put=_set))
#define GET_PROPERTY(_get) _declspec(property(get=_get))

enum class DLL_DECLSPEC EComponentType
{
	//update
	TRANSFORM,
	//render
	MESHRENDERER,
	//script
	SCRIPT,
	END
};