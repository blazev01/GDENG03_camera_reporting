#include "Quad.h"
#include "../Math/Colors.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../SceneCamera/SceneCameraHandler.h"

Quad::Quad(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name)
{
	Vertex vertices[] =
	{
		{Vector3(-0.5f, -0.5f, 0.0f), RGB_WHITE, RGB_WHITE},
		{Vector3(-0.5f,  0.5f, 0.0f), RGB_WHITE, RGB_WHITE},
		{Vector3(0.5f, -0.5f, 0.0f), RGB_WHITE, RGB_WHITE},
		{Vector3(0.5f,  0.5f, 0.0f), RGB_WHITE, RGB_WHITE},
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

	this->transform.SetIdentity();
	Matrix4x4 temp;

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

	GraphicsEngine::GetImmediateDeviceContext()->SetVertexBuffer(this->vertexBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->DrawTriangleStrip(this->vertexBuffer->GetVertexListSize(), 0);
}

void Quad::Release()
{
	this->vertexBuffer->Release();
	this->constantBuffer->Release();

	delete this;
}
