//Matrices
cbuffer MatrixBuffer : register(b0)
{
    float4x4 worldViewProjectionMatrix;
    float4x4 worldMatrix;
    float3 worldCamPosition;
};

//Input from CPU
struct VertexInput
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
};

//Output to Pixel Shader
struct VertexOutput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 viewDirection : TEXCOORD1;
    float2 uv : TEXCOORD;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
	
    //Calc World Position
    OUTPUT.position = mul(float4(INPUT.position, 1.0f), worldViewProjectionMatrix);
    //Calc World Normal
    OUTPUT.normal = normalize(mul(INPUT.normal, (float3x3) worldMatrix));
    //Set UV
    OUTPUT.uv = INPUT.uv;
    //Calc View Direction
    OUTPUT.viewDirection = worldCamPosition - mul(worldMatrix, float4(INPUT.position, 1.0)).xyz;
	
    return OUTPUT;
}