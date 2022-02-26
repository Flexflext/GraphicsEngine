//Matrix Buffer to get 
cbuffer MatrixBuffer
{
	float4x4 worldViewProjectionMatrix;
	float4x4 worldMatrix;
};

//Input to the Vertex Shader
struct VertexInput
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

//Output from the VertexShader
struct VertexOutput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

VertexOutput main(VertexInput INPUT)
{
	VertexOutput OUTPUT;
	
    //Set VertexPosition in WorldSpace
	OUTPUT.position = mul(float4(INPUT.position, 1.0f), worldViewProjectionMatrix);
    //World Normal
	OUTPUT.normal = normalize(mul(INPUT.normal, (float3x3) worldMatrix));
    //Set UV
	OUTPUT.uv = INPUT.uv;
	
	return OUTPUT;
}