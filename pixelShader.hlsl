//===============================================
//
//  DX11_Initialization: pixelShader.hlsl
//  Author: Luigi Sim
//  Last modified: 2022.04.21
//
//===============================================

Texture2D texture01 :register(t0);
SamplerState samplerState01 : register(s0);

struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

float4 main(PixelShaderInput IN) : SV_Target
{
	return texture01.Sample(samplerState01, IN.texCoord);
}
