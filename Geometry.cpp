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
