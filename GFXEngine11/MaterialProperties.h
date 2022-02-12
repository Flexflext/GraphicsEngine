#pragma once
#include <d3d11.h>
#include "Utils.h"

class MaterialProperties
{
public:
	virtual INT InitProperties(ID3D11DeviceContext* _p_d3ddevicecontext, ID3D11Device* _p_d3ddevice) = 0;
	virtual void Update() = 0;
	virtual void DeinitProperties() = 0;
	EMaterials materialType;
protected:
	ID3D11DeviceContext* p_d3dDeviceContext = nullptr;
	ID3D11Device* p_d3dDevice = nullptr;
};

