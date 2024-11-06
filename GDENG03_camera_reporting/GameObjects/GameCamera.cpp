#include "GameCamera.h"

GameCamera::GameCamera(std::string name, SwapChain* swapChain, Cube* cube, float width, float height):Camera(name,swapChain)
{
	this->camIndicator = cube;
	this->width = width;
	this->height = height;
}

void GameCamera::Update(float deltaTime)
{
	if (InputSystem::IsKeyDown(VK_RBUTTON))
	{
		std::cout << "RMB HELD" << "\n";
		InputSystem::ShowCursor(false);
	}
	else if (InputSystem::IsKeyUp(VK_RBUTTON))
	{
		std::cout << "RMB RELEASED" << "\n";
		InputSystem::ShowCursor(true);
	}

	if (InputSystem::IsKey(VK_RBUTTON))
	{
		Vector2 mousePos = InputSystem::GetCursorPosition();
		InputSystem::SetCursorPosition(this->width / 2.0f, this->height / 2.0f);

		if (mousePos != this->oldMousePos)
		{
			this->localRotation.x += (mousePos.y - (this->height / 2.0f)) * deltaTime * 0.1f;
			this->localRotation.y += (mousePos.x - (this->width / 2.0f)) * deltaTime * 0.1f;
			this->oldMousePos = mousePos;
			std::cout << this->camIndicator->GetLocalRotation().x << std::endl;
			std::cout << this->camIndicator->GetLocalRotation().y << std::endl;
		}
	}

	if (InputSystem::IsKey('W'))
	{
		std::cout << "W" << "\n";
		this->localPosition -= this->speed * deltaTime * this->GetForward();
	}

	if (InputSystem::IsKey('S'))
	{
		std::cout << "S" << "\n";
		this->localPosition += this->speed * deltaTime * this->GetForward();
		std::cout << this->camIndicator->GetLocalPosition() << std::endl;

	}

	if (InputSystem::IsKey('A'))
	{
		std::cout << "A" << "\n";
		this->localPosition -= this->speed * deltaTime * this->GetRight();
	}

	if (InputSystem::IsKey('D'))
	{
		std::cout << "D" << "\n";
		this->localPosition += this->speed * deltaTime * this->GetRight();
	}

	if (InputSystem::IsKey('Q'))
	{
		std::cout << "Q" << "\n";
		this->localPosition.y -= this->speed * deltaTime;
	}

	if (InputSystem::IsKey('E'))
	{
		std::cout << "E" << "\n";
		this->localPosition.y += this->speed * deltaTime;
	}
	Matrix4x4 temp;
	this->transform.SetIdentity();
	this->camIndicator->GetTransform().SetIdentity();

	temp.SetIdentity();
	temp.SetRotationX(this->localRotation.x);
	this->transform *= temp;
	this->camIndicator->SetRotation(this->localRotation);

	temp.SetIdentity();
	temp.SetRotationY(this->localRotation.y);
	this->transform *= temp;
	this->camIndicator->SetRotation(this->localRotation);
	
	this->transform.SetPosition(this->localPosition);
	this->camIndicator->SetPosition(this->localPosition);



	this->transform.Inverse();

	
}


void GameCamera::Release()
{
}

GameCamera::~GameCamera()
{
}
