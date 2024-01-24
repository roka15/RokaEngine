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