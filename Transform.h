#pragma once
#include"IRoutine.h"

struct InstanceBuffer;
class Transform : public IRoutine
{
public:

	Transform();
	Transform(InstanceBuffer buffer);
	Transform(const Transform& rhs);
	~Transform();

	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void SetScale(float x, float y, float z);

	ID3D11Buffer* GetBuffer() const { return mBuffer.Get(); }
	ID3D11ShaderResourceView* GetView() const { return mView.Get(); }
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float delta) override;
	virtual void Render(float delta) override;

private:

	bool generate();

	ComPtr<ID3D11Buffer> mBuffer;
	ComPtr<ID3D11ShaderResourceView> mView;

	XMFLOAT4X4 mTransform;

};