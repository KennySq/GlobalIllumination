#include "pch.h"
#include "MemoryBank.h"

MemoryBank* MemoryBank::mInstance = nullptr;

const string& MemoryBank::Find(const char* value)
{
    auto inst = MemoryBank::GetInstance();

    long long key = inst->make_hash(value);

    if (inst->mStringMap.find(key) != inst->mStringMap.cend())
    {
        return inst->mStringMap[key];
    }
    
    std::pair<long long, string> stringPair = std::pair<long long, string>(key, string(value));

    inst->mStringMap.insert(stringPair);

    return inst->mStringMap[key];
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