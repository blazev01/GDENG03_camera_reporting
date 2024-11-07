#pragma once
#include "Camera.h"
#include "Cube.h"
#include "../InputSystem/InputSystem.h"
#include "../Math/Colors.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GameObjects/RenderQueue.h"

class GameCamera:public Camera
{
public:
	GameCamera(std::string name, SwapChain* swapChain, void* shaderBytes, size_t shaderSize);
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void Release() override;
	void SetActive(bool isActive);
	~GameCamera();

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	bool isActive = false;
	float ticks = 0.0f;
	Matrix4x4 gameCameraTransforms;
};

