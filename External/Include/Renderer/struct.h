#pragma once
#include "pch.h"

#ifdef RENDERER_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS


namespace Renderer
{
	struct DLL_DECLSPEC t_RendererData
	{
		Vec2 Resolution;
	};
}
