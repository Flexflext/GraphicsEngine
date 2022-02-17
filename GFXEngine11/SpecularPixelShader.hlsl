Texture2D MainTexture : register(t0);
sampler MainSampler;

cbuffer LightData : register(b0) // has to be aligned in 16 byte blocks
{
    float3 lightDirection;
    float lightIntensity;
    float4 lightDiffuseColor;
};

cbuffer ExtraData : register(b1) // has to be aligned in 16 byte blocks
{
    float4 specularColor;
    float glossy;
    float specularPower;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float3 viewDirection : TEXCOORD1;
};


float4 main(PixelInput INPUT) : SV_TARGET
{
    float4 textureColor = MainTexture.Sample(MainSampler, INPUT.uv);
    float4 diffuseColor = 0;
    float4 ambientColor = textureColor * 0.1;
	
	//light source
    float3 normal = normalize(INPUT.normal);
    float3 light = normalize(-lightDirection);
    float3 viewDir = normalize(INPUT.viewDirection);
	
	//difusse color
    float diffuse = max(dot(normal, light), 0);
    diffuseColor = lightDiffuseColor * diffuse * lightIntensity;
    
    
    float3 reflectVector = 2 * diffuse * normal - light;
    float specular = pow(max(dot(reflectVector, viewDir), 0), specularPower) * glossy;
    float4 specColor = specularColor * specular;
	
	//texture * (ambient + diffuse) + specular + emission
    return textureColor * saturate(saturate(diffuseColor + ambientColor) + specColor);

}