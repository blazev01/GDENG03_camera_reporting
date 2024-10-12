#include "Cube.h"
#include "../GraphicsEngine/Structs.h"
#include "../Math/Colors.h"
#include "../GraphicsEngine/GraphicsEngine.h"

Cube::Cube(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name)
{
	Vertex vertices[] =
	{
		{Vector3(-0.5f, -0.5f, -0.5f), RGB_RED, RGB_MAGENTA},
		{Vector3(-0.5f,  0.5f, -0.5f), RGB_GREEN, RGB_YELLOW},
		{Vector3(0.5f,  0.5f, -0.5f), RGB_BLUE, RGB_CYAN},
		{Vector3(0.5f, -0.5f, -0.5f), RGB_CYAN, RGB_BLUE},
		{Vector3(0.5f, -0.5f,  0.5f), RGB_YELLOW, RGB_GREEN},
		{Vector3(0.5f,  0.5f,  0.5f), RGB_MAGENTA, RGB_RED},
		{Vector3(-0.5f,  0.5f,  0.5f), RGB_WHITE, RGB_BLACK},
		{Vector3(-0.5f, -0.5f,  0.5f), RGB_BLACK, RGB_WHITE},
	};

	this->vertexBuffer = GraphicsEngine::GetInstance()->CreateVertexBuffer();
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

	this->indexBuffer = GraphicsEngine::GetInstance()->CreateIndexBuffer();
	UINT indexListSize = ARRAYSIZE(indices);

	this->vertexBuffer->Load(vertices, sizeof(Vertex), ARRAYSIZE(vertices), shaderBytes, shaderSize);
	this->indexBuffer->Load(indices, ARRAYSIZE(indices));

	Constant cc = Constant();
	cc.time = 0;

	this->constantBuffer = GraphicsEngine::GetInstance()->CreateConstantBuffer();
	this->constantBuffer->Load(&cc, sizeof(Constant));
}

Cube::~Cube()
{

}

void Cube::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->totalTime += deltaTime;

	this->deltaRot += this->deltaTime * this->speed;

	this->transform.SetIdentity();
	Matrix4x4 temp;
	/*
	temp.SetRotationX((-0.1f * (1.0f - this->deltaRot)) + (0.1f * this->deltaRot));
	this->transform *= temp;

	temp.SetRotationY((-0.1f * (1.0f - this->deltaRot)) + (0.1f * this->deltaRot));
	this->transform *= temp;

	temp.SetRotationZ((-0.1f * (1.0f - this->deltaRot)) + (0.1f * this->deltaRot));
	this->transform *= temp;
	*/
	temp.SetRotationX(this->localRotation.x);
	this->transform *= temp;

	temp.SetRotationY(this->localRotation.y);
	this->transform *= temp;

	temp.SetRotationZ(this->localRotation.z);
	this->transform *= temp;

	temp.SetScale(this->localScale);
	this->transform *= temp;

	temp.SetTranslation(this->localPosition);
	this->transform *= temp;

	//this->SetRotation(Vector3::Lerp(this->localRotation, Vector3(5.0f), (sinf(this->deltaRot) + 1.0f) / 2.0f));
}

void Cube::Draw(int width, int height, VertexShader * vertexShader, PixelShader * pixelShader)
{
	Constant cc = Constant();
	cc.time = this->totalTime;
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
