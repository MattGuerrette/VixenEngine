struct PointLight
{
	float3	ambientColor;
	float3	position;
	float	radius;
};

struct DirectionLight
{
	float3 ambientColor;
	float3 direction;
} dirLights[30];

cbuffer externalData : register(b0)
{
    float time;
};

Texture2D    txDiffuse : register(t0);
SamplerState samLinear : register(s0);


struct VertexToPixel
{

	float4 position		: SV_POSITION;
	float2 uv		    : TEXCOORD;
	float3 normal       : NORMAL;
	float  depth		: TEXCOORD1;
	float  time			: TEXCOORD2;
};

float4 main(VertexToPixel input) : SV_TARGET
{
    input.normal = normalize(input.normal);

    float4 ambientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);
    float4 diffuse = txDiffuse.Sample(samLinear, input.uv);
    float3 lightDir = float3(0.0f, 1.0f, 0.0f);
    float4 lightDiffuse = float4(0.6f, 0.6f, 0.6f, 1.0f);
    float3 color;
   
    color = diffuse * ambientLight;
	float diffuseValue = dot(lightDir, input.normal);
	//diffuseValue = round((diffuseValue+ .5) * 2.0) / 3;
    color += saturate(diffuseValue * lightDiffuse * diffuse);

	color *= (1 - input.depth*input.depth*.0001);
	//return (1-input.depth*input.depth*.0001);
	//return float4((1 + input.normal)*.5, 1.0);
	return float4(color, diffuse.a);
}