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
	class CInnerDevice;
	typedef RKEngine::CRKEngine* PEngine;
	class DLL_DECLSPEC CDxDevice : public rokaStl::Singleton<CDxDevice>
	{
		SINGLETON(CDxDevice)
	public:
		virtual HRESULT InitDevice(PEngine _engine);
		void Render();
	private:
		HRESULT CreateSwapChain(HWND _hwnd, Vec2 _resolution);
		HRESULT CreateRenderTargetView(Vec2 _resolution);	
	private:
		PEngine mEngine;
		CInnerDevice*const mDevice;
	};
}



