#pragma once
#include"Shader.h"

enum PASS_TYPE
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
	static bool Compile(const char* path, unsigned int passType, Shader* shader);
	static bool Reflect(ID3DBlob* vertexBlob, Shader* shader);
};