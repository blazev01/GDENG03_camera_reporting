#include "Camera.h"
#include "RenderQueue.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/DeviceContext.h"
#include "../InputSystem/InputSystem.h"

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
	this->deltaTime = deltaTime;
}

void Camera::Draw(Matrix4x4 view, Matrix4x4 proj)
{

}

void Camera::Destroy()
{
	GameObject::Destroy();

	this->swapChain->Release();
	this->viewTexture->Release();

	delete this;
}

void Camera::Recalculate()
{
	GameObject::Recalculate();

	Matrix4x4 temp;
	this->view.SetIdentity();

	temp.SetIdentity();
	temp.SetRotationX(-this->localRotation.x);
	this->view *= temp;

	temp.SetIdentity();
	temp.SetRotationY(-this->localRotation.y);
	this->view *= temp;

	temp.SetIdentity();
	temp.SetRotationZ(-this->localRotation.z);
	this->view *= temp;

	this->view.SetPosition(this->localPosition);
	this->view.Inverse();
}

void Camera::Render()
{
	GraphicsEngine::GetImmediateDeviceContext()->ClearRenderTargetColor(this->swapChain, 0.0f, 0.45f, 0.5f, 1.0f);

	GraphicsEngine::GetImmediateDeviceContext()->SetViewportSize(this->swapChain);

	RenderQueue::Render(this->cullingMask, this->view, this->projection);
}

void Camera::RenderViewTexture()
{
	GraphicsEngine::GetImmediateDeviceContext()->ClearRenderTargetColor(this->viewTexture, 0.0f, 0.45f, 0.5f, 1.0f);

	GraphicsEngine::GetImmediateDeviceContext()->SetViewportSize(this->viewTexture);

	RenderQueue::Render(this->cullingMask, this->view, this->projection);
}

void Camera::Present()
{
	this->swapChain->Present(true);
}

ViewTexture* Camera::GetViewTexture()
{
	return this->viewTexture;
}

Matrix4x4 Camera::GetView() const
{
    return this->view;
}

Matrix4x4 Camera::GetProjection() const
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

std::vector<Vector3D> Camera::CreateRenderRegionOutliner(float fov, float aspect, float z)
{
	float angle = fov; //already in radians
	//float angle = fov * 3.14 / 180 * 1.047;

	float heightZ = 2 * z * std::tan(angle / 2);
	float widthZ = heightZ * aspect;

	Vector3D zTL = Vector3D(-widthZ / 2, heightZ / 2, z);
	Vector3D zTR = Vector3D(widthZ / 2, heightZ / 2, z);
	Vector3D zBL = Vector3D(-widthZ / 2, -heightZ / 2, z);
	Vector3D zBR = Vector3D(widthZ / 2, -heightZ / 2, z);

	/*Line* line = new Line("lyn", AppWindow::instance->vsBytes, AppWindow::instance->vsSize, Vector3D(0), Vector3D(1));
	line->SetVertexShader(AppWindow::instance->vertexShader);
	line->SetPixelShader(AppWindow::instance->pixelShader);
	GameObjectManager::AddGameObject(line);
	RenderQueue::AddRenderer(line);*/

	return { zTL, zTR, zBL, zBR };
}

std::bitset<4> Camera::GetCullingMask() const
{
	return this->cullingMask;
}

void Camera::SetCullingMask(std::bitset<4> cullingMask)
{
	this->cullingMask = cullingMask;
}

