cbuffer CAMERA : register(b0)
{
	float4x4 gView;
	float4x4 gProjection;
	
	float4 gViewPosition;
	float4 gViewDirection;
}

cbuffer INSTANCE : register(b1)
{
	float4x4 gWorld;
}