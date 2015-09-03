

Texture2D    txDiffuse : register(t0);
SamplerState samLinear : register(s0);


struct VertexToPixel
{
    float4 position		: SV_POSITION;
    float2 uv		    : TEXCOORD;
};


float4 main(VertexToPixel input) : SV_TARGET
{
    return txDiffuse.Sample(samLinear, input.uv);
}