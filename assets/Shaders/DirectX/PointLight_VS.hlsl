

struct PointLight
{
	float4 color;
	float3 position;
	float  range;
	float  attenConstant;
	float  attenLinear;
	float  attenQuadratic;
};

StructuredBuffer<PointLight> LightBuffer;

float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}