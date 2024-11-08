#pragma once
#include "Resource.h"
#include "d3d11.h"

class Texture : public Resource
{
public:
	Texture(const wchar_t* fullPath);
	~Texture();

	ID3D11ShaderResourceView* GetSRV();

private:
	ID3D11Resource* texture = NULL;
	ID3D11ShaderResourceView* srv = NULL;

	friend class DeviceContext;
};

