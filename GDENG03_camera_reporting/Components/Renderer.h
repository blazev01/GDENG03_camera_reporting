#pragma once
#include "Component.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/VertexShader.h"
#include "../GraphicsEngine/PixelShader.h"
#include "../GraphicsEngine/ConstantBuffer.h"
#include "../Resource/Mesh.h"
#include "../Resource/Texture.h"

class Renderer : public Component
{
public:
	Renderer(
		std::string name,
		GameObject* owner,
		VertexShader* vertexShader,
		PixelShader* pixelShader);
	~Renderer();

	virtual void Perform(float deltaTime) override;
	virtual void Destroy() override;

	VertexShader* GetVertexShader();
	void SetVertexShader(VertexShader* vertexShader);
	PixelShader* GetPixelShader();
	void SetPixelShader(PixelShader* pixelShader);

	Mesh* GetMesh();
	void SetMesh(Mesh* mesh);
	Texture* GetTexture();
	void SetTexture(Texture* texture);

	std::wstring GetTextureFilePath();
	void SetTextureFilePath(std::wstring path);

	void SetWorld(const Matrix4x4& world);
	void SetView(const Matrix4x4& view);
	void SetProjection(const Matrix4x4& projection);

private:
	VertexShader* vertexShader = NULL;
	PixelShader* pixelShader = NULL;

	ConstantBuffer* constantBuffer = NULL;
	Constant cc;

	Mesh* mesh = NULL;
	Texture* texture = NULL;

	std::wstring texFilePath = L"";
};

