#pragma once
enum class EDllType
{
	ENGINE,
	SCRIPT,
	RENDER,
	SERVER,
	END,
};

enum class EFilePathType
{
	SOLUTION,
	INCLUDE,
	PROJECT,
	RESOURCE,
};


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
}

enum class EComponentType
{
	//update
	TRANSFORM,
	//render
	MESHRENDERER,
	//script
	SCRIPT,
	END
};


enum class EHwndType
{
	MAIN,
	END
};