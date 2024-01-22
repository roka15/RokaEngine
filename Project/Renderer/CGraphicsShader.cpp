#include "pch.h"
#include "CGraphicsShader.h"
#include "DxDevice.h"
#include <Engine/RKEngine.h>
namespace Renderer
{
	CGraphicsShader::CGraphicsShader()
		:CShader(EResourceType::GraphicsShader),
		mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{
	}
	CGraphicsShader::~CGraphicsShader()
	{
	}
	void CGraphicsShader::CreateVertexShader(const TCHAR* _ShaderFileName, const char* _MainName, const char* _ShaderVer)
	{
		const TCHAR* path = ENGINE->GetFileManager()->GetShaderCodePath();
		std::shared_ptr<TCHAR> fileName = AddTCHAR(path, _ShaderFileName);
		HRESULT hr = S_OK;
		std::shared_ptr<wchar_t> wFileName = nullptr;
#ifndef _UNICODE
		wFileName = ConvertWC2C((char*)fileName.get());
#else
		wFileName = fileName;
#endif

#ifdef VER_DX11
		hr = D3DCompileFromFile(wFileName.get(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			_MainName, _ShaderVer, 0, 0, mVertexBlob.GetAddressOf(), mErrorBlob.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBox(NULL,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return;
		}
		hr = DX11_PDEVICE->CreateVertexShader(mVertexBlob->GetBufferPointer(), mVertexBlob->GetBufferSize(), NULL, mVertexShader.GetAddressOf());
		if (FAILED(hr))
		{
			mVertexBlob->Release();
			return;
		}

		const size_t layoutLen = 2;
		D3D11_INPUT_ELEMENT_DESC layout[layoutLen] = {};
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

		hr = DX11_PDEVICE->CreateInputLayout(layout, layoutLen, mVertexBlob->GetBufferPointer(),
			mVertexBlob->GetBufferSize(), mVertexLayout.GetAddressOf());
		mVertexBlob->Release();

		if (FAILED(hr))
			return;
#endif
	}
	void CGraphicsShader::CreatePixelShader(const TCHAR* _ShaderFileName, const char* _MainName, const char* _ShaderVer)
	{
		const TCHAR* path = ENGINE->GetFileManager()->GetShaderCodePath();
		std::shared_ptr<TCHAR> fileName = AddTCHAR(path, _ShaderFileName);
		HRESULT hr = S_OK;
		std::shared_ptr<wchar_t> wFileName = nullptr;
#ifndef _UNICODE
		wFileName = ConvertWC2C((char*)fileName.get());
#else
		wFileName = fileName;
#endif

#ifdef VER_DX11
		hr = D3DCompileFromFile(wFileName.get(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, _MainName, _ShaderVer, 0, 0, mPixelBlob.GetAddressOf(), mErrorBlob.GetAddressOf());
		if (FAILED(hr))
		{
			MessageBox(NULL,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return;
		}

		// Create the pixel shader
		hr = DX11_PDEVICE->CreatePixelShader(mPixelBlob->GetBufferPointer(), mPixelBlob->GetBufferSize(), NULL, mPixelShader.GetAddressOf());
		mPixelBlob->Release();
		if (FAILED(hr))
			return;
#endif
	}
	void CGraphicsShader::UpdateData()
	{
#ifdef VER_DX11
		DX11_PCONTEXT->IASetInputLayout(mVertexLayout.Get());
		DX11_PCONTEXT->IASetPrimitiveTopology(mTopology);
	
		DX11_PCONTEXT->VSSetShader(mVertexShader.Get(), NULL, 0);
		DX11_PCONTEXT->PSSetShader(mPixelShader.Get(), NULL, 0);
#endif
	}
}