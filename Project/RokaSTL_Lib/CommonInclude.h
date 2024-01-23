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
#include <Windows.h>
//
//#include <DirectXMath.h>
//#include <DirectXPackedVector.h>
//using namespace DirectX;
//using namespace DirectX::PackedVector;


#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
using namespace std::experimental;
using namespace std::experimental::filesystem;

#include "SimpleMath.h"
using namespace DirectX::SimpleMath;

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;


#ifdef _NOT_CMAKE_BUILD
#pragma comment(lib,"openssl\\lib\\libssl.lib")
#pragma comment(lib,"openssl\\lib\\libcrypto.lib")
#endif

#include <openssl/sha.h>

#include "define.h"
#include "func.h"
#include "operators.h"
#include "LRU_Queue.h"
#include "RBT.h"
#include "SingleTon.h"
#include "MemoryPool.h"

#include "interface.h"
#include "enums.h"
#include "Entity.h"
#include "SPtr.h"
#include "Resource.h"

//manager
#include "ObjectPoolManager.h"
#include "DllLoader.h"
#include "FileManager.h"
