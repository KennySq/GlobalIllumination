#pragma once

enum class PASS_TYPE
{
	eVertex = 1,
	eGeometry = 2,
	eDomain = 4,
	eHull = 8,
	ePixel = 16,
	eCompute = 32,
};

class Compiler
{
public:
	static bool compile(const char* path, const char* entry, const char* model, unsigned int passType);

};

