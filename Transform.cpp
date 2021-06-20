#include "pch.h"
#include "Transform.h"

void Transform::Translate(XMFLOAT4X4& transform, float x, float y, float z)
{
	transform._14+= x;
	transform._24 += y;
	transform._34 += z;
}

void Transform::Rotate(XMFLOAT4X4& transform, float pitch, float yaw, float roll)
{
	XMMATRIX mat =  XMMatrixTranspose(XMLoadFloat4x4(&transform));
	mat *= XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	XMStoreFloat4x4(&transform, XMMatrixTranspose(mat));
}

void Transform::SetScale(XMFLOAT4X4& transform, float x, float y, float z)
{
	transform._11 = x;
	transform._22 = y;
	transform._33 = z;
}

XMFLOAT4 Transform::GetViewPosition(XMFLOAT4X4& transform)
{
	static XMMATRIX inverse;
	static XMMATRIX origin;
	static XMVECTOR deter;
	static XMVECTOR position, rotation, scale;
	static XMFLOAT4 ret;

	origin = XMLoadFloat4x4(&transform);

	inverse = XMMatrixInverse(&deter, origin);

	XMMatrixDecompose(&scale, &rotation, &position, inverse);
	XMStoreFloat4(&ret, position);

	return ret;
}

void Transform::ViewRotate(XMFLOAT4X4& transform, float pitch, float yaw, float roll)
{
	DebugLog("NOT YET.");
}