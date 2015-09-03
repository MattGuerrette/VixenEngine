
cbuffer externalData : register(b0)
{
    matrix world;
    matrix view;
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

   
    matrix worldViewProj = mul(mul(world, view), projection);

   
    output.position = mul(float4(input.position, 1.0f), worldViewProj);
    output.uv = input.uv;

    
    return output;
}