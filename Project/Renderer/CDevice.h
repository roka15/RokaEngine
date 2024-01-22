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
}
namespace Renderer
{
	typedef RKEngine::CRKEngine* PEngine;
	class DLL_DECLSPEC CDevice 
	{
	public:
		virtual HRESULT InitDevice(PEngine _engine) = 0;
		virtual void Render() = 0;	
	protected:
		PEngine mEngine;
	};
}



