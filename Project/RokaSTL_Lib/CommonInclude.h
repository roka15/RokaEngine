#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <map>

#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <typeinfo>
#include <format>
#include <tchar.h>




#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
using namespace std::experimental;
using namespace std::experimental::filesystem;



#include <wrl.h>
using namespace Microsoft::WRL;

#include <d3d11.h>					// DirectX11
#include <d3dcompiler.h>			// Shader ÄÄÆÄÀÏ
#include <DirectXMath.h>			// DX Math
#include <DirectXPackedVector.h>	

using namespace DirectX;
using namespace DirectX::PackedVector;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")


#include "SimpleMath.h"
using namespace DirectX::SimpleMath;

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;

#pragma comment(lib,"openssl\\lib\\libcrypto.lib")
#pragma comment(lib,"openssl\\lib\\libssl.lib")

#include <openssl/sha.h>

#include "define.h"
#include "func.h"
#include "operators.h"
#include "LRU_Queue.h"
#include "RBT.h"
#include "SingleTon.h"
#include "MemoryPool.h"

#include "interface.h"

//manager
#include "ObjectPoolManager.h"
#include "DllLoader.h"
#include "FileManager.h"