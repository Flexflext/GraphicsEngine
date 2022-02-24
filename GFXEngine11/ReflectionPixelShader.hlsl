Texture2D MainTexture : register(t0);
sampler MainSampler : register(s0);

Texture2D NormalTexture : register(t1);
sampler NormalTextureSampler : register(s1);

TextureCube ReflectionTexture : register(t2);
SamplerState ReflectionTextureSampler : register(s2);

cbuffer LightData : register(b0) // has to be aligned in 16 byte blocks
{
    float3 lightDirection;
    float lightIntensity;
    float4 lightDiffuseColor;
    float4 lightAmbientColor;
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
    float3 viewDirection : TEXCOORD1;
    float2 uv : TEXCOORD;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
};


float4 main(PixelInput INPUT) : SV_Target
{
    float4 textureColor = MainTexture.Sample(MainSampler, INPUT.uv);
    float4 diffuseColor = 0;
    
	
    //Normal Mapping
    INPUT.normal = normalize(INPUT.normal);
    INPUT.tangent = normalize(INPUT.tangent);
    INPUT.bitangent = normalize(INPUT.bitangent);
    
    float3x3 TBN = float3x3(normalize(INPUT.tangent), normalize(INPUT.bitangent), normalize(INPUT.normal)); //transforms world=>tangent space

    TBN = transpose(TBN); //transform tangent space=>world
    
    float3 normalMapNormal = (NormalTexture.Sample(NormalTextureSampler, INPUT.uv) * 2) - 1;
    normalMapNormal = mul(TBN, normalMapNormal);
    normalMapNormal = normalize(normalMapNormal);
    
	//light source
    float3 light = normalize(-lightDirection);
    float3 viewDir = normalize(INPUT.viewDirection);
	
	//diffuse color
    float diffuse = max(dot(normalMapNormal, light), 0);
    diffuseColor = lightDiffuseColor * diffuse * lightIntensity;
    
    
    float3 reflectVector = 2 * diffuse * normalMapNormal - light;
    float specular = pow(max(dot(reflectVector, viewDir), 0), specularPower) * glossy;
    float4 specColor = specularColor * specular;
	
	//texture * (ambient + diffuse) + specular + emission
    //textureColor = textureColor * saturate(saturate(diffuseColor + ambientColor) + specColor);
    //return float4(normalMapNormal, 1);
    float3 reflectedVec = reflect(INPUT.viewDirection, normalMapNormal);
    
    float4 reflectedColour = ReflectionTexture.Sample(ReflectionTextureSampler, reflectedVec);
    
    //return lerp(textureColor, reflectedColour, glossy);
    float4 ambientColor = mul(reflectedColour, lightAmbientColor);
    return reflectedColour * saturate(saturate(diffuseColor + ambientColor) + specColor); 
}