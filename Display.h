#pragma once



class Display
{
public:
	Display(unsigned int width, unsigned int height);
	Display(float u, float v, unsigned int width, unsigned int height);
	
	unsigned int GetWidth() const { return mWidth; }
	unsigned int GetHeight() const { return mHeight; }
	
	float GetU() const { return mU; }
	float GetV() const { return mV; }
	float GetAspectRatio() const { return mAspectRatio; }

	void Bind(const ID3D11RenderTargetView* rtv);
	const ID3D11RenderTargetView* GetResource() const { return mRenderTarget; }

private:
	Display(const Display&) = delete;

	unsigned int mWidth;
	unsigned int mHeight;

	float mU; // 0.0 ~ 1.0
	float mV; // 0.0 ~ 1.0

	float mAspectRatio;

	const ID3D11RenderTargetView* mRenderTarget;

};

