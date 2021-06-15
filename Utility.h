#pragma once
using namespace std;
static void DebugLog(const char* str)
{
#ifdef _DEBUG || DEBUG
	cout << str << endl;
#endif
}
