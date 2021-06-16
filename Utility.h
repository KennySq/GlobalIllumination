#pragma once
#include<limits>
#include<type_traits>
using namespace std;

static void DebugLog(const char* str)
{
#ifdef _DEBUG || DEBUG
	cout << str << endl;
#endif
}

static void DebugLog(char ch)
{
#ifdef _DEBUG || DEBUG
	cout << ch << endl;
#endif
}

static void DebugLog(int num)
{
#ifdef _DEBUG || DEBUG
	cout << num << endl;
#endif
}

static void DebugLog(unsigned int num)
{
#ifdef _DEBUG || DEBUG
	cout << num << endl;
#endif
}

static void DebugLog(long num)
{
#ifdef _DEBUG || DEBUG
	cout << num << endl;
#endif
}


static void DebugLog(float num)
{
#ifdef _DEBUG || DEBUG
	cout << num << endl;
#endif
}

static void DebugLog(double num)
{
#ifdef _DEBUG || DEBUG
	cout << num << endl;
#endif
}