#include "Camera.h"
#include "RenderQueue.h"
#include "../InputSystem/InputSystem.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/DeviceContext.h"

Camera::Camera(std::string name, SwapChain* swapChain) : GameObject(name)
{
	for (int i = 0; i < this->cullingMask.size(); i++)
		this->cullingMask[i] = true;

	this->swapChain = swapChain;
}

Camera::~Camera()
{}

void Camera::Update(float deltaTime)
{
	Matrix4x4 temp;
	this->transform.SetIdentity();

	temp.SetIdentity();
	temp.SetRotationX(this->localRotation.x);
	this->transform *= temp;

	temp.SetIdentity();
	temp.SetRotationY(this->localRotation.y);
	this->transform *= temp;

	this->transform.SetPosition(this->localPosition);

	this->transform.Inverse();
}

void Camera::Draw()
{
	GraphicsEngine::GetImmediateDeviceContext()->ClearRenderTargetColor(this->swapChain, 0.0f, 0.45f, 0.5f, 1.0f);

	GraphicsEngine::GetImmediateDeviceContext()->SetViewportSize(this->width, this->height);

	RenderQueue::Render(this->cullingMask);
}

void Camera::Release()
{
	this->swapChain->Release();

	delete this;
}

Matrix4x4 Camera::GetViewMatrix()
{
    return this->transform;
}

Matrix4x4 Camera::GetProjectionMatrix()
{
    return this->projection;
}

void Camera::SetOrthoProjection(float width, float height, float nearPlane, float farPlane)
{
	this->projection.SetOrthoLH(width, height, nearPlane, farPlane);
}

void Camera::SetPerspProjection(float fov, float aspect, float zNear, float zFar)
{
	this->projection.SetPerspectiveLH(fov, aspect, zNear, zFar);
}

void Camera::SetWindowSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Camera::Present()
{
	this->swapChain->Present(true);
}

std::bitset<4> Camera::GetCullingMask() const
{
	return this->cullingMask;
}

void Camera::SetCullingMask(std::bitset<4> cullingMask)
{
	this->cullingMask = cullingMask;
}

ID3D11ShaderResourceView* Camera::RenderCameraToTexture()
{
    D3D11_TEXTURE2D_DESC texdesc;
    D3D11_RENDER_TARGET_VIEW_DESC rtdesc;
    D3D11_SHADER_RESOURCE_VIEW_DESC srdesc;

    ID3D11Texture2D* targetTex;
    ID3D11RenderTargetView* rtview;
    ID3D11ShaderResourceView* srview; 

    ID3D11Device* device = GraphicsEngine::GetDevice();
    ID3D11DeviceContext* deviceContext = GraphicsEngine::GetImmediateDeviceContext()->GetDeviceContext();
    
    ZeroMemory(&texdesc, sizeof(texdesc));

    texdesc.Width = this->width;
    texdesc.Height = this->height;
    texdesc.MipLevels = 1;
    texdesc.ArraySize = 1;
    texdesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    texdesc.SampleDesc.Count = 1;
    texdesc.Usage = D3D11_USAGE_DEFAULT;
    texdesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    texdesc.CPUAccessFlags = 0;
    texdesc.MiscFlags = 0;

    HRESULT hr = device->CreateTexture2D(&texdesc, NULL, &targetTex);
    if (FAILED(hr)) {
        std::cout << "Failed to create texture2D" << std::endl;
        return nullptr;
    }

    rtdesc.Format = texdesc.Format;
    rtdesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D; 
    rtdesc.Texture2D.MipSlice = 0;

    hr = device->CreateRenderTargetView(targetTex, &rtdesc, &rtview);
    if (FAILED(hr)) {
        std::cout << "Failed to create render target view" << std::endl;
        return nullptr;
    }

    srdesc.Format = texdesc.Format;
    srdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    srdesc.Texture2D.MostDetailedMip = 0;
    srdesc.Texture2D.MipLevels = 1;
    
    hr = device->CreateShaderResourceView(targetTex, &srdesc, &srview);
    if (FAILED(hr)) {
        std::cout << "Failed to create shader resource view" << std::endl;
        return nullptr;
    }

    deviceContext->OMSetRenderTargets(1, &rtview, NULL);
    
    float clearColor[4] = { 0.0f, 0.45f, 0.5f, 1.0f };
    deviceContext->ClearRenderTargetView(rtview, clearColor);

    this->Draw();

    //ID3D11Texture2D* renderTargetTexture = nullptr;
    //CD3D11_TEXTURE2D_DESC renderTargetDesc = {};
    //D3D11_TEXTURE2D_DESC textureDesc = {};


    //renderTargetDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //renderTargetDesc.Width = static_cast<UINT>(this->width);
    //renderTargetDesc.Height = static_cast<UINT>(this->height);
    //renderTargetDesc.ArraySize = 1; 
    //renderTargetDesc.MipLevels = 1; 
    //renderTargetDesc.SampleDesc.Count = 1;

    //HRESULT hr = device->CreateTexture2D(&renderTargetDesc, NULL, &renderTargetTexture);
    //if (FAILED(hr)) {
    //    std::cout << "Texture2D creation failed" << std::endl;
    //    return nullptr;
    //}

    //ID3D11RenderTargetView* renderTargetView = nullptr;
    //hr = device->CreateRenderTargetView(renderTargetTexture, NULL, &renderTargetView);
    //if (FAILED(hr)) {
    //    std::cout << "Render Target View creation failed" << std::endl;
    //    renderTargetTexture->Release();
    //    return nullptr;
    //}

    //ID3D11ShaderResourceView* shaderResourceView = nullptr;
    //hr = device->CreateShaderResourceView(renderTargetTexture, NULL, &shaderResourceView);
    //if (FAILED(hr)) {
    //    std::cout << "Shader Resource View creation failed" << std::endl;
    //    renderTargetView->Release();
    //    renderTargetTexture->Release();
    //    return nullptr;
    //}

    //deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);

    //float clearColor[4] = { 0.0f, 0.45f, 0.5f, 1.0f };
    //deviceContext->ClearRenderTargetView(renderTargetView, clearColor);

    //this->Draw();

    //renderTargetView->Release();

    return srview;
}


