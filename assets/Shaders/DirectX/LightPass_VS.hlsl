


struct InstanceData
{
	float4x4 world;
};


StructuredBuffer<InstanceData> InstanceBuffer;

struct PointLight
{
	float4 color;
	float  intensity;
	float3 position;
	float  range;
	float  attenConstant;
	float  attenLinear;
	float  attenQuadratic;
};

StructuredBuffer<PointLight> LightBuffer;


cbuffer externalData : register(b2)
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


struct PS_INPUT
{
	float4 position   : SV_POSITION;
	float3 center     : TEXCOORD1;
	PointLight light : TEXCOORD2;
};

PS_INPUT main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{

	PS_INPUT output;

	matrix world = InstanceBuffer[instanceID].world;
	PointLight light = LightBuffer[instanceID];

	float4 pos = mul(float4(0, 0, 0, 1), world);

	//transform data requires distance variable that is being set from game
	float depth = pos.z;// / pos.w;

	output.center = pos.xyz;

	pos = float4(input.position * -light.range * 2.8, 1.0f) + pos;
	output.position = mul(pos, mul(view, projection));
	output.light = light;

	return output;
}