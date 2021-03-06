#include "pch.h"
#include "Display.h"

Display::Display(unsigned int width, unsigned int height)
	: mU(.0f), mV(.0f), mWidth(width), mHeight(height), mAspectRatio(static_cast<float>(width) / height)
{
	mViewport.Width = width;
	mViewport.Height = height;

	mViewport.MaxDepth = 1.0f;
	mViewport.MinDepth = 0.0f;
	mViewport.TopLeftX = mU;
	mViewport.TopLeftY = mV;


}

Display::Display(float u, float v, unsigned int width, unsigned int height)
	: mU(u), mV(v), mWidth(width), mHeight(height), mAspectRatio(static_cast<float>(width) / height)
{
	mViewport.Width = width;
	mViewport.Height = height;

	mViewport.MaxDepth = 1.0f;
	mViewport.MinDepth = 0.0f;
	mViewport.TopLeftX = mU;
	mViewport.TopLeftY = mV;


}

void Display::BindRenderTarget(ID3D11RenderTargetView* rtv)
{
	if (rtv == nullptr)
	{
		DebugLog("render target view was invalid.");
		return;
	}

	mRenderTarget = rtv;

}

void Display::BindDepthStencil(ID3D11DepthStencilView* dsv)
{
	if (dsv == nullptr)
	{
		DebugLog("depth stencil view was invalid.");

		return;
	}

	mDepthStencil = dsv;
}
