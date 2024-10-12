#pragma once
#include "d3d11.h"
#include "DeviceContext.h"

class IndexBuffer
{
public:
	IndexBuffer();
	bool Load(void* indexList, UINT listSize);
	UINT GetIndexListSize();
	bool Release();
	~IndexBuffer();

private:
	UINT listSize;

private:
	ID3D11Buffer* buffer;

private:
	friend class DeviceContext;
};

