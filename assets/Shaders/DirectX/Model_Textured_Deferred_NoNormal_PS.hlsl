cbuffer externalData : register(b0)
{
    float time;
};

Texture2D		txDiffuse : register(t0);
SamplerState	samLinear : register(s0);


struct VertexToPixel
{
    float4 position		: SV_POSITION;
    float2 uv		    : TEXCOORD;
    float3 normal       : NORMAL;
    float3 tangent		: TANGENT;
    float  worldz : TEXCOORD1;
    float  depth : TEXCOORD2;
};

struct PixelOutput
{
    float4 diffuse : SV_Target0;
    float4 normal :  SV_Target1;
    float depth : SV_Target2;
};

PixelOutput main(VertexToPixel input)
{

    PixelOutput output;

    output.normal = float4(input.normal * .5 + .5, input.worldz * .01);

    float4 diffuse = txDiffuse.Sample(samLinear, input.uv);

    output.diffuse = diffuse;

    output.depth = input.depth;

    return output;
}