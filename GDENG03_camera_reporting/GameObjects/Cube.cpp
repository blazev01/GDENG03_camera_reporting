#include "Cube.h"
#include "../Math/Colors.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../SceneCamera/SceneCameraHandler.h"

Cube::Cube(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name)
{
	Vertex vertices[] =
	{
		{Vector3(-0.5f, -0.5f, -0.5f), RGB_RED, RGB_RED},
		{Vector3(-0.5f,  0.5f, -0.5f), RGB_YELLOW, RGB_YELLOW},
		{Vector3(0.5f,  0.5f, -0.5f), RGB_YELLOW, RGB_YELLOW},
		{Vector3(0.5f, -0.5f, -0.5f), RGB_RED, RGB_RED},
		{Vector3(0.5f, -0.5f,  0.5f), RGB_GREEN, RGB_GREEN},
		{Vector3(0.5f,  0.5f,  0.5f), RGB_CYAN, RGB_CYAN},
		{Vector3(-0.5f,  0.5f,  0.5f), RGB_CYAN, RGB_CYAN},
		{Vector3(-0.5f, -0.5f,  0.5f), RGB_GREEN, RGB_GREEN},
	};

	this->vertexBuffer = GraphicsEngine::CreateVertexBuffer();
	UINT vertexListSize = ARRAYSIZE(vertices);

	unsigned int indices[] =
	{
		0, 1, 2,	2, 3, 0,
		4, 5, 6,	6, 7, 4,
		1, 6, 5,	5, 2, 1,
		7, 0, 3,	3, 4, 7,
		3, 2, 5,	5, 4, 3,
		7, 6, 1,	1, 0, 7,
	};

	this->indexBuffer = GraphicsEngine::CreateIndexBuffer();
	UINT indexListSize = ARRAYSIZE(indices);

	this->vertexBuffer->Load(vertices, sizeof(Vertex), ARRAYSIZE(vertices), shaderBytes, shaderSize);
	this->indexBuffer->Load(indices, ARRAYSIZE(indices));

	Constant cc = Constant();
	cc.time = 0;

	this->constantBuffer = GraphicsEngine::CreateConstantBuffer();
	this->constantBuffer->Load(&cc, sizeof(Constant));
}

Cube::~Cube()
{

}

void Cube::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	//this->ticks += deltaTime * this->speed;

	this->deltaRot += this->deltaTime * this->speed;

	this->transform.SetIdentity();
	Matrix4x4 temp;
	/*
	temp.SetIdentity();
	temp.SetRotationZ((-0.1f * (1.0f - this->deltaRot)) + (0.1f * this->deltaRot));
	this->transform *= temp;

	temp.SetIdentity();
	temp.SetRotationY((-0.1f * (1.0f - this->deltaRot)) + (0.1f * this->deltaRot));
	this->transform *= temp;

	temp.SetIdentity();
	temp.SetRotationX((-0.1f * (1.0f - this->deltaRot)) + (0.1f * this->deltaRot));
	this->transform *= temp;
	*/

	temp.SetIdentity();
	temp.SetRotationZ(this->localRotation.z);
	this->transform *= temp;

	temp.SetIdentity();
	temp.SetRotationY(this->localRotation.y);
	this->transform *= temp;

	temp.SetIdentity();
	temp.SetRotationX(this->localRotation.x);
	this->transform *= temp;

	temp.SetIdentity();
	temp.SetScale(this->localScale);
	this->transform *= temp;

	temp.SetIdentity();
	temp.SetPosition(this->localPosition);
	this->transform *= temp;
}

void Cube::Draw(VertexShader * vertexShader, PixelShader * pixelShader)
{
	Constant cc = Constant();
	cc.time = this->ticks;
	cc.world = this->transform;
	cc.view = SceneCameraHandler::GetViewMatrix();
	cc.proj = SceneCameraHandler::GetProjectionMatrix();

	this->constantBuffer->Update(GraphicsEngine::GetImmediateDeviceContext(), &cc);
	GraphicsEngine::GetImmediateDeviceContext()->SetConstantBuffer(vertexShader, this->constantBuffer);
	GraphicsEngine::GetImmediateDeviceContext()->SetConstantBuffer(pixelShader, this->constantBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->SetVertexShader(vertexShader);
	GraphicsEngine::GetImmediateDeviceContext()->SetPixelShader(pixelShader);

	GraphicsEngine::GetImmediateDeviceContext()->SetVertexBuffer(this->vertexBuffer);
	GraphicsEngine::GetImmediateDeviceContext()->SetIndexBuffer(this->indexBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->DrawIndexedTriangleList(this->indexBuffer->GetIndexListSize(), 0, 0);
}

void Cube::Release()
{
	this->vertexBuffer->Release();
	this->indexBuffer->Release();
	this->constantBuffer->Release();

	delete this;
}

void Cube::SetAnimationSpeed(float speed)
{
	this->speed = speed;
}
