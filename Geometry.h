#pragma once
using namespace DirectX;

struct StaticVertex
{
	XMFLOAT4 mPosition;
	XMFLOAT3 mNormal;
	XMFLOAT2 mTexcoord;

	StaticVertex(XMFLOAT3 position, XMFLOAT3 normal, XMFLOAT2 texcoord);
	StaticVertex(float px, float py, float pz, float nx, float ny, float nz, float u, float v);

	bool operator==(const StaticVertex& rhs) const;
	bool operator<(const StaticVertex& rhs) const;
};