#include "pch.h"
#include "Hardware.h"

Hardware* Hardware::mInstance = nullptr;
Hardware::Hardware(unsigned int width, unsigned int height, HWND handle, HINSTANCE handleInst)
	: mHandle(handle), mHandleInstance(handleInst)
{
	HRESULT result;

	D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0 };
	DXGI_SWAP_CHAIN_DESC scDesc{};

	scDesc.BufferCount = 1;
	scDesc.BufferDesc.Width = width;
	scDesc.BufferDesc.Height = height;
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferDesc.RefreshRate.Denominator = 1;
	scDesc.BufferDesc.RefreshRate.Numerator = 60;
	scDesc.OutputWindow = handle;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scDesc.Windowed = true;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		nullptr, 0, D3D11_SDK_VERSION, &scDesc, mSwapChain.GetAddressOf(), mDevice.GetAddressOf(), &levels[0], mContext.GetAddressOf());
	
	assert(result == S_OK && "failed to create device and swapchain.");

}
