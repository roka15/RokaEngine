#pragma once
#include "pch.h"

#ifdef RENDERER_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS


namespace Renderer
{
	namespace ConstBf
	{
		struct DLL_DECLSPEC t_GlobalData
		{
			Vec2 Resolution;
		};

		struct DLL_DECLSPEC t_TransformData
		{
			Matrix MatWorld;
			Matrix MatWorldInv;
			
			Matrix MatView;
			Matrix MatViewInv;

			Matrix MatProj;
			Matrix MatProjInv;

			Matrix MatWV;
			Matrix MatWVP;
		};
	}
	

	struct DLL_DECLSPEC t_VertexData
	{
		Vec3 Position;
		Vec4 Color;
		Vec2 UV;
	};
}
