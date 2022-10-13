


struct InstanceData
{
	float4x4 world;
};


StructuredBuffer<InstanceData> InstanceBuffer;

struct PointLight
{
	float4 color;
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
	float t = distance + pos.z;

	float curvex = (sin(t*.03) + cos(t*.05) - sin(t*.07)) * 2.0;
	float curvey = (cos(t*.03) + sin(t*.07) - cos(t*.13)) * 0.5;
	float ddx = (.03*cos(distance*.03) - .05*sin(distance*.05) - .07*cos(distance*.07)) * 2.0;
	float ddz = 1;
	float rot = -atan2(ddx, ddz);

	matrix depthDistortion = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		curvex, curvey, 0.0, 1.0 };

	matrix depthDistortion2 = {
		cos(-curvex*.05), -sin(-curvex*.05), 0.0, 0.0,
		sin(-curvex*.05), cos(-curvex*.05), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0 };

	matrix depthDistortion3 = {
		cos(rot), 0.0, -sin(rot), 0.0,
		0.0, 1.0, 0.0, 0.0,
		sin(rot), 0.0, cos(rot), 0.0,
		0.0, 0.0, 0.0, 1.0 };

	depthDistortion = mul(mul(depthDistortion, depthDistortion2), depthDistortion3);
	

	pos = mul(pos, depthDistortion);
	output.center = pos.xyz;

	pos = float4(input.position * -light.range * 1.1, 0.0) + pos;
	output.position = mul(pos, mul(view, projection));
	output.light = light;

	return output;
}