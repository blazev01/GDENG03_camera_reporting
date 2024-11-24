#pragma once
#include "d3d11.h"

class DeviceContext;

class ViewTexture
{
public:
	ViewTexture();
	~ViewTexture();

	bool Initialize(int width, int height, bool depthTest = true);
	void Release();

	int GetWidth() const;
	int GetHeight() const;

	ID3D11RenderTargetView* GetRTV();
	ID3D11ShaderResourceView* GetSRV();

private:
	int width = 0;
	int height = 0;

	ID3D11RenderTargetView* rtv;
	ID3D11DepthStencilView* dsv;
	ID3D11ShaderResourceView* srv;

private:
	friend class DeviceContext;
};

