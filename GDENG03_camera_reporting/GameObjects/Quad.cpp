#include "Quad.h"
#include "../Math/Colors.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"

Quad::Quad(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name,QUAD)
{
	Vertex vertices[] =
	{
		{ Vector3D(-0.5f, -0.5f, 0.0f), Vector2D(0.0f,1.0f), RGBA_WHITE },
		{ Vector3D(-0.5f,  0.5f, 0.0f), Vector2D(0.0f,0.0f), RGBA_WHITE },
		{ Vector3D(0.5f, -0.5f, 0.0f), Vector2D(1.0f,0.0f), RGBA_WHITE },
		{ Vector3D(0.5f,  0.5f, 0.0f), Vector2D(1.0f,1.0f), RGBA_WHITE },
	};

	this->vertexBuffer = GraphicsEngine::CreateVertexBuffer();
	UINT vertexListSize = ARRAYSIZE(vertices);

	this->vertexBuffer->Load(vertices, sizeof(Vertex), ARRAYSIZE(vertices), shaderBytes, shaderSize);

	Constant cc = Constant();
	cc.time = 0;

	this->constantBuffer = GraphicsEngine::CreateConstantBuffer();
	this->constantBuffer->Load(&cc, sizeof(Constant));

}

Quad::~Quad()
{

}

void Quad::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	//this->ticks += deltaTime;
}

void Quad::Draw(Matrix4x4 view, Matrix4x4 proj)
{
	Constant cc = Constant();
	cc.time = this->ticks;
	cc.world = this->transform;
	cc.view = view;
	cc.proj = proj;

	this->constantBuffer->Update(GraphicsEngine::GetImmediateDeviceContext(), &cc);
	GraphicsEngine::GetImmediateDeviceContext()->SetConstantBuffer(this->vertexShader, this->constantBuffer);
	GraphicsEngine::GetImmediateDeviceContext()->SetConstantBuffer(this->pixelShader, this->constantBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->SetVertexShader(this->vertexShader);
	GraphicsEngine::GetImmediateDeviceContext()->SetPixelShader(this->pixelShader);

	if (this->texture) {
		GraphicsEngine::GetImmediateDeviceContext()->SetTexture(this->vertexShader, this->texture);
		GraphicsEngine::GetImmediateDeviceContext()->SetTexture(this->pixelShader, this->texture);
	}

	GraphicsEngine::GetImmediateDeviceContext()->SetVertexBuffer(this->vertexBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->DrawTriangleStrip(this->vertexBuffer->GetVertexListSize(), 0);
}

void Quad::Destroy()
{
	GameObject::Destroy();

	this->vertexBuffer->Release();
	this->constantBuffer->Release();

	delete this;
}
