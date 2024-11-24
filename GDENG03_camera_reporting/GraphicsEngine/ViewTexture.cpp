#include "ViewTexture.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/DeviceContext.h"

ViewTexture::ViewTexture()
{
    this->rtv = NULL;
    this->dsv = NULL;
    this->srv = NULL;
}

ViewTexture::~ViewTexture()
{

}

bool ViewTexture::Initialize(int width, int height, bool depthTest)
{
    this->width = width;
    this->height = height;

    D3D11_TEXTURE2D_DESC texDesc = {};
    D3D11_RENDER_TARGET_VIEW_DESC rtDesc = {};
    D3D11_SHADER_RESOURCE_VIEW_DESC srDesc = {};

    ID3D11Texture2D* targetTex = nullptr;

    ID3D11Device* device = GraphicsEngine::GetDevice();
    ID3D11DeviceContext* deviceContext = GraphicsEngine::GetImmediateDeviceContext()->GetDeviceContext();

    texDesc.Width = width;
    texDesc.Height = height;
    texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.CPUAccessFlags = 0;
    texDesc.MiscFlags = 0;

    HRESULT hr = device->CreateTexture2D(&texDesc, NULL, &targetTex);
    if (FAILED(hr)) return false;

    rtDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    rtDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    rtDesc.Texture2D.MipSlice = 0;

    hr = device->CreateRenderTargetView(targetTex, &rtDesc, &this->rtv);
    if (FAILED(hr)) return false;

    //if (depthTest)
    //{
    //    hr = device->CreateDepthStencilView(targetTex, NULL, &this->dsv);
    //    if (FAILED(hr)) return false;
    //}

    srDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srDesc.Texture2D.MostDetailedMip = 0;
    srDesc.Texture2D.MipLevels = 1;

    hr = device->CreateShaderResourceView(targetTex, &srDesc, &this->srv);
    if (FAILED(hr)) return false;

    return true;
}

void ViewTexture::Release()
{
    if (this->rtv) this->rtv->Release();
    if (this->dsv) this->dsv->Release();
    if (this->srv) this->srv->Release();

    delete this;
}

int ViewTexture::GetWidth() const
{
    return this->width;
}

int ViewTexture::GetHeight() const
{
    return this->height;
}

ID3D11RenderTargetView* ViewTexture::GetRTV()
{
    return this->rtv;
}

ID3D11ShaderResourceView* ViewTexture::GetSRV()
{
    return this->srv;
}
