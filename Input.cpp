#include "pch.h"
#include "Input.h"

Input::Input(unsigned int width, unsigned int height)
	: mKeyState(), mWidth(width), mHeight(height)
{
	Init();
}

Input::~Input()
{
	Release();
}

bool Input::ReadKeyboard()
{
	HRESULT result;

	result = mKeyboard->GetDeviceState(sizeof(mKeyState), reinterpret_cast<void*>(&mKeyState));
	if (result != S_OK)
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mKeyboard->Acquire();
		}
		else
		{
			DebugLog("failed to get keyboard state.");
			return false;
		}
	}

	return true;
}

bool Input::ReadMouse()
{
	HRESULT result;

	result = mMouse->GetDeviceState(sizeof(DIMOUSESTATE), reinterpret_cast<void*>(&mMouseState));
	if (result != S_OK)
	{
		DebugLog("failed to get mouse state");

		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mMouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void Input::ProcessInput()
{
	mMouseX += mMouseState.lX;
	mMouseY += mMouseState.lY;

	if (mMouseX < 0) { mMouseX = 0; }
	if (mMouseY < 0) { mMouseY = 0; }

	if (mMouseX > mWidth) { mMouseX = mWidth; }
	if (mMouseY > mHeight) { mMouseY = mHeight; }

	return;
}

void Input::Init()
{
	HRESULT result;

	HWND handle = Hardware::GetHandle();
	HINSTANCE hInst = Hardware::GetHandleInstnace();

	result = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mDirectInput, nullptr);
	if (result != S_OK)
	{
		DebugLog("failed to create direct input.");
		return;
	}

	result = mDirectInput->CreateDevice(GUID_SysKeyboard, mKeyboard.GetAddressOf(), nullptr);
	if (result != S_OK)
	{
		DebugLog("failed to create keyboard device");
		return;
	}

	result = mDirectInput->CreateDevice(GUID_SysMouse, mMouse.GetAddressOf(), nullptr);
	if (result != S_OK)
	{
		DebugLog("failed to create mouse device");
		return;
	}

	result = mKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (result != S_OK)
	{
		DebugLog("failed to set keyboard data format");

		return;
	}

	result = mMouse->SetDataFormat(&c_dfDIMouse);
	if (result != S_OK)
	{
		DebugLog("failed to set mouse data format");
		return;
	}

	result = mKeyboard->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (result != S_OK)
	{
		DebugLog("failed to set keyboard cooperative level");
		return;
	}

	result = mMouse->SetCooperativeLevel(handle, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (result != S_OK)
	{
		DebugLog("faield to set mouse cooperative level");
		return;
	}

	result = mKeyboard->Acquire();
	if (result != S_OK)
	{
		DebugLog("failed to acquire the keyboard");
		return;
	}

	result = mMouse->Acquire();
	if (result != S_OK)
	{
		DebugLog("failed to acquire the mouse");
		return;
	}

	return;
}

void Input::Release()
{

	if (mMouse != nullptr)
	{
		mMouse->Unacquire();
		mMouse->Release();
	}

	if (mKeyboard != nullptr)
	{
		mKeyboard->Unacquire();
		mKeyboard->Release();
	}

	mDirectInput.ReleaseAndGetAddressOf();

}

void Input::Update(float delta)
{

	bool result = ReadMouse();
	if (result == false)
	{
	//	DebugLog("mouse control has been lost.");
	}


	result = ReadKeyboard();
	if (result == false)
	{
	//	DebugLog("keyboard control has been lost.");
	}

	ProcessInput();



	return;
}

void Input::Render(float delta)
{
}
