#pragma once
namespace Renderer
{
	enum class EDeviceType
	{
		None,
		Dx11Device,
	};

	enum class EResourceType
	{
		Mesh,
		Material,
		GraphicsShader,
		MAX
	};

	enum class EConstBFType
	{
		GLOBAL,
		TRANSFORM,
		
	};
}