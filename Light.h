#pragma once
#include"IRoutine.h"

struct DirectionalLightBuffer
{
	XMFLOAT4X4 mTransform;
	XMFLOAT3 mDirection;
	float mIntensity;
};

struct PointLightBuffer
{
	XMFLOAT4X4 mTransform;
	XMFLOAT3 mColor;
	float mIntensity;
};

class DirectionalLight : IRoutine
{
public:
	DirectionalLight(XMVECTOR direction, float intensity);
	~DirectionalLight();

	virtual void Update(float delta) override;
	virtual void Render(float delta) override;

	XMFLOAT4X4& GetRawTransform() { return mRaw.mTransform; }

private:
	static long long mLightID;

	DirectionalLightBuffer mRaw;
	ComPtr<ID3D11Buffer> mBuffer;

	virtual void Init() override;
	virtual void Release() override;

};

class PointLight : IRoutine
{
public:

	

	PointLight(XMVECTOR position, XMVECTOR color, float intensity);
	~PointLight();

	virtual void Update(float delta) override;
	virtual void Render(float delta) override;

private:
	static long long mLightID;

	PointLightBuffer mRaw;
	ComPtr<ID3D11Buffer> mBuffer;

	virtual void Init() override;
	virtual void Release() override;
};