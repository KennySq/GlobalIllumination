#include "pch.h"
#include "Camera.h"

Camera::Camera(XMFLOAT3 pos, XMFLOAT3 dir, float fov, float aspectRatio)
	: mFieldofView(fov), mAspectRatio(aspectRatio)
{
	HRESULT result;
	auto device = Hardware::GetDevice();

	XMFLOAT4 posflt4 = XMFLOAT4(pos.x, pos.y, pos.z, 1.0f);
	XMFLOAT4 dirflt4 = XMFLOAT4(dir.x, dir.y, dir.z, 1.0);

	XMVECTOR position = XMLoadFloat4(&posflt4);
	XMVECTOR direction = XMVector4Normalize(XMLoadFloat4(&dirflt4));

	
	XMStoreFloat4x4(&mRaw.mView, XMMatrixTranspose(XMMatrixLookToLH(position, direction, XMVectorSet(0, 1, 0, 0))));
	XMStoreFloat4x4(&mRaw.mProjection, XMMatrixTranspose( XMMatrixPerspectiveFovLH(fov, aspectRatio, 0.01, 1000.0)));

	mBuffer = new ConstantBuffer<CameraBuffer>(&mRaw);
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Release()
{
	delete mBuffer;
}

void Camera::Update(float delta)
{
	static XMVECTOR deter;
	static auto context = Hardware::GetContext();
	XMMATRIX inverse = XMMatrixInverse(&deter, XMLoadFloat4x4(&mRaw.mView));

	mRaw.mPosition = XMFLOAT4(inverse.r[3].m128_f32[0], inverse.r[3].m128_f32[1], inverse.r[3].m128_f32[2], 1.0f);
	mBuffer->Write();
}

void Camera::Render(float delta)
{
}
