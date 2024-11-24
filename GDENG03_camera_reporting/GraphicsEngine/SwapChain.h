#pragma once
#include "d3d11.h"

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	bool Init(HWND hwnd, UINT width, UINT height, bool depthTest = true);
	bool Present(bool vsync);
	bool Release();

	int GetWidth() const;
	int GetHeight() const;

	ID3D11DepthStencilView* GetDSV();

private:
	int width = 0;
	int height = 0;

	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;
	ID3D11DepthStencilView* dsv;

private:
	friend class DeviceContext;
};

