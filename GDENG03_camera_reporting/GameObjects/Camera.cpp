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

	this->swapChain->Present(true);
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

std::bitset<4> Camera::GetCullingMask() const
{
	return this->cullingMask;
}

void Camera::SetCullingMask(std::bitset<4> cullingMask)
{
	this->cullingMask = cullingMask;
}

