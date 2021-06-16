#pragma once
#include"Asset.h"

using namespace Assets;

class Shader : public Asset
{
public:
	// for more information about 'passType' check out PASS_TYPE enum class in Compiler.h
	Shader(const char* path, unsigned int passType);
	~Shader();


	ID3D11VertexShader* GetVertex() const { return mVertex.Get(); }
	ID3D11GeometryShader* GetGeometry() const { return mGeometry.Get(); }
	ID3D11DomainShader* GetDomain() const { return mDomain.Get(); }
	ID3D11HullShader* GetHull() const { return mHull.Get(); }
	ID3D11PixelShader* GetPixel() const { return mPixel.Get(); }
	ID3D11ComputeShader* GetCompute() const { return mCompute.Get(); }
	ID3D11InputLayout* GetLayout() const { return mLayout.Get(); }

private:
	Shader(const Shader& rhs) = delete;

	friend class Compiler;

	ComPtr<ID3D11VertexShader> mVertex;
	ComPtr<ID3D11GeometryShader> mGeometry;
	ComPtr<ID3D11DomainShader> mDomain;
	ComPtr<ID3D11HullShader> mHull;
	ComPtr<ID3D11PixelShader> mPixel;
	ComPtr<ID3D11ComputeShader> mCompute;
	ComPtr<ID3D11InputLayout> mLayout;



	// Asset을(를) 통해 상속됨
	virtual bool Open() override;
	virtual void Close() override;

};