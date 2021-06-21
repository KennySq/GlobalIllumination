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

	static inline ID3D11Device* GetDevice() { return GetInstance()->mDevice11.Get(); }
	static inline ID3D10Device* GetDevice10() { return GetInstance()->mDevice10.Get(); }


	static inline ID3D11DeviceContext* GetContext() { return GetInstance()->mContext.Get(); }
	//static inline ID3D10DeviceContext* GetContext10() { return GetInstance()->mContext }
	
	static inline IDXGISwapChain* GetSwapChain() { return GetInstance()->mSwapChain.Get(); }

	static HWND GetHandle() { return GetInstance()->mHandle; }
	static HINSTANCE GetHandleInstnace() { return GetInstance()->mHandleInstance; }
private:
	Hardware(unsigned int width, unsigned int height, HWND handle, HINSTANCE handleInst);
	
	ComPtr<ID3D11Device> mDevice11;
	ComPtr<ID3D11DeviceContext> mContext;
	ComPtr<IDXGISwapChain> mSwapChain;

	ComPtr<ID3D10Device> mDevice10;
//	ComPtr<ID3D10Context> mContext10;

	HWND mHandle;
	HINSTANCE mHandleInstance;

	static Hardware* mInstance;


};

