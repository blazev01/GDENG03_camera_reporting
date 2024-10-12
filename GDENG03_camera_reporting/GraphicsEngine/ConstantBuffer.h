#pragma once
#include "d3d11.h"
#include "DeviceContext.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	bool Load(void* buffer, UINT bufferSize);
	void Update(DeviceContext* context, void* buffer);
	bool Release();
	~ConstantBuffer();

private:
	ID3D11Buffer* buffer;

private:
	friend class DeviceContext;
};

