#pragma once

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif



enum class DLL_DECLSPEC EComponentType
{
	//update
	TRANSFORM,
	//render
	MESHRENDERER,
	//script
	SCRIPT,
	END
};


enum class DLL_DECLSPEC EHwndType
{
	MAIN,
	END
};