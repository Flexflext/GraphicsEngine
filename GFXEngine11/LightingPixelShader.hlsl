Texture2D MainTexture : register(t0);
sampler MainSampler;

//Light Data
cbuffer LightData
{
	float3 lightDirection;
	float lightIntensity;
	float4 lightDiffuseColor;
	float4 ambientColor;
};

//Input Data from Vertex Shader
struct PixelInput
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};


float4 main(PixelInput INPUT) : SV_TARGET
{
    //Sample TextureColor
	float4 textureColor = MainTexture.Sample(MainSampler, INPUT.uv);
	float4 diffuseColor = 0;
	
	//light source
	float3 normal = normalize(INPUT.normal);
	float3 light = normalize(-lightDirection);
	
	//difusse color
    float diffuse = max(dot(normal, light), 0);
	diffuseColor = lightDiffuseColor * diffuse * lightIntensity;
	
	//texture * (ambient + diffuse) + specular + emission
    return textureColor * diffuseColor + textureColor * ambientColor;
}