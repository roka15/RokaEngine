#pragma once

#ifdef RENDERER_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS


namespace Renderer
{
	enum class DLL_DECLSPEC EDeviceType
	{
		None,
		Dx11Device,
	};
}
