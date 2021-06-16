#pragma once
#include"Asset.h"
#include"Compiler.h"

namespace Assets
{
	class Shader : public Asset
	{
	public:
		
	private:
		ComPtr<ID3D11VertexShader> mVertex;
		ComPtr<ID3D11GeometryShader> mGeometry;
		ComPtr<ID3D11DomainShader> mDomain;
		ComPtr<ID3D11HullShader> mHull;
		ComPtr<ID3D11PixelShader> mPixel;
		ComPtr<ID3D11ComputeShader> mCompute;



		virtual bool Open() override;
		virtual void Close() override;

	};
}