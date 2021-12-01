
cbuffer Transform0 : register( b0 )
{
  matrix world;
};

cbuffer transforms1 : register( b1 )
{
  matrix view;
};

struct VS_INPUT
{
  float3 Pos : POSITION;
  float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float2 Tex : TEXCOORD0;
};

PS_INPUT main(VS_INPUT input)
{
  PS_INPUT output = (PS_INPUT)0;
  float4 pos = float4(input.Pos, 1.0f);
  pos = mul( pos, world );
  pos = mul( pos, view );
  output.Pos = pos;
  output.Tex = input.Tex;
  return output;
}