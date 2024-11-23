#pragma once
#include "Resource.h"
#include "../GraphicsEngine/VertexBuffer.h"
#include "../GraphicsEngine/IndexBuffer.h"

class Mesh : public Resource
{
public:
	Mesh(const wchar_t* fullPath);
	~Mesh();

	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

private:
	friend class DeviceContext;
};

