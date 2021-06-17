cbuffer CAMERA : register(b0)
{
	float4x4 gView;
	float4x4 gProjection;
	
	float4 gViewPosition;
	float4 gViewDirection;
}

struct InstanceBuffer
{
    float4x4 mWorld;
};