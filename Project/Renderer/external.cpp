#include "pch.h"
#include "external.h"
#include "CDxDevice.h"


DLL_DECLSPEC void CreateDXDevice()
{
	Renderer::CDxDevice::Create();
	return;
}
DLL_DECLSPEC void DestroyDXDevice()
{
	Renderer::CDxDevice::Destroy();
	return;
}
DLL_DECLSPEC Renderer::CDxDevice* const& GetDXDevice()
{
	return Renderer::CDxDevice::GetInstance();
}
