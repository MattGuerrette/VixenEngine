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

Texture2D		txDiffuse : register(t0);
Texture2D		txNormal : register(t1);
SamplerState	samLinear : register(s0);


struct VertexToPixel
{

	float4 position		: SV_POSITION;
	float2 uv		    : TEXCOORD;
	float3 normal       : NORMAL;
	float3 tangent		: TANGENT;
	float  depth		: TEXCOORD1;
};

float4 main(VertexToPixel input) : SV_TARGET
{
	// Sample from normal map
	float3 normalFromMap = txNormal.Sample(samLinear, input.uv).rgb * 2 - 1;

	// Calculate the TBN matrix to go from tangent to world space
	float3 N = input.normal;
	float3 T = normalize(input.tangent - N * dot(input.tangent, N));
	float3 B = cross(T, N);
	float3x3 TBN = float3x3(T, B, N);

	input.normal = normalize(mul(normalFromMap, TBN));


    float4 ambientLight = float4(0.2f, 0.2f, 0.2f, 1.0f);
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