#include "Circle.h"
#include "vector"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../Math/Colors.h"


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

	this->vertexBuffer = GraphicsEngine::GetInstance()->CreateVertexBuffer();
	UINT vertexListSize = ARRAYSIZE(vertices);

	this->indexBuffer = GraphicsEngine::GetInstance()->CreateIndexBuffer();
	UINT indexListSize = ARRAYSIZE(indices);

	this->vertexBuffer->Load(vertices, sizeof(Vertex), vertexListSize, shaderBytes, shaderSize);
	this->indexBuffer->Load(indices, indexListSize);

	Constant cc = Constant();
	cc.time = 0;

	this->constantBuffer = GraphicsEngine::GetInstance()->CreateConstantBuffer();
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
	Matrix4x4 temp;

	temp.SetScale(this->localScale);
	this->transform *= temp;

	temp.SetTranslation(this->localPosition);
	this->transform *= temp;
}

void Circle::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{
	Constant cc = Constant();
	cc.time = this->ticks;
	cc.world = this->transform;
	cc.view.SetIdentity();
	cc.proj.SetOrthoLH(width, height, -4.0f, 4.0f);

	this->constantBuffer->Update(GraphicsEngine::GetInstance()->GetImmediateDeviceContext(), &cc);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetConstantBuffer(vertexShader, this->constantBuffer);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetConstantBuffer(pixelShader, this->constantBuffer);

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexShader(vertexShader);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetPixelShader(pixelShader);

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetVertexBuffer(this->vertexBuffer);
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetIndexBuffer(this->indexBuffer);

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawIndexedTriangleList(this->indexBuffer->GetIndexListSize(), 0, 0);
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
