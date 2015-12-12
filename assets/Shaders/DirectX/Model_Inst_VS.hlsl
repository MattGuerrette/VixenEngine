struct InstanceData
{
    float4x4 world;
};


StructuredBuffer<InstanceData> InstanceBuffer;


cbuffer externalData : register(b1)
{
    matrix		view;
    matrix		projection;
    float		distance;
};

struct VertexShaderInput
{
    float3 position		: POSITION;     // XYZ position
    float2 uv		    : TEXCOORD;     // tex coord
    float3 normal       : NORMAL;       // normal
    float3 tangent		: TANGENT;

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

VertexToPixel main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{

    VertexToPixel output;

    matrix world = InstanceBuffer[instanceID].world;

    float4 position = mul(float4(input.position, 1.0f), world);
	
    float worldz = position.z;

	position = mul(mul(position, view), projection);


	output.position = position;
    output.normal = mul(input.normal, (float3x3)world);
    output.tangent = mul(input.tangent, (float3x3)world);
    output.uv = input.uv;
    output.worldz = worldz;
	output.depth = position.z / position.w;

    return output;
}