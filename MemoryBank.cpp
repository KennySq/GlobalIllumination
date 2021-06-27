#include "pch.h"
#include "MemoryBank.h"

MemoryBank* MemoryBank::mInstance = nullptr;

const string& MemoryBank::Find(const char* value)
{
    static MemoryBank* inst = MemoryBank::GetInstance();

    long long key = inst->make_hash(value);

    if (inst->mStrings.find(key) != inst->mStrings.cend())
    {
        return inst->mStrings[key];
    }
    
    std::pair<long long, string> stringPair = std::pair<long long, string>(key, string(value));

    inst->mStrings.insert(stringPair);

    return inst->mStrings[key];
}

Assets::AssetModel* MemoryBank::FindModel(const char* name)
{
    static MemoryBank* inst = MemoryBank::GetInstance();

    long long key = inst->make_hash(name);

    if (inst->mModels.find(key) != inst->mModels.cend())
    {
        return inst->mModels[key];
    }

    return nullptr;
}

void MemoryBank::AddModel(Assets::AssetModel* model)
{
    static MemoryBank* memory = MemoryBank::GetInstance();

    if (model == nullptr)
    {
        DebugLog("failed to add a model, the pointer was invalid.");
        return;
    }

    const char* name = model->GetPath();
    long long key = memory->make_hash(name);

    std::pair<long long, Assets::AssetModel*> modelPair = std::pair<long long, Assets::AssetModel*>(key, model);

    memory->mModels.insert(modelPair);

    return;
}

Instance* MemoryBank::FindInstance(long long iid)
{
    static MemoryBank* memory = MemoryBank::GetInstance();
    return memory->mInstances[iid];
}

void MemoryBank::AddInstance(Instance* inst)
{
    static MemoryBank* memory = MemoryBank::GetInstance();

    if (inst == nullptr)
    {
        DebugLog("failed to add instance, invalid pointer.");
        return;
    }

    memory->mInstances.emplace_back(inst);
}

void MemoryBank::AddShader(Shader* shader)
{
    static MemoryBank* memory = MemoryBank::GetInstance();

    if (shader == nullptr)
    {
        DebugLog("failed to add a shader, invalid pointer.");
        return;
    }

    const char* name = shader->GetPath();
    long long key = memory->make_hash(name);

    std::pair<long long, Shader*> shaderPair = std::pair<long long, Shader*>(key, shader);

    memory->mShaders.insert(shaderPair);

}

Shader* MemoryBank::FindShader(const char* name)
{
    MemoryBank* memory = MemoryBank::GetInstance();
    return memory->mShaders[memory->make_hash(name)];
}

void MemoryBank::AddLight(DirectionalLight* light)
{
    static MemoryBank* memory = MemoryBank::GetInstance();

    if (light == nullptr)
    {
        DebugLog("failed to add directional light, invalid pointer.");
        return;
    }

    memory->mDirectionalLights.emplace_back(light);
}

DirectionalLight* MemoryBank::FindDirectionalLight(long long lightID)
{
    static MemoryBank* memory = MemoryBank::GetInstance();
    return memory->mDirectionalLights[lightID];
}

void MemoryBank::AddLight(PointLight* light)
{
    static MemoryBank* memory = MemoryBank::GetInstance();

    if (light == nullptr)
    {
        DebugLog("failed to add point light, invalid pointer.");
        return;
    }

    memory->mPointLights.emplace_back(light);
}

PointLight* MemoryBank::FindPointLight(long long lightID)
{
    static MemoryBank* memory = MemoryBank::GetInstance();
    return memory->mPointLights[lightID];
}

long long MemoryBank::make_hash(string value)
{
    const int p = 53;
    const int m = 1e9 + 9; // 10^9 + 9

    int hash_val = 0;
    int power = 1;

    for (int i = 0; i < value.length(); i++)
    {
        hash_val = (hash_val + (value[i] - 'a' + 1) * power) % m;
        power = (p * power) % m;
    }

    return hash_val;
}