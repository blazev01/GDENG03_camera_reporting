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
    this->viewTexture = new ViewTexture();
}

Camera::~Camera()
{

}

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
	this->view.SetMatrix(this->transform);

	this->view.Inverse();
	this->transform.Inverse();
}

void Camera::Draw(Matrix4x4 view, Matrix4x4 proj)
{

}

void Camera::Release()
{
	this->swapChain->Release();
    this->viewTexture->Release();

	delete this;
}

void Camera::Render()
{
    GraphicsEngine::GetImmediateDeviceContext()->ClearRenderTargetColor(this->swapChain, 0.0f, 0.45f, 0.5f, 1.0f);

    GraphicsEngine::GetImmediateDeviceContext()->SetViewportSize(this->swapChain->GetWidth(), this->swapChain->GetHeight());

    RenderQueue::Render(this->cullingMask, this->transform, this->projection);
}

void Camera::RenderViewTexture()
{
    if (!this->viewTexture->GetRTV()) return;

    GraphicsEngine::GetImmediateDeviceContext()->ClearRenderTargetColor(this->viewTexture->GetRTV(), this->swapChain->getDSV(), 0.0f, 0.45f, 0.5f, 1.0f);

	GraphicsEngine::GetImmediateDeviceContext()->SetViewportSize(this->viewTexture->GetWidth(), this->viewTexture->GetHeight());

    RenderQueue::Render(this->cullingMask, this->transform, this->projection);
}

ViewTexture* Camera::GetViewTexture()
{
    return this->viewTexture;
}

Matrix4x4 Camera::GetViewMatrix()
{
    return this->transform;
}

Matrix4x4 Camera::GetProjectionMatrix()
{
    return this->projection ;
}

void Camera::SetOrthoProjection(float width, float height, float nearPlane, float farPlane)
{
	this->projection.SetOrthoLH(width, height, nearPlane, farPlane);
}

void Camera::SetPerspProjection(float fov, float aspect, float zNear, float zFar)
{
	this->projection.SetPerspectiveLH(fov, aspect, zNear, zFar);
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

float Camera::getWidth()
{
    return this->swapChain->GetWidth();
}

float Camera::getHeight()
{
    return this->swapChain->GetHeight();
}

