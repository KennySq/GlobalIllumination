#pragma once

using namespace std;

class MemoryBank
{
public:

	const string& Find(const char* value);

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

	unordered_map<long long, string> mStringMap;
	long long make_hash(string value);
};

