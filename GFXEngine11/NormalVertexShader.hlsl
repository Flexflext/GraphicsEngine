//Get the Buffer Matrix Data
cbuffer MatrixBuffer : register(b0)
{
    float4x4 worldViewProjectionMatrix;
    float4x4 worldMatrix;
    float3 worldCamPosition;
};


//Get Input from CPU
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
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
};

VertexOutput main(VertexInput INPUT)
{
    VertexOutput OUTPUT;
	
    //Set Output
    //World Position
    OUTPUT.position = mul(float4(INPUT.position, 1.0f), worldViewProjectionMatrix);
    //World Normal
    OUTPUT.normal = normalize(mul(INPUT.normal, (float3x3) worldMatrix));
    //World Tangent
    OUTPUT.tangent = normalize(mul(INPUT.tangent, (float3x3) worldMatrix));
    //World Bitangent
    OUTPUT.bitangent = normalize(mul(INPUT.bitangent, (float3x3) worldMatrix));
    OUTPUT.uv = INPUT.uv;
    //View Direction from Camera to Pos
    OUTPUT.viewDirection = worldCamPosition - OUTPUT.position.xyz;
	
    return OUTPUT;
}