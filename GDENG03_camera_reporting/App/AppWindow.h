#pragma once
#include "vector"
#include "../WindowSystem/Window.h"
#include "../InputSystem/InputListener.h"

#include "../GraphicsEngine/SwapChain.h"
#include "../GraphicsEngine/VertexShader.h"
#include "../GraphicsEngine/PixelShader.h"
#include "../GraphicsEngine/DepthStencilState.h"

#include "../GameObjects/Quad.h"
#include "../GameObjects/Cube.h"
#include "../GameObjects/Circle.h"

class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnDestroy() override;

	virtual void OnKey(int key) override;
	virtual void OnKeyDown(int key) override;
	virtual void OnKeyUp(int key) override;

	void SpawnCircles();
	void DespawnCircles();
	void DespawnAllCircles();

private:
	float deltaRot = 0.0f;
	float rotX = 0.0f;
	float rotY = 0.0f;
	int spawnSize = 5;

	bool spawn = false;
	bool despawn = false;
	bool despawnAll = false;

private:
	SwapChain* swapChain;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	std::vector<Circle*> circles;
	Cube* cube;
	Quad* quad;

	void* vsBytes = nullptr;
	size_t vsSize = 0;
};

