struct PixelShaderInput
{
    float4 position : SV_POSITION;
    float3 uv : TEXCOORD;
};

TextureCube cubeTex;
SamplerState cubeTexSampler;

float4 main(PixelShaderInput INPUT) : SV_TARGET
{
    return cubeTex.Sample(cubeTexSampler, INPUT.uv);
}