#include "pch.h"
#include "DxDevice.h"
#include  <Engine/RKEngine.h>
#include "Mesh.h"
#include "CGraphicsShader.h"
#include "ResourceManager.h"
namespace Renderer
{
	CDxDevice::CDxDevice()
	{

	}
	CDxDevice::~CDxDevice()
	{
	}
	HRESULT CDxDevice::InitDevice(RKEngine::PEngine _engine)
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
			mDevice.GetAddressOf(),
			&featureLevel,
			mContext.GetAddressOf()
		);

		if (FAILED(hr))
			return hr;

		hr = CreateSwapChain(hwnd, Resolution);

		if (FAILED(hr))
			return hr;

		hr = CreateRenderTargetView(Resolution);

		if (FAILED(hr))
			return hr;

		struct SimpleVertex
		{
			XMFLOAT3 Pos;
			XMFLOAT4 Color;
		};
		std::vector<t_VertexData> vertices;
		vertices.push_back(t_VertexData{ Vec3(0.0f, 0.5f, 0.5f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2(0.f, 0.f) });
		vertices.push_back(t_VertexData{ Vec3(0.5f, -0.5f, 0.5f), Vec4(1.0f,1.0f,0.0f,1.0f), Vec2(0.f, 0.f) });
		vertices.push_back(t_VertexData{ Vec3(-0.5f, -0.5f, 0.5f), Vec4(1.0f,1.0f,0.0f,1.0f), Vec2(0.f, 0.f) });

		const int indexCnt = 3;
		int indexs[indexCnt] =
		{
			0,1,2
		};
		ID3D11DeviceContext* context = DX11_PCONTEXT;
		CResourceManager::Create();
		CResourceManager* rm = CResourceManager::GetInstance();
		
		
		General::SPtr<CMesh> mesh = new CMesh(true);
		mesh->Create(vertices.data(), vertices.size(), indexs, indexCnt);
		CGraphicsShader* shader = new CGraphicsShader();
		shader->CreateVertexShader(TEXT("//std3D.fx"), "VS_Main", "vs_5_0");
		shader->CreatePixelShader(TEXT("//std3D.fx"), "PS_Main", "ps_5_0");

		rm->AddRes<CMesh>(TEXT("TriangleMesh"),mesh);
		rm->AddRes<CGraphicsShader>(TEXT("DefaultShader"), shader);
		return hr;
	}
	void CDxDevice::Render()
	{
		float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), ClearColor);
		CResourceManager* rm = CResourceManager::GetInstance();
		General::SPtr<CMesh> mesh = rm->FindRes<CMesh>(TEXT("TriangleMesh"));
		General::SPtr<CGraphicsShader> shader = rm->FindRes<CGraphicsShader>(TEXT("DefaultShader"));
		shader->UpdateData();
		mesh->Render();
		mSwapChain->Present(0, 0);
	}
	void* CDxDevice::GetDevicePtr()
	{
		return mDevice.Get();
	}
	void** CDxDevice::GetDevicePPtr()
	{
		return (void**)mDevice.GetAddressOf();
	}
	void* CDxDevice::GetContextPtr()
	{
		return mContext.Get();
	}
	void** CDxDevice::GetContextPPtr()
	{
		return (void**)mContext.GetAddressOf();
	}
	HRESULT CDxDevice::CreateSwapChain(HWND _hwnd, Vec2 _resolution)
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
		SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		SwapDesc.Flags = 0;
		SwapDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

		ComPtr<IDXGIDevice> pDevice;
		ComPtr<IDXGIAdapter> pAdapter;
		ComPtr<IDXGIFactory> pFactory;
		HRESULT hr = mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDevice.GetAddressOf());
		hr = pDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
		hr = pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
		hr = pFactory->CreateSwapChain(mDevice.Get(), &SwapDesc, mSwapChain.GetAddressOf());

		return hr;
	}
	HRESULT CDxDevice::CreateRenderTargetView(Vec2 _resolution)
	{
		ID3D11Texture2D* pBackBuffer = NULL;
		HRESULT hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		if (FAILED(hr))
			return hr;
		hr = mDevice->CreateRenderTargetView(pBackBuffer, NULL, mRenderTargetView.GetAddressOf());
		pBackBuffer->Release();

		if (FAILED(hr))
			return hr;

		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), NULL);

		D3D11_VIEWPORT vp;
		vp.Width = (FLOAT)_resolution.x;
		vp.Height = (FLOAT)_resolution.y;
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		mContext->RSSetViewports(1, &vp);

		return hr;
	}
}