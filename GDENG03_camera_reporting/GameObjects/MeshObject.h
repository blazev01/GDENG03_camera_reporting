#pragma once
#include "GameObject.h"
#include "../GraphicsEngine/VertexBuffer.h"
#include "../GraphicsEngine/IndexBuffer.h"
#include "../GraphicsEngine/ConstantBuffer.h"
#include "../Resource/Mesh.h"
#include "../Resource/Texture.h"

class MeshObject : public GameObject
{
public:
	MeshObject(std::string name, void* shaderBytes, size_t shaderSize);
	~MeshObject();

	void Update(float deltaTime) override;
	void Draw(Matrix4x4 view, Matrix4x4 proj) override;
	void Destroy() override;

	void SetMesh(Mesh* mesh);
	void SetTexture(Texture* texture);

private:
	float ticks = 0.0f;
	ConstantBuffer* constantBuffer = NULL;
	Mesh* mesh = NULL;
	Texture* texture = NULL;
};

