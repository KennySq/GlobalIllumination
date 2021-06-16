#include"Constants.hlsli"

struct StaticVertex
{
	float4 mPosition : POSITION0;
	float3 mNormal : NORMAL0;
	float2 mTexcoord : TEXCOORD0;
};

struct PixelInput
{
	float4 mPosition : SV_Position;
	float4 mNormal : TEXCOORD0; // world normal
	float2 mTexcoord : TEXCOORD1;
};

PixelInput vert(StaticVertex vertex)
{
	PixelInput output = (PixelInput)0;
	
	output.mPosition = mul(vertex.mPosition, gWorld);
    output.mPosition = mul(output.mPosition, gView);
    output.mPosition = mul(output.mPosition, gProjection);
	
	output.mNormal = float4(mul(vertex.mNormal, (float3x3) gWorld), 1.0f);
	output.mTexcoord = vertex.mTexcoord;

	return output;
}

float4 pix(PixelInput input) : SV_Target0
{
    return normalize(input.mPosition);
}