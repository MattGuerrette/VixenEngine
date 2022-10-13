struct PointLight
{
	float3	ambientColor;
	float3	position;
	float	radius;
};

cbuffer externalData : register(b0)
{
	matrix		view;
	matrix		projection;
	float4x4	transforms[1000];
	float		distance;
	PointLight	pLights[4];
	int			numPLights;
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
	float  depth		: TEXCOORD1;
};

VertexToPixel main(VertexShaderInput input, uint instanceID : SV_InstanceID)
{

	VertexToPixel output;

	matrix world = transforms[instanceID];

	output.position = mul(float4(input.position, 1.0f), world);

	float depth = output.position.z / output.position.w;

	float t = distance + depth;

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
	
	/*matrix curve = {
		cos((t + output.depth) * .01), 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, cos((t + output.depth) * .01), 0.0,
		0.0, 0.0, 0.0, 1.0 };*/

	//depthDistortion = mul(depthDistortion, curve);

	/*matrix depthDistortion = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0 };*/

	output.position = mul(output.position, depthDistortion);

	output.position = mul(mul(output.position, view), projection);
	

	output.normal = mul(input.normal, (float3x3)mul(world, depthDistortion));
	output.tangent = mul(input.tangent, (float3x3)mul(world, depthDistortion));
	output.uv = input.uv;
	output.depth = depth;

	return output;
}