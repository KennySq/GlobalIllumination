#include"pch.h"
#include"Geometry.h"

StaticVertex::StaticVertex(XMFLOAT3 position, XMFLOAT3 normal, XMFLOAT2 texcoord)
	: mPosition(position.x, position.y, position.z, 1.0f), mNormal(normal.x, normal.y, normal.z), mTexcoord(texcoord.x, texcoord.y)
{
}

StaticVertex::StaticVertex(float px, float py, float pz, float nx, float ny, float nz, float u, float v)
	: mPosition(px, py, pz, 1.0), mNormal(nx, ny,nz), mTexcoord(u,v)
{
}

bool StaticVertex::operator==(const StaticVertex& rhs) const
{
	return ((mPosition.x == rhs.mPosition.x && mPosition.y == rhs.mPosition.y && mPosition.z == rhs.mPosition.z)
		&& (mNormal.x == rhs.mNormal.x && mNormal.y == rhs.mNormal.y && mNormal.z == rhs.mNormal.z))
		&& (mTexcoord.x == rhs.mTexcoord.x && mTexcoord.y == rhs.mTexcoord.y);
}

bool StaticVertex::operator<(const StaticVertex& rhs) const
{
	return (XMVector4Length(XMLoadFloat4(&mPosition)).m128_f32[0] < XMVector4Length(XMLoadFloat4(&rhs.mPosition)).m128_f32[0]);
}
