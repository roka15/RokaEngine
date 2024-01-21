#pragma once

namespace Renderer
{
	class CDxDevice;
	class CInnerDevice 
	{
	private:
		CInnerDevice();
		~CInnerDevice();

		friend class CDxDevice;
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	};
}


