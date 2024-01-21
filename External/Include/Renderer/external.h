#pragma once
//#include "pch.h"
#ifdef RENDERER_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

#include <Renderer/struct.h>

namespace Renderer 
{
	class DLL_DECLSPEC CDxDevice;
}
typedef void (*RENDERER_LIFE_FUNC)(void);
typedef Renderer::CDxDevice* const& (*RENDERER_INST_FUNC)(void);


extern "C"
{
	DLL_DECLSPEC void CreateDXDevice();
	DLL_DECLSPEC Renderer::CDxDevice*const& GetDXDevice();
	DLL_DECLSPEC void DestroyDXDevice();
}


