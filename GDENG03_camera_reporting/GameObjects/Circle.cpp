#include "Circle.h"
#include "vector"
#include "../Math/Colors.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../SceneCamera/SceneCameraHandler.h"


Circle::Circle(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name)
{
	this->radius = 0.5f;
	int segments = 32;

	Vertex vertices[32 + 1];
	int indices[32 * 3] = {};

	for (int i = 0; i < segments; i++) {
		float angle = 2.0f * 3.14159f * i / segments;
		float x = this->radius * cos(angle);
		float y = this->radius * sin(angle);
		vertices[i] = { Vector3(x, y, 0.0f), RGB_RED, RGB_BLUE };
	}

	vertices[segments] = { Vector3(0.0f), RGB_RED, RGB_BLUE };

	for (int i = 0; i < segments; i++) {
		indices[i * 3] = (i + 1) % segments;
		indices[(i * 3) + 1] = i;
		indices[(i * 3) + 2] = segments;
	}

	this->vertexBuffer = GraphicsEngine::CreateVertexBuffer();
	UINT vertexListSize = ARRAYSIZE(vertices);

	this->indexBuffer = GraphicsEngine::CreateIndexBuffer();
	UINT indexListSize = ARRAYSIZE(indices);

	this->vertexBuffer->Load(vertices, sizeof(Vertex), vertexListSize, shaderBytes, shaderSize);
	this->indexBuffer->Load(indices, indexListSize);

	Constant cc = Constant();
	cc.time = 0;

	this->constantBuffer = GraphicsEngine::CreateConstantBuffer();
	this->constantBuffer->Load(&cc, sizeof(Constant));
}

Circle::~Circle()
{

}

void Circle::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += this->deltaTime;

	Vector3 newPos = this->localPosition + (this->velocity * this->deltaTime);

	float right = 1.5f;
	float left = -1.5f;
	float top = 1.0f;
	float bottom = -1.0f;

	if (newPos.y > top - (this->radius * this->localScale.y) ||
		newPos.y < bottom + (this->radius * this->localScale.y))
		this->velocity.y *= -1;

	if (newPos.x > right - (this->radius * this->localScale.x) ||
		newPos.x < left + (this->radius * this->localScale.x))
		this->velocity.x *= -1;
	
	newPos = this->localPosition + (this->velocity * this->deltaTime);
	this->localPosition = newPos;

	this->transform.SetIdentity();
	this->transform.SetScale(this->localScale);
	this->transform.SetPosition(this->localPosition);
}

void Circle::Draw()
{
	Constant cc = Constant();
	cc.time = this->ticks;
	cc.world = this->transform;
	cc.view = SceneCameraHandler::GetViewMatrix();
	cc.proj = SceneCameraHandler::GetProjectionMatrix();

	this->constantBuffer->Update(GraphicsEngine::GetImmediateDeviceContext(), &cc);
	GraphicsEngine::GetImmediateDeviceContext()->SetConstantBuffer(this->vertexShader, this->constantBuffer);
	GraphicsEngine::GetImmediateDeviceContext()->SetConstantBuffer(this->pixelShader, this->constantBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->SetVertexShader(this->vertexShader);
	GraphicsEngine::GetImmediateDeviceContext()->SetPixelShader(this->pixelShader);

	GraphicsEngine::GetImmediateDeviceContext()->SetVertexBuffer(this->vertexBuffer);
	GraphicsEngine::GetImmediateDeviceContext()->SetIndexBuffer(this->indexBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->DrawIndexedTriangleList(this->indexBuffer->GetIndexListSize(), 0, 0);
}

void Circle::Release()
{
	this->vertexBuffer->Release();
	this->indexBuffer->Release();
	this->constantBuffer->Release();

	delete this;
}

void Circle::SetVelocity(Vector3 velocity)
{
	this->velocity = velocity;
}
