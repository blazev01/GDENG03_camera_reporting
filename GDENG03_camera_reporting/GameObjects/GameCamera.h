#pragma once
#include "Camera.h"
#include "Cube.h"
#include "../InputSystem/InputSystem.h"
class GameCamera:public Camera
{
public:
	GameCamera(std::string name, SwapChain* swapChain, Cube* cube, float width, float height);
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	~GameCamera();
private:
	Cube* camIndicator;
	
	
};

