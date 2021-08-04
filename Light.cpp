#include "pch.h"
#include "Light.h"

long long DirectionalLight::mLightID = 0;
long long PointLight::mLightID = 0;

DirectionalLight::DirectionalLight(XMVECTOR direction, float intensity)
{
	HRESULT result;
	ID3D11Device* device = Hardware::GetDevice();


	XMStoreFloat3(&mRaw.mDirection, direction);
	mRaw.mIntensity = intensity;

	XMMATRIX mat;
	mat = XMMatrixLookToLH(XMVectorSet(0, 0, 0, 1), direction, XMVectorSet(0, 1, 0, 0));
	XMStoreFloat4x4(&mRaw.mTransform, XMMatrixIdentity() * mat);

	D3D11_BUFFER_DESC desc{};
	D3D11_SUBRESOURCE_DATA data{};

	data.pSysMem = &mRaw;
	desc.ByteWidth = sizeof(DirectionalLightBuffer);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.Usage = D3D11_USAGE_DEFAULT;

	result = device->CreateBuffer(&desc, &data, mBuffer.GetAddressOf());
	if (result != S_OK)
	{
		DebugLog("failed to create directional light buffer");
		return;
	}

	MemoryBank::AddLight(this);

	mLightID++;

	Init();
}

DirectionalLight::~DirectionalLight()
{
	Release();
}

void DirectionalLight::Init()
{
}

void DirectionalLight::Release()
{
	mBuffer.ReleaseAndGetAddressOf();
}

void DirectionalLight::Update(float delta)
{
	static auto context = Hardware::GetContext();

	context->UpdateSubresource(mBuffer.Get(), 0, nullptr, &mRaw, 0, 0);
}

void DirectionalLight::Render(float delta)
{
}

void PointLight::Init()
{
}

void PointLight::Release()
{
}

PointLight::PointLight(XMVECTOR position, XMVECTOR color, float intensity)
{
	HRESULT result;
	ID3D11Device* device = Hardware::GetDevice();

	XMStoreFloat3(&mRaw.mColor, color);
	mRaw.mIntensity = intensity;

	XMMATRIX mat;
	mat = XMMatrixLookToLH(position, XMVectorSet(1, 0, 0, 1), XMVectorSet(0, 1, 0, 0));

	D3D11_BUFFER_DESC desc{};
	D3D11_SUBRESOURCE_DATA data{};

	data.pSysMem = &mRaw;
	desc.ByteWidth = sizeof(PointLightBuffer);
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.StructureByteStride = sizeof(PointLightBuffer);

	result = device->CreateBuffer(&desc, &data, mBuffer.GetAddressOf());
	if (result != S_OK)
	{
		DebugLog("failed to create point light buffer");
		return;
	}
	MemoryBank::AddLight(this);

	mLightID++;

	Init();

}

PointLight::~PointLight()
{
}

void PointLight::Update(float delta)
{
	static auto context = Hardware::GetContext();

	context->UpdateSubresource(mBuffer.Get(), 0, nullptr, &mRaw, 0, 0);
}

void PointLight::Render(float delta)
{
}
