#include "pch.h"
#include "Shader.h"

Shader::Shader(const char* path, unsigned int passType)
	:	Asset(path)
{
	Compiler::Compile(path, passType, this);

	MemoryBank::AddShader(this);
}

Shader::~Shader()
{
	mVertex.ReleaseAndGetAddressOf();
	mGeometry.ReleaseAndGetAddressOf();
	mDomain.ReleaseAndGetAddressOf();
	mHull.ReleaseAndGetAddressOf();
	mPixel.ReleaseAndGetAddressOf();
	mCompute.ReleaseAndGetAddressOf();
}

bool Shader::Open()
{
	return false;
}

void Shader::Close()
{
}
