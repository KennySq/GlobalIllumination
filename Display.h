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

	void BindRenderTarget(ID3D11RenderTargetView* rtv);
	void BindDepthStencil(ID3D11DepthStencilView* dsv);

	ID3D11RenderTargetView* GetRenderTarget() const { return mRenderTarget; }
	ID3D11DepthStencilView* GetDepthStencil() const { return mDepthStencil; }
	const D3D11_VIEWPORT& GetViewport() const { return mViewport; }

private:
	Display(const Display&) = delete;

	unsigned int mWidth;
	unsigned int mHeight;

	float mU; // 0.0 ~ 1.0
	float mV; // 0.0 ~ 1.0

	float mAspectRatio;

	D3D11_VIEWPORT mViewport;

	ID3D11RenderTargetView* mRenderTarget;
	ID3D11DepthStencilView* mDepthStencil;

};

