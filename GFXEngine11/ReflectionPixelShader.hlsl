//Main Color Texture
Texture2D MainTexture : register(t0);
sampler MainSampler : register(s0);

//Reflection Texture
TextureCube ReflectionTexture : register(t1);
SamplerState ReflectionTextureSampler : register(s1);

//Light properties
cbuffer LightData : register(b0) // has to be aligned in 16 byte blocks
{
    float3 lightDirection;
    float lightIntensity;
    float4 lightDiffuseColor;
    float4 lightAmbientColor;
};

//Properties from Material
cbuffer MaterialProperties : register(b1) // has to be aligned in 16 byte blocks
{
    float4 specularColor;
    float glossy;
    float specularPower;
};

//input from Vertex Shader
struct PixelInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 viewDirection : TEXCOORD1;
    float2 uv : TEXCOORD;
};


float4 main(PixelInput INPUT) : SV_Target
{
    //Calculate Main Color and Ambient Color
    float4 textureColor = MainTexture.Sample(MainSampler, INPUT.uv);
    float4 diffuseColor = 0;
    float4 ambientColor = mul(textureColor, lightAmbientColor);
    
    INPUT.normal = normalize(INPUT.normal);
    
	//light source
    //Invert light Direction
    float3 light = normalize(-lightDirection);
    //Normalize View Direction
    float3 viewDir = normalize(INPUT.viewDirection);
	
	//difusse color
    float diffuse = max(dot(INPUT.normal, light), 0);
    //Calculate Diffuse Color
    diffuseColor = lightDiffuseColor * diffuse * lightIntensity;
    
    //Calculate the Reflect Vector Phong
    float3 reflectVector = 2 * diffuse * INPUT.normal - light;
    //Calculate the Specular Highlight
    float specular = pow(max(dot(reflectVector, viewDir), 0), specularPower) * glossy;
    //Calculate the Specular Color
    float4 specColor = specularColor * specular;
	
    //Reflection from View Direction and Normal
    float3 reflectedVec = reflect(INPUT.viewDirection, INPUT.normal);
    //Invert Y Axis (Correct Reflection)
    reflectedVec.y = -reflectedVec.y;
    
    //Calculate Reflected Color
    float4 reflectedColour = ReflectionTexture.Sample(ReflectionTextureSampler, reflectedVec);
    
    //Lerp Color Dependent on the Glossyness
    float4 color = lerp(textureColor, reflectedColour, glossy);
    
    //Calculate Final Color
    return color * saturate(saturate(diffuseColor + ambientColor) + specColor);
}