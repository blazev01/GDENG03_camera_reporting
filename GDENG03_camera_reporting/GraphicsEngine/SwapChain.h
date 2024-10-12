#pragma once
#include "d3d11.h"

class DeviceContext;

class SwapChain
{
public:
	SwapChain();

	bool Init(HWND hwnd, UINT width, UINT height);
	bool Present(bool vsync);
	bool Release();

	~SwapChain();

private:
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;
	ID3D11DepthStencilView* dsv;

private:
	friend class DeviceContext;
};

