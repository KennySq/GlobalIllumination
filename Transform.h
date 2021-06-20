#pragma once

class Transform
{
public:

	static void Translate(XMFLOAT4X4& transform, float x, float y, float z);
	static void Rotate(XMFLOAT4X4& transform, float x, float y, float z);
	static void SetScale(XMFLOAT4X4& transform, float x, float y, float z);

	static XMFLOAT4 GetViewPosition(XMFLOAT4X4& transform);
	static void ViewTranslate(XMFLOAT4X4& transform, float x, float y, float z);
	static void ViewRotate(XMFLOAT4X4& transform, float pitch, float yaw, float roll);
};