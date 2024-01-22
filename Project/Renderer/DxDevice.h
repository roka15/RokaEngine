#pragma once
#include "CDevice.h"
namespace Renderer
{
	class CDxDevice : public CDevice , public rokaStl::Singleton<CDxDevice>
	{
		SINGLETON(CDxDevice)
	public:
		virtual HRESULT InitDevice(PEngine _engine)override;
		virtual void Render()override;
	private:
		HRESULT CreateSwapChain(HWND _hwnd, Vec2 _resolution);
		HRESULT CreateRenderTargetView(Vec2 _resolution);
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	};
}


