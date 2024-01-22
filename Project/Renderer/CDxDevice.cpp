#include "pch.h"
#include "CDxDevice.h"
#include "InnerDevice.h"
#include  <Engine/RKEngine.h>
namespace Renderer
{
	Microsoft::WRL::ComPtr<ID3D11VertexShader> g_VS;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> g_pVertexLayout = NULL;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> g_PS;
	Microsoft::WRL::ComPtr<ID3D11Buffer> g_VB;
	Microsoft::WRL::ComPtr<ID3D11Buffer> g_IB;
	CDxDevice::CDxDevice() :
		mEngine(nullptr),
		mDevice(new CInnerDevice())
	{
	}
	CDxDevice::~CDxDevice()
	{
		delete mDevice;
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

		hr = CreateSwapChain(hwnd, Resolution);

		if (FAILED(hr))
			return hr;

		hr = CreateRenderTargetView(Resolution);

		if (FAILED(hr))
			return hr;

		return hr;
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
		HRESULT hr = mDevice->mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDevice.GetAddressOf());
		hr = pDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf());
		hr = pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf());
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

		mDevice->mContext->OMSetRenderTargets(1, mDevice->mRenderTargetView.GetAddressOf(), NULL);

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
		HRESULT hr = S_OK;
		// Compile the vertex shader
		ID3DBlob* pVSBlob = NULL;
		ID3DBlob* pErrorBlob = NULL;
		const TCHAR* path = mEngine->M_File->GetShaderCodePath();
		std::shared_ptr<TCHAR> fileName = AddTCHAR(path, TEXT("\\std3D.fx"));

		hr = D3DCompileFromFile(fileName.get(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "VS_Main", "vs_5_0", 0, 0, &pVSBlob, &pErrorBlob);
		if (FAILED(hr))
		{
			MessageBox(NULL,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return;
		}

	
		// Create the vertex shader
		hr = mDevice->mDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, g_VS.GetAddressOf());
		if (FAILED(hr))
		{
			pVSBlob->Release();
			return;
		}

		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[2] =
		{
		};
		layout[0].SemanticName = "POSITION";
		layout[0].SemanticIndex = 0;
		layout[0].InputSlot = 0;
		layout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		layout[0].InstanceDataStepRate = 0;
		layout[0].AlignedByteOffset = 0;
		layout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;


		layout[1].SemanticName = "COLOR";
		layout[1].SemanticIndex = 0;
		layout[1].InputSlot = 0;
		layout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		layout[1].InstanceDataStepRate = 0;
		layout[1].AlignedByteOffset = 12;
		layout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;

		UINT numElements = ARRAYSIZE(layout);

	
		// Create the input layout
		hr = mDevice->mDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
			pVSBlob->GetBufferSize(), g_pVertexLayout.GetAddressOf());
		pVSBlob->Release();
		if (FAILED(hr))
			return;

		// Set the input layout
		mDevice->mContext->IASetInputLayout(g_pVertexLayout.Get());

		// Compile the pixel shader
		ID3DBlob* pPSBlob = NULL;
		hr = D3DCompileFromFile(fileName.get(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, "PS_Main", "ps_5_0", 0, 0, &pPSBlob, &pErrorBlob);
		if (FAILED(hr))
		{
			MessageBox(NULL,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return;
		}
	
		// Create the pixel shader
		hr = mDevice->mDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, g_PS.GetAddressOf());
		pPSBlob->Release();
		if (FAILED(hr))
			return;
		struct SimpleVertex
		{
			XMFLOAT3 Pos;
			XMFLOAT4 Color;
		};

		// Create vertex buffer
		SimpleVertex vertices[] =
		{
		{XMFLOAT3(0.0f, 0.5f, 0.5f),XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
		{XMFLOAT3(0.5f, -0.5f, 0.5f),XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
		{XMFLOAT3(-0.5f, -0.5f, 0.5f),XMFLOAT4(1.0f,1.0f,0.0f,1.0f)},
		};
		int indexs[]
		{
			0,1,2
		};

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * 3;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		bd.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;
		
		hr = mDevice->mDevice->CreateBuffer(&bd, &InitData, g_VB.GetAddressOf());
		if (FAILED(hr))
			return;
		
		// Set vertex buffer
		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		mDevice->mContext->IASetVertexBuffers(0, 1, g_VB.GetAddressOf(), &stride, &offset);
	//	mDevice->mContext->IASetIndexBuffer(g_IB.Get(), &stride, &offset);
		// Set primitive topology
		mDevice->mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		float ClearColor[4] = { 0.5f, 0.5f, 0.5f, 1.f };
		

		mDevice->mContext->VSSetShader(g_VS.Get(), NULL, 0);
		mDevice->mContext->PSSetShader(g_PS.Get(), NULL, 0);
		mDevice->mContext->ClearRenderTargetView(mDevice->mRenderTargetView.Get(), ClearColor);
		mDevice->mContext->Draw(3,0);

		mDevice->mSwapChain->Present(0, 0);
	}
}

