#pragma once

using namespace std;

// MemoryBank has been made as singleton pattern
// Since Hardware does not resource allocate or release, MemoryBank is the only class that allocate resources dynamically except for d3d interaces.
class MemoryBank
{
public:

	static const string& Find(const char* value);

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

