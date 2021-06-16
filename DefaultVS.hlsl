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

PixelInput DefaultVS(StaticVertex vertex)
{
	PixelInput output = (PixelInput)0;
	
	output.mPosition = mul(vertex.mPosition, gWorld);
	output.mNormal = mul(vertex.mNormal, (float3x3) gWorld);
	output.mTexcoord = vertex.mTexcoord;

	return output;
}

float4 DefaultPS(PixelInput input)
{
	return input.mNormal;
}