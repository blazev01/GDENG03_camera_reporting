#include "Quad.h"
#include "../GraphicsEngine/Structs.h"
#include "../Math/Colors.h"
#include "../GraphicsEngine/GraphicsEngine.h"

Quad::Quad(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name)
{
	Vertex vertices[] =
	{
		{Vector3(-0.5f, -0.5f, 0.0f), RGB_RED, RGB_MAGENTA},
		{Vector3(-0.5f,  0.5f, 0.0f), RGB_RED, RGB_MAGENTA},
		{Vector3( 0.5f, -0.5f, 0.0f), RGB_RED, RGB_MAGENTA},
		{Vector3( 0.5f,  0.5f, 0.0f), RGB_RED, RGB_MAGENTA},
	};

	this->vertexBuffer = GraphicsEngine::GetInstance()->CreateVertexBuffer();
	UINT vertexListSize = ARRAYSIZE(vertices);

	this->vertexBuffer->Load(vertices, sizeof(Vertex), ARRAYSIZE(vertices), shaderBytes, shaderSize);

	Constant cc = Constant();
	cc.time = 0;

	this->constantBuffer = GraphicsEngine::GetInstance()->CreateConstantBuffer();
	this->constantBuffer->Load(&cc, sizeof(Constant));
}

Quad::~Quad()
{

}

void Quad::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->ticks += deltaTime;

	this->transform.SetIdentity();
	Matrix4x4 temp;

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
}

void Quad::Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
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

	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->DrawTriangleStrip(this->vertexBuffer->GetVertexListSize(), 0);
}

void Quad::Release()
{
	this->vertexBuffer->Release();
	this->constantBuffer->Release();

	delete this;
}
