//Input from Vertex Shader
struct PixelShaderInput
{
    float4 position : SV_POSITION;
    float3 uv : TEXCOORD;
};

//Skybox Cubemap
TextureCube cubeTex;
SamplerState cubeTexSampler;

float4 main(PixelShaderInput INPUT) : SV_TARGET
{
    //Sample UV at World Position
    return cubeTex.Sample(cubeTexSampler, INPUT.uv);
}