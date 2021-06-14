#pragma once

namespace Resources
{
	struct IMemory
	{
		virtual void Generate() = 0;
		virtual void Release() = 0;
	};

	enum class TEX_TYPE
	{
		eShader		= 8,
		eRender		= 32,
		eDepth		= 64,
		eUnorder	= 128,

	};

	class Tex2D : protected IMemory
	{
	public:
		Tex2D(unsigned int width, unsigned int height, TEX_TYPE type, DXGI_FORMAT format = DXGI_FORMAT_R32G32B32A32_FLOAT);
		~Tex2D();

		ID3D11Texture2D* GetTexture() const { return mTex.Get(); }
		ID3D11RenderTargetView* GetRTV() const { return mRenderTarget.Get(); }
		ID3D11ShaderResourceView* GetSRV() const { return mShaderResource.Get(); }
		ID3D11UnorderedAccessView* GetUAV() const { return mUnorderedAccess.Get(); }
		ID3D11DepthStencilView* GetDSV() const { return mDepthStencil.Get(); }


	private:
		TEX_TYPE mType;
		DXGI_FORMAT mFormat;
		unsigned int mWidth, mHeight;

		ComPtr<ID3D11Texture2D> mTex;

		ComPtr<ID3D11RenderTargetView> mRenderTarget;
		ComPtr<ID3D11ShaderResourceView> mShaderResource;
		ComPtr<ID3D11UnorderedAccessView> mUnorderedAccess;
		ComPtr<ID3D11DepthStencilView> mDepthStencil;

		virtual void Generate() override;
		virtual void Release() override;
	};

	class Buffer2D : public IMemory
	{
	public:
		Buffer2D(unsigned int width, unsigned height);
		~Buffer2D();

		ID3D11Texture2D* GetTexture() const { return mTex.Get(); }
		ID3D11RenderTargetView* GetRTV() const { return mRenderTarget.Get(); }

	private:
		unsigned int mWidth, mHeight;

		ComPtr<ID3D11Texture2D> mTex;
		ComPtr<ID3D11RenderTargetView> mRenderTarget;

		virtual void Generate() override;
		virtual void Release() override;

	};

}

