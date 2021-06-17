#pragma once
#include"IRoutine.h"
#include"Transform.h"
#include"Asset.h"
#include"Shader.h"

struct InstanceBuffer
{
	XMFLOAT4X4 mWorld;

	InstanceBuffer()
	{
		XMStoreFloat4x4(&mWorld, XMMatrixIdentity());
	}
};

class Instance : public IRoutine
{
public:
	Instance(const char* name);
	~Instance();

	Instance(const Instance& rhs) = delete;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float delta) override;
	virtual void Render(float delta) override;

	bool BindModel(const char* model);
	bool BindShader(const char* name);

	ID3D11Buffer* GetBuffer() const { return mTransform->GetBuffer(); }
	ID3D11ShaderResourceView* GetResourceView() const { return mTransform->GetView(); }

	Shader* GetShader() const { return mShader; }
	Assets::AssetModel* GetModel() const { return mModel; }

private:

	static long long gInstanceID;

	Shader* mShader;
	Assets::AssetModel* mModel;
	
	Transform* mTransform;
	InstanceBuffer mRaw;

	long long mInstanceID;
	const string& mName;
};

