#include "pch.h"
#include "Display.h"

Display::Display(unsigned int width, unsigned int height)
	: mU(.0f), mV(.0f), mWidth(width), mHeight(height), mAspectRatio(width / height)
{


}

Display::Display(float u, float v, unsigned int width, unsigned int height)
	: mU(u), mV(v), mWidth(width), mHeight(height), mAspectRatio(width / height)
{


}

void Display::Bind(const ID3D11RenderTargetView* rtv)
{
	if (rtv == nullptr)
	{
		return;
	}

	mRenderTarget = rtv;

}
