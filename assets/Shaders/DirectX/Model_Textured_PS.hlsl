

Texture2D    txDiffuse : register(t0);
SamplerState samLinear : register(s0);


struct VertexToPixel
{
    float4 position		: SV_POSITION;
    float2 uv		    : TEXCOORD;
    float3 normal       : NORMAL;
};


float4 main(VertexToPixel input) : SV_TARGET
{
    input.normal = normalize(input.normal);


    float4 ambientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);
    float4 diffuse = txDiffuse.Sample(samLinear, input.uv);
    float3 lightDir = float3(0.0f, 1.0f, 0.0f);
    float4 lightDiffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
    float3 color;
   

    color = diffuse * ambientLight;
	float diffuseValue = dot(lightDir, input.normal);
	diffuseValue = round((diffuseValue+ .5) * 2.0) / 3;
    color += saturate(diffuseValue * lightDiffuse * diffuse);
	color *= input.position.z;
    
	return float4(color, diffuse.a);
}