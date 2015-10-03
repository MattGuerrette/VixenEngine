

cbuffer externalData : register(b0)
{
    matrix   view;
    matrix   projection;
    float4x4 transforms[1000];
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


VertexToPixel main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{
    VertexToPixel output;

    matrix world = transforms[instanceID];
    matrix worldViewProj = mul(mul(world, view), projection);
    matrix viewProj = mul(view, projection);

    output.position = mul(float4(input.position, 1.0f), worldViewProj);
    output.normal = mul(input.normal, (float3x3)world);
    output.uv = input.uv;
	
    
    return output;
}