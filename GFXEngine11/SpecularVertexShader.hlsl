
cbuffer MatrixBuffer : register(b0)
{
    float4x4 worldViewProjectionMatrix;
    float4x4 worldMatrix;
    float3 worldCamPosition;
};



struct VertexInput
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float3 viewDirection : TEXCOORD1;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
	
    OUTPUT.position = mul(float4(INPUT.position, 1.0f), worldViewProjectionMatrix);
    OUTPUT.normal = normalize(mul(INPUT.normal, (float3x3) worldMatrix));
    OUTPUT.uv = INPUT.uv;
    OUTPUT.viewDirection = worldCamPosition - mul(worldMatrix, float4(INPUT.position, 1.0)).xyz;
	
    return OUTPUT;
}