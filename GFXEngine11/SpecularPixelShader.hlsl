//Main Color Texture
Texture2D MainTexture : register(t0);
sampler MainSampler : register(s0);

//Light Data Constant Buffer
cbuffer LightData : register(b0) // has to be aligned in 16 byte blocks
{
    float3 lightDirection;
    float lightIntensity;
    float4 lightDiffuseColor;
    float4 lightAmbientColor;
};

//Calculate Extra Propertie Data
cbuffer ExtraData : register(b1) // has to be aligned in 16 byte blocks
{
    float4 specularColor;
    float glossy;
    float specularPower;
};

//Input fromthe Vertex Shader
struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 viewDirection : TEXCOORD1;
    float2 uv : TEXCOORD;
};


float4 main(PixelInput INPUT) : SV_Target
{
    //Sample Main Texture Color and UV
    float4 textureColor = MainTexture.Sample(MainSampler, INPUT.uv);
    float4 diffuseColor = 0;
    //Calc Main Color
    float4 ambientColor = mul(textureColor, lightAmbientColor);
    
	//light source
    //Normalize Normal
    INPUT.normal = normalize(INPUT.normal);
    //Normalize Light and Invert (Now going from Models Perspective)
    float3 light = normalize(-lightDirection);
    //Normalize View Dir
    INPUT.viewDirection = normalize(INPUT.viewDirection);
	
	//difusse color
    //Calculate Diffuse Shading Num
    float diffuse = max(dot(INPUT.normal, light), 0);
    //Calculate Diffuse Color
    diffuseColor = lightDiffuseColor * diffuse * lightIntensity;
    
    //Calculate Reflect Color from 
    float3 reflectVector = reflect(-light, INPUT.normal); //2 * diffuse * INPUT.normal - light;
    //Calculate Specular Multiplier
    float specular = pow(max(dot(reflectVector, INPUT.viewDirection), 0), specularPower) * glossy;
    //Calculate Specular Color
    float4 specColor = specularColor * specular;
	
	//Calculate Final Color
    return textureColor * saturate(saturate(diffuseColor + ambientColor) + specColor);
}