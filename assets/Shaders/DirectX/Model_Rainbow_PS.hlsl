
cbuffer externalData : register(b0)
{
	float time;
};


struct VertexToPixel
{

	float4 position		: SV_POSITION;
	float2 uv		    : TEXCOORD;
	float3 normal       : NORMAL;
	float  depth : TEXCOORD1;
};


float4 main(VertexToPixel input) : SV_TARGET
{
	input.normal = normalize(input.normal);


	float4 ambientLight = float4(0.5f, 0.5f, 0.5f, 1.0f);
	float4 diffuse = float4(sin(input.depth * .5)*.5 + .5, cos(input.depth * .5)*.5 + .5, -sin(input.depth *.5)*.5 + .5, 1.0f);
	float3 lightDir = float3(0.0f, 1.0f, 0.0f);
	float4 lightDiffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
	float3 color;


	color = diffuse * ambientLight;
	float diffuseValue = dot(lightDir, input.normal);
	color += saturate(diffuseValue * lightDiffuse * diffuse);

	color *= (1 - input.depth*input.depth*.0001);


    return float4(diffuse.rgb, diffuse.a);
}