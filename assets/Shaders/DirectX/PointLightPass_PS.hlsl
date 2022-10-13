
struct PointLight
{
	float4 color;
	float  range;
	float  attenConstant;
	float  attenLinear;
	float  attenQuadratic;
};

cbuffer pixelData : register(b0)
{
	float width;
	float height;
	matrix invViewProj;
};

struct PS_INPUT
{
	float4 position   : SV_POSITION;
	float3 center     : TEXCOORD1;
	PointLight light : TEXCOORD2;
};


Texture2D txDiffuse : register(t0);
Texture2D txNormal : register(t1);
Texture2D txWorld : register(t2);

SamplerState samLinear : register(s0);

float4 main( PS_INPUT input ) : SV_TARGET
{
	float screenx = input.position.x / width;
	float screeny = input.position.y / height;
	float depth = txWorld.Sample(samLinear, float2(screenx, screeny));

	//convert from screen to world space
	float4 pos = float4(screenx * 2.0 - 1.0, 1.0 - screeny * 2.0, depth, 1.0);
	pos = mul(pos, invViewProj);
	pos = pos / pos.w;

	//normal
	float3 normal = txNormal.Sample(samLinear, float2(screenx, screeny));
	normal = normalize(normal * 2.0 - 1.0);

	//ndotl
	float3 lightDir = normalize(input.center.xyz - pos.xyz);
	float ndotl = dot(normal.xyz, lightDir.xyz);

	//attenuation
	float lightDist = length(input.center.xyz - pos.xyz) / input.light.range;
	float atten = min(1 / (lightDist * lightDist * input.light.attenQuadratic + lightDist * input.light.attenLinear + input.light.attenConstant), 1);

	//combine everything
	float3 finalLight = input.light.color * ndotl * atten;

	return float4(finalLight, 1.0);
}