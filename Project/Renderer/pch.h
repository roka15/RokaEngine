// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

#ifdef RENDERER_EXPORTS
#define SCRIPTDLL_DECLSPEC __declspec(dllexport)
#else
#define SCRIPTDLL_DECLSPEC __declspec(dllimport)
#endif


// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"

#pragma comment(lib,"RokaSTL\\RokaSTL_Lib.lib")
#include <RokaSTL/CommonInclude.h>


#include <wrl.h>
using namespace Microsoft::WRL;

#include <d3d11.h>					// DirectX11
#include <d3dcompiler.h>			// Shader 컴파일
#include <DirectXMath.h>			// DX Math
#include <DirectXPackedVector.h>	

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <Engine/define.h>
#include "define.h"
#include "external.h"
#include "global.h"
#endif //PCH_H
