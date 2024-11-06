#include "ViewTexture.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/DeviceContext.h"

ViewTexture::ViewTexture()
{
    this->rtv = NULL;
    this->srv = NULL;
}

ViewTexture::~ViewTexture()
{

}

bool ViewTexture::Initialize(int width, int height)
{
    this->width = width;
    this->height = height;

    D3D11_TEXTURE2D_DESC texdesc = {};
    D3D11_RENDER_TARGET_VIEW_DESC rtdesc = {};
    D3D11_SHADER_RESOURCE_VIEW_DESC srdesc = {};

    ID3D11Texture2D* targetTex = nullptr;

    ID3D11Device* device = GraphicsEngine::GetDevice();
    ID3D11DeviceContext* deviceContext = GraphicsEngine::GetImmediateDeviceContext()->GetDeviceContext();

    texdesc.Width = width;
    texdesc.Height = height;
    texdesc.MipLevels = 1;
    texdesc.ArraySize = 1;
    texdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texdesc.SampleDesc.Count = 1;
    texdesc.Usage = D3D11_USAGE_DEFAULT;
    texdesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    texdesc.CPUAccessFlags = 0;
    texdesc.MiscFlags = 0;

    HRESULT hr = device->CreateTexture2D(&texdesc, NULL, &targetTex);
    if (FAILED(hr)) return false;

    rtdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    rtdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    rtdesc.Texture2D.MipSlice = 0;

    hr = device->CreateRenderTargetView(targetTex, &rtdesc, &this->rtv);
    if (FAILED(hr)) return false;

    srdesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    srdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srdesc.Texture2D.MostDetailedMip = 0;
    srdesc.Texture2D.MipLevels = 1;

    hr = device->CreateShaderResourceView(targetTex, &srdesc, &this->srv);
    if (FAILED(hr)) return false;

    return true;
}

void ViewTexture::Release()
{
    this->rtv->Release();
    this->srv->Release();

    delete this;
}

int ViewTexture::GetWidth()
{
    return this->width;
}

int ViewTexture::GetHeight()
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
