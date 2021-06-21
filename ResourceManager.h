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

	class SwapTex2D : public IMemory
	{
	public:
		SwapTex2D(unsigned int width, unsigned height);
		~SwapTex2D();

		ID3D11Texture2D* GetTexture() const { return mTex.Get(); }
		ID3D11RenderTargetView* GetRTV() const { return mRenderTarget.Get(); }

	private:
		unsigned int mWidth, mHeight;

		ComPtr<ID3D11Texture2D> mTex;
		ComPtr<ID3D11RenderTargetView> mRenderTarget;

		virtual void Generate() override;
		virtual void Release() override;

	};

	template<class _Ty>
	class ConstantBuffer
	{
	public:
		ConstantBuffer(_Ty* data);
		~ConstantBuffer();
		ID3D11Buffer* GetBuffer() const { return mBuffer.Get(); }

		void Write();

	private:
		ComPtr<ID3D11Buffer> mBuffer;
		_Ty* mData;
	};

	template<class _Ty>
	inline ConstantBuffer<_Ty>::ConstantBuffer(_Ty* data)
		:	mData(data)
	{
		HRESULT result;
		auto device = Hardware::GetDevice();
		
		D3D11_BUFFER_DESC desc{};
		D3D11_SUBRESOURCE_DATA subData{};

		desc.ByteWidth = sizeof(_Ty);
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE_DEFAULT;
		
		subData.pSysMem = reinterpret_cast<void*>(data);

		result = device->CreateBuffer(&desc, &subData, mBuffer.GetAddressOf());
		if (result != S_OK)
		{
			DebugLog("WARNING, failed to create buffer.");
			return;
		}
	}

	template<class _Ty>
	inline ConstantBuffer<_Ty>::~ConstantBuffer()
	{
		mBuffer.ReleaseAndGetAddressOf();
	}

	template<class _Ty>
	inline void ConstantBuffer<_Ty>::Write()
	{
		static auto context = Hardware::GetContext();

		context->UpdateSubresource(mBuffer.Get(), 0, nullptr, reinterpret_cast<void*>(mData), 0, 0);
	}

	template<class _Ty>
	class RWStructuredBuffer
	{
	public:
		RWStructuredBuffer(_Ty* data, unsigned int count);
		~RWStructuredBuffer();

		ID3D11Buffer* GetBuffer() const { return mBuffer.Get(); }
		ID3D11ShaderResourceView* GetView() const { return mView.Get(); }

		void Write();

	private:
		ComPtr<ID3D11Buffer> mBuffer;
		ComPtr<ID3D11ShaderResourceView> mView;
		_Ty* mData;
	};

	template<class _Ty>
	inline RWStructuredBuffer<_Ty>::RWStructuredBuffer(_Ty* data, unsigned int count)
		: mData(data)
	{
		HRESULT result;
		auto device = Hardware::GetDevice();

		D3D11_BUFFER_DESC desc{};
		D3D11_SUBRESOURCE_DATA subData{};
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};

		desc.ByteWidth = sizeof(_Ty) * count;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = sizeof(_Ty);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		subData.pSysMem = data;

		srvDesc.Format = DXGI_FORMAT_UNKNOWN;
		srvDesc.Buffer.ElementWidth = sizeof(_Ty);
		srvDesc.Buffer.NumElements = count;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;

		result = device->CreateBuffer(&desc, &subData, mBuffer.GetAddressOf());
		if (result != S_OK)
		{
			DebugLog("WARNING, failed to create buffer.");
			return;
		}

		result = device->CreateShaderResourceView(mBuffer.Get(), &srvDesc, mView.GetAddressOf());
		if (result != S_OK)
		{
			DebugLog("WARNING, failed to create shader resource view.");
			return;
		}

	}

	template<class _Ty>
	inline RWStructuredBuffer<_Ty>::~RWStructuredBuffer()
	{
		mBuffer.ReleaseAndGetAddressOf();
	}

	template<class _Ty>
	inline void RWStructuredBuffer<_Ty>::Write()
	{
		static auto context = Hardware::GetContext();

		if (mBuffer == nullptr)
		{
			DebugLog("buffer was invalid, check RWStructuredBuffer constructor.");
			return;
		}

		context->UpdateSubresource(mBuffer.Get(), 0, nullptr, reinterpret_cast<void*>(mData), 0, 0);
	}

}