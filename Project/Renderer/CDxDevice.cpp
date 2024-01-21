#include "pch.h"
#include "CDxDevice.h"
#include "InnerDevice.h"
#include  <Engine/RKEngine.h>
namespace Renderer
{
	CDxDevice::CDxDevice() :
		mEngine(nullptr),
		mDevice(nullptr)
	{
	}
	CDxDevice::~CDxDevice()
	{
	}
	HRESULT CDxDevice::InitDevice(PEngine _engine)
	{
		mEngine = _engine;
		HWND hwnd = mEngine->GetHWND(EHwndType::MAIN);
		HRESULT hr = S_OK;

		const Vec2& Resolution = mEngine->GetResolution();
		UINT width = Resolution.x;
		UINT height = Resolution.y;

		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_HARDWARE;
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

		//1 Device »ý¼º
		hr = D3D11CreateDevice(nullptr, driverType,
			nullptr, createDeviceFlags,
			nullptr, 0,
			D3D11_SDK_VERSION,
			mDevice->mDevice.GetAddressOf(),
			&featureLevel,
			mDevice->mContext.GetAddressOf()
		);

		if (FAILED(hr))
			return hr;

		hr = CreateSwapChain(hwnd,Resolution);

		if (FAILED(hr))
			return hr;

		hr = CreateRenderTargetView(Resolution);

		if (FAILED(hr))
			return hr;

		return hr;
	}
	HRESULT CDxDevice::CreateSwapChain(HWND _hwnd,Vec2 _resolution)
	{
		DXGI_SWAP_CHAIN_DESC SwapDesc;
		ZeroMemory(&SwapDesc, sizeof(SwapDesc));
		SwapDesc.BufferCount = 1;
		SwapDesc.BufferDesc.Width = _resolution.x;
		SwapDesc.BufferDesc.Height = _resolution.y;
		SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		SwapDesc.BufferDesc.RefreshRate.Numerator = 60;
		SwapDesc.BufferDesc.RefreshRate.Denominator = 1;
		SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		SwapDesc.OutputWindow = _hwnd;
		SwapDesc.SampleDesc.Count = 1;
		SwapDesc.SampleDesc.Quality = 0;
		SwapDesc.Windowed = TRUE;

		ComPtr<IDXGIDevice> pDevice;
		ComPtr<IDXGIAdapter> pAdapter;
		ComPtr<IDXGIFactory> pFactory;
		HRESULT hr = mDevice->mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDevice.GetAddressOf());
		hr = pDevice->QueryInterface(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
		hr = pAdapter->QueryInterface(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
		hr = pFactory->CreateSwapChain(mDevice->mDevice.Get(), &SwapDesc, mDevice->mSwapChain.GetAddressOf());

		return hr;
	}
	HRESULT CDxDevice::CreateRenderTargetView(Vec2 _resolution)
	{
		ID3D11Texture2D* pBackBuffer = NULL;
		HRESULT hr = mDevice->mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if (FAILED(hr))
			return hr;
		hr = mDevice->mDevice->CreateRenderTargetView(pBackBuffer, NULL, mDevice->mRenderTargetView.GetAddressOf());
		pBackBuffer->Release();

		if (FAILED(hr))
			return hr;

		mDevice->mContext->OMSetRenderTargets(1, &mDevice->mRenderTargetView, NULL);

		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)_resolution.x;
		vp.Height = (FLOAT)_resolution.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		mDevice->mContext->RSSetViewports(1, &vp);

		return hr;
	}
	void CDxDevice::Render()
	{
		float ClearColor[4] = { 0.f, 0.f, 0.f, 0.f }; 
		mDevice->mContext->ClearRenderTargetView(mDevice->mRenderTargetView.Get(), ClearColor);
		mDevice->mSwapChain->Present(0, 0);
	}
}

