#pragma once

#include "d3d11.h"

class GraphicsEngine;
class DeviceContext;

class PixelShader
{
public:
	PixelShader();
	bool Release();
	~PixelShader();

private:
	bool Init(const void* shaderBytes, size_t shaderByteSize);

private:
	ID3D11PixelShader* ps;

private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};

