#include "pch.h"
#include "Transform.h"



Transform::Transform()
	: mTransform()
{
	XMStoreFloat4x4(&mTransform, XMMatrixIdentity());

	generate();
}

Transform::Transform(InstanceBuffer buffer)
	: mTransform(buffer.mWorld)
{
	generate();
}

Transform::Transform(const Transform& rhs)
	: mTransform(rhs.mTransform)
{
	generate();
}

Transform::~Transform()
{
	Release();

}

void Transform::Translate(float x, float y, float z)
{
	mTransform._41 += x;
	mTransform._42 += y;
	mTransform._43 += z;
}

void Transform::Rotate(float pitch, float yaw, float roll)
{
	XMMATRIX mat = XMLoadFloat4x4(&mTransform);
	mat *= XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	XMStoreFloat4x4(&mTransform, mat);
}

void Transform::SetScale(float x, float y, float z)
{
	mTransform._11 = x;
	mTransform._22 = y;
	mTransform._33 = z;
}

void Transform::Init()
{
}

void Transform::Release()
{
	mBuffer.ReleaseAndGetAddressOf();
}

void Transform::Update(float delta)
{
	static auto context = Hardware::GetContext();
	static HRESULT result;
	D3D11_MAPPED_SUBRESOURCE sub;
	result = context->Map(mBuffer.Get(), D3D11CalcSubresource(0,0,1), D3D11_MAP::D3D11_MAP_WRITE_DISCARD, D3D11_MAP_FLAG_DO_NOT_WAIT, &sub);

	if (result != S_OK)
	{
		DebugLog("faield to map buffer.");
		return;
	}

	XMFLOAT4X4* mat = reinterpret_cast<XMFLOAT4X4*>(sub.pData);

	*mat = mTransform;

	context->Unmap(mBuffer.Get(), D3D11CalcSubresource(0, 0, 1));

}

void Transform::Render(float delta)
{
}

bool Transform::generate()
{
	auto device = Hardware::GetDevice();
	HRESULT result;

	D3D11_BUFFER_DESC desc{};
	D3D11_SUBRESOURCE_DATA subData{};
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc{};

	desc.ByteWidth = sizeof(InstanceBuffer);
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.StructureByteStride = sizeof(InstanceBuffer);
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	subData.pSysMem = &mTransform;

	srvDesc.Buffer.NumElements = 1;
	srvDesc.Buffer.ElementWidth = sizeof(InstanceBuffer);
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;

	result = device->CreateBuffer(&desc, &subData, mBuffer.GetAddressOf());
	if (result != S_OK)
	{
		DebugLog("failed to generate a buffer.");
		return false;
	}


	result = device->CreateShaderResourceView(mBuffer.Get(), &srvDesc, mView.GetAddressOf());
	if (result != S_OK)
	{
		DebugLog("failed to create shader resource view.");
		return false;
	}

	return true;
}
