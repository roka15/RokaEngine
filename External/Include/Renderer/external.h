#pragma once
//#include "pch.h"
#ifdef RENDERER_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

#include <Renderer/struct.h>
#include "define.h"
#include "Entity.h"

namespace Renderer 
{
	class DLL_DECLSPEC CDevice;
}

typedef void (*RENDERER_CREATE_FUNC)(Renderer::EDeviceType _type);
typedef void (*RENDERER_DESTROY_FUNC)(void);
typedef Renderer::CDevice* const& (*RENDERER_INST_FUNC)(void);


extern "C"
{
	DLL_DECLSPEC void CreateDevice(Renderer::EDeviceType _type);
	DLL_DECLSPEC Renderer::CDevice*const& GetDevice();
	DLL_DECLSPEC void DestroyDevice();
}


