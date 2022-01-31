struct PixelInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};


float4 main(PixelInput INPUT) : SV_TARGET
{
	//return float4(1.0f, 1.0f, 0.0f, 1.0f); //Solid Color Value for all pixels
	
	INPUT.color.w = 1.0f;
	INPUT.color.x = 1.0f;
	INPUT.color.y = 1.0f;
	INPUT.color.z = 1.0f;
	
	return INPUT.color; // Solid Color Value interpolated
}