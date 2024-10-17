#pragma once
#include "GameObject.h"
#include "../GraphicsEngine/VertexBuffer.h"
#include "../GraphicsEngine/IndexBuffer.h"
#include "../GraphicsEngine/ConstantBuffer.h"

class Cube : public GameObject
{
public:
	Cube(std::string name, void* shaderBytes, size_t shaderSize);
	~Cube();

	void Update(float deltaTime) override;
	void Draw(VertexShader* vertexShader, PixelShader* pixelShader) override;
	void Release() override;
	void SetAnimationSpeed(float speed);

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaRot = 0.0f;
	float deltaTime = 0.0f;
	float speed = 1.0f;
};

