#pragma once
#include"Display.h"

using namespace Microsoft::WRL;

class Hardware
{
public:
	
	static Hardware* GetInstance(unsigned int width = 0, unsigned int height = 0, HWND handle = nullptr, HINSTANCE handleInst = nullptr) { 
		
		if (mInstance == nullptr)
		{
			mInstance = new Hardware(width, height, handle, handleInst);
		}

		return mInstance;
	}

	static ID3D11Device* GetDevice() { return GetInstance()->mDevice.Get(); }
	static ID3D11DeviceContext* GetContext() { return GetInstance()->mContext.Get(); }
	static IDXGISwapChain* GetSwapChain() { return GetInstance()->mSwapChain.Get(); }

	static HWND GetHandle() { return GetInstance()->mHandle; }
	static HINSTANCE GetHandleInstnace() { return GetInstance()->mHandleInstance; }
private:
	Hardware(unsigned int width, unsigned int height, HWND handle, HINSTANCE handleInst);
	
	ComPtr<ID3D11Device> mDevice;
	ComPtr<ID3D11DeviceContext> mContext;
	ComPtr<IDXGISwapChain> mSwapChain;
	
	HWND mHandle;
	HINSTANCE mHandleInstance;

	static Hardware* mInstance;


};

