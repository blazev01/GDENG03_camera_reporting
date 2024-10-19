#include "Camera.h"
#include "../InputSystem/InputSystem.h"

Camera::Camera(std::string name) : GameObject(name)
{
	this->camPos = Vector3(0.0f, 0.0f, -2.0f);
	this->localPosition = this->camPos;
	
	this->transform.SetPosition(this->localPosition);
	this->transform.Inverse();

	for (int i = 0; i < this->cullingMask.size(); i++)
		this->cullingMask[i] = true;
}

Camera::~Camera()
{}

void Camera::Update(float deltaTime)
{
	this->deltaTime = deltaTime;

	if (InputSystem::IsKeyDown(VK_LBUTTON))
	{
		std::cout << "LMB HELD" << "\n";
		InputSystem::ShowCursor(false);
	}
	else if (InputSystem::IsKeyUp(VK_LBUTTON))
	{
		std::cout << "LMB RELEASED" << "\n";
		InputSystem::ShowCursor(true);
	}
		
	if (InputSystem::IsKey(VK_LBUTTON))
	{
		Vector2 mousePos = InputSystem::GetCursorPosition();
		InputSystem::SetCursorPosition(this->width / 2.0f, this->height / 2.0f);

		if (mousePos != this->oldMousePos)
		{
			this->rotX += (mousePos.y - (this->height / 2.0f)) * this->deltaTime * 0.1f;
			this->rotY += (mousePos.x - (this->width / 2.0f)) * this->deltaTime * 0.1f;
			this->oldMousePos = mousePos;
		}
	}

	if (InputSystem::IsKey('W'))
	{
		std::cout << "W" << "\n";
		this->camPos -= this->speed * this->deltaTime * this->GetForward();
	}
	
	if (InputSystem::IsKey('S'))
	{
		std::cout << "S" << "\n";
		this->camPos += this->speed * this->deltaTime * this->GetForward();
	}
	
	if (InputSystem::IsKey('A'))
	{
		std::cout << "A" << "\n";
		this->camPos -= this->speed * this->deltaTime * this->GetRight();
	}
	
	if (InputSystem::IsKey('D'))
	{
		std::cout << "D" << "\n";
		this->camPos += this->speed * this->deltaTime * this->GetRight();
	}
	
	if (InputSystem::IsKey('Q'))
	{
		std::cout << "Q" << "\n";
		this->camPos.y -= this->speed * this->deltaTime;
	}
	
	if (InputSystem::IsKey('E'))
	{
		std::cout << "E" << "\n";
		this->camPos.y += this->speed * this->deltaTime;
	}

	Matrix4x4 temp;
	this->transform.SetIdentity();

	temp.SetIdentity();
	temp.SetRotationX(this->rotX);
	this->transform *= temp;

	temp.SetIdentity();
	temp.SetRotationY(this->rotY);
	this->transform *= temp;

	this->transform.SetPosition(this->camPos);

	this->transform.Inverse();
}

void Camera::Draw(VertexShader * vertexShader, PixelShader * pixelShader)
{}

void Camera::Release()
{}

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

