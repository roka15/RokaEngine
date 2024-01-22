#pragma once

namespace Renderer
{
	class CDevice;
	class CDxDevice 
	{
	private:
		CDxDevice();
		~CDxDevice();

		friend class CDevice;
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	};
}


