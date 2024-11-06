#include "GameCamera.h"

GameCamera::GameCamera(std::string name, SwapChain* swapChain, Cube* cube):Camera(name,swapChain)
{
	this->camIndicator = cube;
}

void GameCamera::Update(float deltaTime)
{
	Matrix4x4 temp;
	this->transform.SetIdentity();
	this->camIndicator->GetTransform().SetIdentity();

	temp.SetIdentity();
	temp.SetRotationX(this->localRotation.x);
	this->transform *= temp;
	this->camIndicator->MultiplyTransform(temp);

	temp.SetIdentity();
	temp.SetRotationY(this->localRotation.y);
	this->transform *= temp;
	this->camIndicator->MultiplyTransform(temp);
	
	this->transform.SetPosition(this->localPosition);
	this->camIndicator->GetTransform().SetPosition(this->localPosition);

	this->transform.Inverse();

	
}


void GameCamera::Release()
{
}

GameCamera::~GameCamera()
{
}
