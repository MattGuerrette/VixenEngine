

cbuffer externalData : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
    float  time;
};

struct VertexShaderInput
{
    float3 position		: POSITION;     // XYZ position
    float2 uv		    : TEXCOORD;     // tex coord
    float3 normal       : NORMAL;       // normal
};

struct VertexToPixel
{

    float4 position		: SV_POSITION;
    float2 uv		    : TEXCOORD;
    float3 normal       : NORMAL;
	float  depth		: TEXCOORD1;
    float  time         : TEXCOORD2;
};


VertexToPixel main(VertexShaderInput input)
{
    VertexToPixel output;

    matrix worldViewProj = mul(mul(world, view), projection);

    matrix viewProj = mul(view, projection);
    float4 depthPos = mul(float4(input.position, 1.0f), viewProj);
    output.position = mul(float4(input.position, 1.0f), worldViewProj);
    output.normal = mul(input.normal, (float3x3)world);
    output.uv = input.uv;
	output.depth = depthPos.z / depthPos.w;
    
    return output;
}