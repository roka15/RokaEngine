#include "pch.h"
#include "external.h"
#include "DxDevice.h"


static Renderer::EDeviceType g_s_DeviceType = Renderer::EDeviceType::None;
DLL_DECLSPEC void CreateDevice(Renderer::EDeviceType _type)
{
	g_s_DeviceType = Renderer::EDeviceType::Dx11Device;
	switch (g_s_DeviceType)
	{
	case Renderer::EDeviceType::Dx11Device:
		Renderer::CDxDevice::Create();
		break;
	}
	return;
}
DLL_DECLSPEC void DestroyDevice()
{
	switch(g_s_DeviceType)
	{
	case Renderer::EDeviceType::Dx11Device:
		Renderer::CDxDevice::Destroy();
		break;
	}
	return;
}
DLL_DECLSPEC Renderer::CDevice* const& GetDevice()
{
	switch (g_s_DeviceType)
	{
	case Renderer::EDeviceType::Dx11Device:
		return Renderer::CDxDevice::GetInstance();
	}
	return nullptr;
}
