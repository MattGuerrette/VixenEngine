
struct PixelInput
{
	float4 position		: SV_POSITION;
	float2 uv		    : TEXCOORD;
};

Texture2D		txDiffuse : register(t0);
Texture2D		txNormal  : register(t1);
Texture2D		txWorld	  : register(t2);
Texture2D		txLight	  : register(t3);
SamplerState	samLinear : register(s0);


float4 main( PixelInput input ) : SV_TARGET
{
	float4 diffuse = txDiffuse.Sample(samLinear, input.uv);
	float4 normalSampled = txNormal.Sample(samLinear, input.uv);
	float4 worldPos = txWorld.Sample(samLinear, input.uv);

	float3 normal = normalSampled.xyz;
	float  depth = normalSampled.w;

	float4 ambientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);
	


	float4 lightDiffuse = txLight.Sample(samLinear, input.uv);

	float4 color = saturate(diffuse * (lightDiffuse * (1 - depth * .5) + ambientLight * (1 - depth * 2)));

	//return (1-input.depth*input.depth*.0001);
	//return float4((1 + input.normal)*.5, 1.0);
	//return float4(light.color.rgb, 1.0);
	return float4(color.rgb, 1.0); //float4(d, diffuse.a);
	
}

