#pragma once

#include "d3d11.h"

class GraphicsEngine;
class DeviceContext;

class VertexShader
{
public:
	VertexShader();
	bool Release();
	~VertexShader();

private:
	bool Init(const void* shaderBytes, size_t shaderByteSize);

private:
	ID3D11VertexShader* vs;

private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};

