#pragma once
#include "CDevice.h"
namespace Renderer
{
	class CMesh;
	class CGraphicsShader;
	class CDxDevice : public CDevice , public rokaStl::Singleton<CDxDevice>
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		

		SINGLETON(CDxDevice)
	public:
		virtual HRESULT InitDevice(RKEngine::PEngine _engine)override;
		virtual void Render()override;
		virtual void* GetDevicePtr()override;
		virtual void** GetDevicePPtr()override;
		virtual void* GetContextPtr()override;
		virtual void** GetContextPPtr()override;


	private:
		HRESULT CreateSwapChain(HWND _hwnd, Vec2 _resolution);
		HRESULT CreateRenderTargetView(Vec2 _resolution);
	};
}


