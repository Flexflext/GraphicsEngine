cbuffer MatrixBuffer : register(b0)
{
    float4x4 worldViewProjectionMatrix;
    float4x4 worldMatrix;
    float3 worldCamPosition;
};

struct VertexInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float3 uv : TEXCOORD;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
    
    OUTPUT.position = mul(float4(INPUT.position, 0.0f), worldViewProjectionMatrix);
    
    OUTPUT.uv = INPUT.position;
    
    return OUTPUT;
}