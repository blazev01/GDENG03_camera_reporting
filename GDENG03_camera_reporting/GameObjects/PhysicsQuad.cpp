#include "PhysicsQuad.h"
#include "../Math/Colors.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../Components/PhysicsComponent.h"

PhysicsQuad::PhysicsQuad(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name)
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

	//this->SetScale(Vector3D(4.0f));
	this->SetRotation(1.5708f, 0.0f, 0.0f);

	PhysicsComponent* component = new PhysicsComponent("Quad Physics", this);
	component->GetRigidBody()->setType(BodyType::STATIC);
	this->components.push_back(component);
}

PhysicsQuad::~PhysicsQuad()
{

}

void PhysicsQuad::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
}

void PhysicsQuad::Draw(Matrix4x4 view, Matrix4x4 proj)
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

	GraphicsEngine::GetImmediateDeviceContext()->SetVertexBuffer(this->vertexBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->DrawTriangleStrip(this->vertexBuffer->GetVertexListSize(), 0);
}

void PhysicsQuad::Destroy()
{
	GameObject::Destroy();

	this->vertexBuffer->Release();
	this->constantBuffer->Release();

	delete this;
}
