#pragma once

using namespace std;

#include"Asset.h"
#include"Instance.h"

// MemoryBank has been made as singleton pattern
// Since Hardware does not resource allocate or release, MemoryBank is the only class that allocate resources dynamically except for d3d interaces.
class MemoryBank
{
public:

	static const string& Find(const char* value);
	
	static Assets::AssetModel* FindModel(const char* name);
	static void AddModel(Assets::AssetModel* model);

	static Instance* FindInstance(long long iid);
	static void AddInstance(Instance* inst);

	static void AddShader(Shader* shader);
	static Shader* FindShader(const char* name);

	MemoryBank() {}
	~MemoryBank() {}

	static MemoryBank* const GetInstance() { 
	
		if (mInstance == nullptr)
		{
			mInstance = new MemoryBank();
		}
		
		return mInstance;
	}
	
private:
	static MemoryBank* mInstance;

	unordered_map<long long, string> mStrings;
	unordered_map<long long, Assets::AssetModel*> mModels;
	unordered_map<long long, Shader*> mShaders;

	vector<Instance*> mInstances;

	long long make_hash(string value);
};

