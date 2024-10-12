#pragma once
#include "d3d11.h"
#include "DeviceContext.h"

class VertexBuffer
{
public:
	VertexBuffer();
	bool Load(void* vertexList, UINT vertexSize, UINT listSize, void* shaderBytes, UINT shaderByteSize);
	UINT GetVertexListSize();
	bool Release();
	~VertexBuffer();

private:
	UINT vertexSize;
	UINT listSize;

private:
	ID3D11Buffer* buffer;
	ID3D11InputLayout* layout;

private:
	friend class DeviceContext;
};

