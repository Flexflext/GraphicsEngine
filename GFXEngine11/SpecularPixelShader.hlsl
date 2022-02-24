Texture2D MainTexture : register(t0);
sampler MainSampler : register(s0);

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
};


float4 main(PixelInput INPUT) : SV_Target
{
    float4 textureColor = MainTexture.Sample(MainSampler, INPUT.uv);
    float4 diffuseColor = 0;
    float4 ambientColor = mul(textureColor, lightAmbientColor);
    
	//light source
    INPUT.normal = normalize(INPUT.normal);
    float3 light = normalize(-lightDirection);
    float3 viewDir = normalize(INPUT.viewDirection);
	
	//difusse color
    float diffuse = max(dot(INPUT.normal, light), 0);
    diffuseColor = lightDiffuseColor * diffuse * lightIntensity;
    
    
    float3 reflectVector = reflect(-light, INPUT.normal); //2 * diffuse * INPUT.normal - light;
    float specular = pow(max(dot(reflectVector, viewDir), 0), specularPower) * glossy;
    float4 specColor = specularColor * specular;
	
	//texture * (ambient + diffuse) + specular + emission
    return textureColor * saturate(saturate(diffuseColor + ambientColor) + specColor);
    //return float4(normalMapNormal, 1);
}