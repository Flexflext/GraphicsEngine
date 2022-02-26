//Matrix Buffer 
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
    float2 uv : TEXCOORD;
};

//Output to Pixel Shader
struct VertexOutput
{
    float4 position : SV_POSITION;
    float3 uv : TEXCOORD;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
    
    //Calculate World position                     ->has to be 0 to always be in the Backof Everthing
    OUTPUT.position = mul(float4(INPUT.position, 0.0f), worldViewProjectionMatrix);
    
    //Set UV to World Position
    OUTPUT.uv = INPUT.position;
    
    return OUTPUT;
}