#pragma once
#include "d3d11.h"
#include "DeviceContext.h"

class DepthStencilState
{
public:
	DepthStencilState();
	~DepthStencilState();

	bool Load();
	bool LoadDrawMask();
	bool LoadApplyMask();
	bool Release();

private:
	ID3D11DepthStencilState* dsState;

private:
	friend class DeviceContext;
};

