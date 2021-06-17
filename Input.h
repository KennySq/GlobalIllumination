#pragma once
#include"IRoutine.h"
class Input : public IRoutine
{
public:
	Input(unsigned int width, unsigned int height);
	~Input();

	bool ReadKeyboard();
	bool ReadMouse();

	void ProcessInput();

	unsigned int GetMouseX() const { return mMouseX; }
	unsigned int GetMouseY() const { return mMouseY; }

	bool GetKey(unsigned int keyCode) const { return mKeyState[keyCode] & 0x80; }

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float delta) override;
	virtual void Render(float delta) override;

private:



	ComPtr<IDirectInput8> mDirectInput;
	ComPtr<IDirectInputDevice8> mKeyboard;
	ComPtr<IDirectInputDevice8> mMouse;

	unsigned int mWidth, mHeight;
	int mMouseX, mMouseY;

	unsigned int mKeyState[256];
	DIMOUSESTATE mMouseState;



};

