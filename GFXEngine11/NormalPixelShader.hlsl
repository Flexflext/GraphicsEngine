//Main Texture and Sampler
Texture2D MainTexture : register(t0);
sampler MainSampler : register(s0);

//Sampler and Texture of the Normal Texture
Texture2D NormalTexture : register(t1);
sampler NormalTextureSampler : register(s1);

//LightData from Constant Buffer
cbuffer LightData : register(b0) // has to be aligned in 16 byte blocks
{
    float3 lightDirection;
    float lightIntensity;
    float4 lightDiffuseColor;
    float4 lightAmbientColor;
};

// Extra Constant Buffer Data
cbuffer ExtraData : register(b1)
{
    float4 specularColor;
    float glossy;
    float specularPower;
};

// Input from VerteXShader
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
    //Sample TextureCOlor and Set 
    float4 textureColor = MainTexture.Sample(MainSampler, INPUT.uv);
    float4 diffuseColor = 0;
    float4 ambientColor = mul(textureColor, lightAmbientColor);
	
    //Normal Mapping
    //Normalize Input Datat
    INPUT.normal = normalize(INPUT.normal);
    INPUT.tangent = normalize(INPUT.tangent);
    INPUT.bitangent = normalize(INPUT.bitangent);
    
    //Cretae the Matrix to Calculate from Tangent to World Space
    float3x3 TBN = float3x3(normalize(INPUT.tangent), normalize(INPUT.bitangent), normalize(INPUT.normal)); //transforms world=>tangent space

    //Transpose -> Change Rows with Collums
    TBN = transpose(TBN); //transform tangent space=>world
    
    //Sample Normal Map
    float3 normalMapNormal = (NormalTexture.Sample(NormalTextureSampler, INPUT.uv) * 2) - 1;
    //Calczlate the Normal
    normalMapNormal = mul(TBN, normalMapNormal);
    //Normalize
    normalMapNormal = normalize(normalMapNormal);
    
	//light source
    //Invert light Direction
    float3 light = normalize(-lightDirection);
    //Normalize View Direction
    float3 viewDir = normalize(INPUT.viewDirection);
	
	//difusse color
    float diffuse = max(dot(normalMapNormal, -light), 0);
    //Calculate Diffuse Color
    diffuseColor = lightDiffuseColor * diffuse * lightIntensity;
    
    //Calculate the Reflect Vector Phong
    float3 reflectVector = 2 * diffuse * normalMapNormal - light;
    //Calculate the Specular Highlight
    float specular = pow(max(dot(reflectVector, viewDir), 0), specularPower) * glossy;
    //Calculate the Specular Color
    float4 specColor = specularColor * specular;
	
	//Calculate Final Color
    return textureColor * saturate(saturate(diffuseColor + ambientColor) + specColor);
}