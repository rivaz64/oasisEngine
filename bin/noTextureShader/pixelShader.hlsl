
Texture2D txDiffuse : register( t0 );

SamplerState samLinear : register( s0 );

struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float2 Tex : TEXCOORD0;
};

float4 main( PS_INPUT input) : SV_Target
{
  return  float4(1.0f,1.0f,0.0f,1.0f);
}