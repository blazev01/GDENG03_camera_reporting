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
	virtual void Draw(Matrix4x4 view, Matrix4x4 proj) override;
	virtual void Destroy() override;
	virtual void Recalculate() override;
	~GameCamera();

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

	float ticks = 0.0f;
};

