#pragma once
#include "Camera.h"
#include "Cube.h"
class GameCamera:public Camera
{
public:
	GameCamera(std::string name, SwapChain* swapChain, Cube* cube);
	virtual void Update(float deltaTime) override;
	virtual void Release() override;
	~GameCamera();
private:
	Cube* camIndicator;
};

