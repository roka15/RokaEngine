#pragma once

#ifdef RENDERER_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

#define PDEVICE GetDevice()->GetDevicePtr()
#define PPDEVICE GetDevice()->GetDevicePPtr()
#define PCONTEXT  GetDevice()->GetContextPtr()
#define PPCONTEXT GetDevice()->GetContextPPtr()
#define DX11_PDEVICE reinterpret_cast<ID3D11Device*>(PDEVICE)
#define DX11_PPDEVICE reinterpret_cast<ID3D11Device**>(PPDEVICE)
#define DX11_PCONTEXT reinterpret_cast<ID3D11DeviceContext*>(PCONTEXT)
#define DX11_PPCONTEXT reinterpret_cast<ID3D11DeviceContext**> (PPCONTEXT)

#define ENGINE GetDevice()->GetEngine()

namespace Renderer
{
	enum class DLL_DECLSPEC EDeviceType
	{
		None,
		Dx11Device,
	};
	
	enum class DLL_DECLSPEC EResourceType
	{
		None,
		Mesh,
		Material,
		GraphicsShader,
	};
}
