#include "pch.h"
#include "Instance.h"

long long Instance::gInstanceID = 0;

Instance::Instance(const char* name)
	: mName(MemoryBank::Find(name)), mInstanceID(gInstanceID), mModel(nullptr), mShader(nullptr), mTransform(new Transform(mRaw))
{
	HRESULT result;
	auto device = Hardware::GetDevice();

	D3D11_BUFFER_DESC bufferDesc{};
	D3D11_SUBRESOURCE_DATA subData{};

	MemoryBank::AddInstance(this);
	gInstanceID++;

}

Instance::~Instance()
{
	Release();

}

void Instance::Init()
{
}

void Instance::Release()
{
}

void Instance::Update(float delta)
{
}

void Instance::Render(float delta)
{
}

bool Instance::BindModel(const char* model)
{
	mModel = MemoryBank::FindModel(model);

	if (mModel == nullptr)
	{
		DebugLog("failed to bind a model, no such model exist.");

		return false;
	}

	return true;
}

bool Instance::BindShader(const char* name)
{
	mShader = MemoryBank::FindShader(name);

	if (mShader == nullptr)
	{
		DebugLog("failed to bind a shader, no such shader exist.");

		return false;
	}

	return true;
}
