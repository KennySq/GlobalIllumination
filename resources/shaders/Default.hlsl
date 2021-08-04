#include"Constants.hlsli"

StructuredBuffer<InstanceBuffer> gInstance : register(t0);
StructuredBuffer<DirectionalLightBuffer> gDirectionalLights : register(t1);

static float4 gDirectionalLight1 = float4(50, 50, 50, 1.0);

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
	
	output.mPosition = mul(vertex.mPosition, gInstance[0].mWorld);
    output.mPosition = mul(output.mPosition, gView);
    output.mPosition = mul(output.mPosition, gProjection);
	
    output.mNormal = float4(mul(vertex.mNormal, (float3x3) gInstance[0].mWorld), 1.0f);
	output.mTexcoord = vertex.mTexcoord;

	return output;
}

float4 pix(PixelInput input) : SV_Target0
{
    float4 normal = normalize(input.mNormal);
	
    float4 lightDir = normalize(input.mPosition - gDirectionalLight1);
    return saturate(dot(normal, lightDir));

}