
cbuffer externalData : register(b0)
{
	float time;
};


struct VertexToPixel
{
    float4 position		: SV_POSITION;
    float2 uv		    : TEXCOORD;
    float3 normal       : NORMAL;
    float3 tangent		: TANGENT;
    float  worldz       : TEXCOORD1;
	float  depth		: TEXCOORD2;
};

struct PixelOutput
{
	float4 diffuse : SV_Target0;
	float4 normal :  SV_Target1;
	float depth : SV_Target2;
};

PixelOutput main(VertexToPixel input) : SV_TARGET
{
	PixelOutput output;

	input.normal = normalize(input.normal);

	output.normal = float4(input.normal * .5 + .5, input.worldz * .01);

	output.diffuse = float4(sin(input.worldz * .5)*.5 + .5, cos(input.worldz * .5)*.5 + .5, -sin(input.worldz *.5)*.5 + .5, 1.0f);

	output.depth = input.depth;

	return output;
}