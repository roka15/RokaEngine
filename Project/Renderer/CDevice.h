#pragma once
#include "pch.h"
#ifdef RENDERER_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

namespace RKEngine
{
	class CRKEngine;
	typedef CRKEngine* PEngine;
}
namespace Renderer
{
	class DLL_DECLSPEC CDevice 
	{
	public:
		virtual HRESULT InitDevice(RKEngine::PEngine _engine) = 0;
		virtual void Render() = 0;
		
		virtual void* GetDevicePtr() = 0;
		virtual void** GetDevicePPtr() = 0;
		virtual void* GetContextPtr() = 0;
		virtual void** GetContextPPtr() = 0;

		RKEngine::PEngine GetEngine();
	protected:
		RKEngine::PEngine mEngine;
	};
}



