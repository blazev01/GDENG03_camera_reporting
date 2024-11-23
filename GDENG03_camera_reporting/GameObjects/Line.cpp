#include "Line.h"
#include "../Math/Colors.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../SceneCamera/SceneCameraHandler.h"

Line::Line(std::string name, void* shaderBytes, size_t shaderSize, const Vector3D& startPos, const Vector3D& endPos) : GameObject(name)
{
	Vertex vertices[] =
	{
		{startPos, Vector2D(), RGBA_RED},
		{endPos, Vector2D(), RGBA_BLUE}
	};

	this->vertexBuffer = GraphicsEngine::CreateVertexBuffer();
	UINT vertexListSize = ARRAYSIZE(vertices);

	this->vertexBuffer->Load(vertices, sizeof(Vertex), ARRAYSIZE(vertices), shaderBytes, shaderSize);

	Constant cc = Constant();
	cc.time = 0;

	this->constantBuffer = GraphicsEngine::CreateConstantBuffer();
	this->constantBuffer->Load(&cc, sizeof(Constant));


	this->localPosition = Vector3D(0);
	this->localRotation = Vector3D(0);
	this->localScale = Vector3D(1);
}

Line::~Line()
{

}

void Line::Update(float deltaTime)
{
	//this->deltaTime = deltaTime;
	////this->ticks += deltaTime;

	//this->transform.SetIdentity();
	//Matrix4x4 temp;

	//temp.SetIdentity();
	//temp.SetRotationZ(this->localRotation.z);
	//this->transform *= temp;

	//temp.SetIdentity();
	//temp.SetRotationY(this->localRotation.y);
	//this->transform *= temp;

	//temp.SetIdentity();
	//temp.SetRotationX(this->localRotation.x);
	//this->transform *= temp;

	//temp.SetIdentity();
	//temp.SetScale(this->localScale);
	//this->transform *= temp;

	//temp.SetIdentity();
	//temp.SetPosition(this->localPosition);
	//this->transform *= temp;

	this->SetTransform(((Camera*)parent)->GetTransform());
	
	//this->transform *= parent->GetTransform();
}

void Line::Draw(Matrix4x4 view, Matrix4x4 proj)
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

	GraphicsEngine::GetImmediateDeviceContext()->DrawLineStrip(this->vertexBuffer->GetVertexListSize(), 0);
}

void Line::Destroy()
{
	this->vertexBuffer->Release();
	this->constantBuffer->Release();

	delete this;
}

void Line::SetParent(GameObject* parent)
{
	this->parent = parent;
}
