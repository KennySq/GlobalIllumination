#pragma once
#include"IRoutine.h"
#include"Transform.h"
#include"Asset.h"
#include"Shader.h"
#include"ResourceManager.h"

using namespace Resources;

struct InstanceBuffer
{
	InstanceBuffer()
	{
		XMStoreFloat4x4(&mWorld, XMMatrixIdentity());
	}

	XMFLOAT4X4 mWorld;
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

	ID3D11Buffer* GetBuffer() const { return mInstanceBuffer->GetBuffer(); }
	ID3D11ShaderResourceView* GetResourceView() const { return mInstanceBuffer->GetView(); }

	Shader* GetShader() const { return mShader; }
	Assets::AssetModel* GetModel() const { return mModel; }

	XMFLOAT4X4& GetRawTransform() { return mRaw.mWorld; }
	const char* GetName() const { return mName.c_str(); }
private:

	static long long gInstanceID;

	Shader* mShader;
	Assets::AssetModel* mModel;

	InstanceBuffer mRaw;
	
	long long mInstanceID;
	const string& mName;

	RWStructuredBuffer<InstanceBuffer>* mInstanceBuffer;
	

};

