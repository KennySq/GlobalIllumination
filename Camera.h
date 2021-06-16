#pragma once
#include"IRoutine.h"
#include"ResourceManager.h"
using namespace DirectX;
using namespace Resources;

struct CameraBuffer
{
	XMFLOAT4X4 mView;
	XMFLOAT4X4 mProjection;

	XMFLOAT4 mPosition;
	XMFLOAT4 mDirection;
};

class Camera : public IRoutine
{
public:

	Camera(XMFLOAT3 pos, XMFLOAT3 dir, float fov, float aspectRatio);
	~Camera();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float delta) override;
	virtual void Render(float delta) override;

	ID3D11Buffer* GetBuffer() const { return mBuffer.Get(); }

private:
	ComPtr<ID3D11Buffer> mBuffer;
	CameraBuffer mRaw;

	float mFieldofView;
	float mAspectRatio;

};