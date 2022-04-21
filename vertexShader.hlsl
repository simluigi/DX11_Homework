//===============================================
//
//  DX11_Initialization: vertexShader.hlsl
//  Author: Luigi Sim
//  Last modified: 2022.04.21
//
//===============================================

//struct Camera
//{
//	matrix world;
//	matrix view;
//	matrix projection;
//
//};

struct VSInput
{
	float3 position : POSITION;
	float2 uv		: TEXCOORD;
};

struct VSOutput
{
	float4 position	: SV_POSITION;
	float2 uv		: TEXCOORD;
};

VSOutput main(VSInput IN)
{
	VSOutput OUT;

	//matrix mvp = mul(projection, mul(world, view));
	//OUT.position = mul(mvp, float4(IN.position, 1.0f));

	OUT.position = float4(IN.position, 1.0f);
	OUT.uv		 = IN.uv;

	return OUT;
}