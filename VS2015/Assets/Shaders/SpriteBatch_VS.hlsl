cbuffer externalData : register(b0)
{
    matrix projection;
};

struct VertexShaderInput
{
    float3 position		: POSITION;     // XYZ position
    float2 uv		    : TEXCOORD;     // tex coord
};

struct VertexToPixel
{

    float4 position		: SV_POSITION;
    float2 uv		    : TEXCOORD;
};


VertexToPixel main(VertexShaderInput input)
{
    VertexToPixel output;

    output.position = mul(float4(input.position, 1.0f), projection);
    output.uv = input.uv;

    return output;
}