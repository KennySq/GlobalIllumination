#include "pch.h"
#include "ResourceManager.h"

Resources::Tex2D::Tex2D(unsigned int width, unsigned int height, TEX_TYPE type, DXGI_FORMAT format)
	: mFormat(format), mWidth(width), mHeight(height), mType(type)
{
	Generate();

}

Resources::Tex2D::~Tex2D()
{
	Release();
}

void Resources::Tex2D::Generate()
{
	HRESULT result;
	auto device = Hardware::GetDevice();
	D3D11_TEXTURE2D_DESC texDesc{};
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{};
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc{};

	unsigned int flag = static_cast<unsigned int>(mType);
	unsigned int renderFlag = static_cast<unsigned int>(TEX_TYPE::eRender);
	unsigned int depthFlag = static_cast<unsigned int>(TEX_TYPE::eDepth);
	unsigned int shaderFlag = static_cast<unsigned int>(TEX_TYPE::eShader);
	unsigned int unorderFlag = static_cast<unsigned int>(TEX_TYPE::eUnorder);

	texDesc.Format = mFormat;
	texDesc.Width = mWidth;
	texDesc.Height = mHeight;
	texDesc.ArraySize = 1;
	texDesc.BindFlags = static_cast<unsigned int>(mType);
	texDesc.MipLevels = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;

	result = device->CreateTexture2D(&texDesc, nullptr, mTex.GetAddressOf());
	assert(result == S_OK && "failed to create a texture2d");

	if ((flag & renderFlag) == renderFlag)
	{
		rtvDesc.Format = mFormat;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

		result = device->CreateRenderTargetView(mTex.Get(), &rtvDesc, mRenderTarget.GetAddressOf());
		assert(result == S_OK && "failed to create a render target view");
	}

	if ((flag & depthFlag) == depthFlag)
	{
		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

		result = device->CreateDepthStencilView(mTex.Get(), &dsvDesc, mDepthStencil.GetAddressOf());
		assert(result == S_OK && "failed to create a depth stencil view");
	}

	if ((flag & unorderFlag) == unorderFlag)
	{
		uavDesc.Format = mFormat;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;

		result = device->CreateUnorderedAccessView(mTex.Get(), &uavDesc, mUnorderedAccess.GetAddressOf());
		assert(result == S_OK && "failed to create a unordered access view.");
	}
	
	if ((flag & shaderFlag) == shaderFlag)
	{
		srvDesc.Format = mFormat;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;

		result = device->CreateShaderResourceView(mTex.Get(), &srvDesc, mShaderResource.GetAddressOf());
		assert(result == S_OK && "failed to create a shader resource view.");
	}

	return;
}

void Resources::Tex2D::Release()
{
	mTex.ReleaseAndGetAddressOf();
}

Resources::SwapTex2D::SwapTex2D(unsigned int width, unsigned height) : mWidth(width), mHeight(height)
{
	Generate();
}

Resources::SwapTex2D::~SwapTex2D()
{
	Release();
}

void Resources::SwapTex2D::Generate()
{
	HRESULT result;
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{};

	auto device = Hardware::GetDevice();
	auto swapChain = Hardware::GetSwapChain();

	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(mTex.GetAddressOf()));
	assert(result == S_OK && "failed to create a buffer from swap chain");

	result = device->CreateRenderTargetView(mTex.Get(), &rtvDesc, mRenderTarget.GetAddressOf());
	assert(result == S_OK && "failed to create a render target view from swap chain buffer.");

}

void Resources::SwapTex2D::Release()
{
	mTex.ReleaseAndGetAddressOf();
	mRenderTarget.ReleaseAndGetAddressOf();
}
