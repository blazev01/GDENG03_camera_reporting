#include "SwapChain.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain()
{
	this->swapChain = NULL;
	this->rtv = NULL;
	this->dsv = NULL;
}

bool SwapChain::Init(HWND hwnd, UINT width, UINT height, bool depthTest)
{
	this->width = width;
	this->height = height;

	ID3D11Device* device = GraphicsEngine::GetDevice();
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = GraphicsEngine::GetFactory()->CreateSwapChain(device, &desc, &this->swapChain);
	if (FAILED(hr)) return false;

	ID3D11Texture2D* buffer = NULL;
	hr = this->swapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(hr)) return false;

	hr = device->CreateRenderTargetView(buffer, NULL, &this->rtv);
	buffer->Release();
	if (FAILED(hr)) return false;

	if (depthTest)
	{
		D3D11_TEXTURE2D_DESC texDesc = {};
		texDesc.Width = width;
		texDesc.Height = height;
		texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		texDesc.Usage = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		texDesc.MipLevels = 1;
		texDesc.SampleDesc.Count = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.MiscFlags = 0;
		texDesc.ArraySize = 1;
		texDesc.CPUAccessFlags = 0;

		hr = device->CreateTexture2D(&texDesc, NULL, &buffer);
		if (FAILED(hr)) return false;

		hr = device->CreateDepthStencilView(buffer, NULL, &this->dsv);
		if (FAILED(hr)) return false;
	}

	return true;
}

bool SwapChain::Present(bool vsync)
{
	this->swapChain->Present(vsync, NULL);
	return true;
}

bool SwapChain::Release()
{
	this->swapChain->Release();
	delete this;
	return true;
}

int SwapChain::GetWidth() const
{
	return this->width;
}

int SwapChain::GetHeight() const
{
	return this->height;
}

SwapChain::~SwapChain()
{

}
