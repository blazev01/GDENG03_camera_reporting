#pragma once
#include "GameObject.h"
#include "../GraphicsEngine/VertexBuffer.h"
#include "../GraphicsEngine/IndexBuffer.h"
#include "../GraphicsEngine/ConstantBuffer.h"

class Circle : public GameObject
{
public:
	Circle(std::string name, void* shaderBytes, size_t shaderSize);
	~Circle();

	void Update(float deltaTime) override;
	void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void Release() override;
	void SetVelocity(Vector3 velocity);

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

	float ticks = 0.0f;
	float deltaTime = 0.0f;
	float radius = 0.5f;
	Vector3 velocity;
};

