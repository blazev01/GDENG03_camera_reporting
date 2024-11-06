#pragma once
#include "d3d11.h"

class ViewTexture
{
public:
	ViewTexture();
	~ViewTexture();

	bool Initialize(int width, int height);
	void Release();

	int GetWidth();
	int GetHeight();

	ID3D11RenderTargetView* GetRTV();
	ID3D11ShaderResourceView* GetSRV();

private:
	int width = 0;
	int height = 0;

	ID3D11RenderTargetView* rtv;
	ID3D11ShaderResourceView* srv;
};

