
cbuffer Transform0 : register( b0 )
{
  matrix world;
};

cbuffer transforms1 : register( b1 )
{
  matrix view;
};

cbuffer transforms2 : register( b2 )
{
  matrix projection;
};

cbuffer Bones : register( b3 )
{
  matrix boneMatrix[1024];
};

struct VS_INPUT
{
  int4 Ids : TEXCOORD2;
  float4 Weights  : TEXCOORD3;
  float4 Postion : POSITION;
  float2 Tex : TEXCOORD0;
  float2 None : TEXCOORD1;
  
  
};

struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float2 Tex : TEXCOORD0;
};

PS_INPUT main(VS_INPUT input)
{
  PS_INPUT output = (PS_INPUT)0;
  float4 pos = float4(input.Postion.xyz, 1.0f);
  pos = mul( pos, world );
  pos = mul( pos, view );
  pos = mul( pos, projection );
  output.Pos = pos;
  output.Tex = input.Tex;
  return output;
}