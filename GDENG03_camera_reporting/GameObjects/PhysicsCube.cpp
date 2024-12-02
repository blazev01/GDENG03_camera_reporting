#include "PhysicsCube.h"
#include "../Math/Colors.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../Resource/TextureManager.h"
#include "../Components/PhysicsComponent.h"

PhysicsCube::PhysicsCube(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name, PHYSICS_CUBE)
{
	Vector3D posList[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f)},

		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f)},
		{ Vector3D(-0.5f,-0.5f,0.5f) }
	};

	Vector2D texcoordList[] =
	{
		{ Vector2D(0.0f,0.0f) },
		{ Vector2D(0.0f,1.0f) },
		{ Vector2D(1.0f,0.0f) },
		{ Vector2D(1.0f,1.0f) }
	};

	Vertex vertices[] =
	{
		{ posList[0], texcoordList[1], RGBA_RED },
		{ posList[1], texcoordList[0], RGBA_RED },
		{ posList[2], texcoordList[2], RGBA_YELLOW },
		{ posList[3], texcoordList[3], RGBA_YELLOW },


		{ posList[4], texcoordList[1], RGBA_GREEN },
		{ posList[5], texcoordList[0], RGBA_GREEN },
		{ posList[6], texcoordList[2], RGBA_BLUE },
		{ posList[7], texcoordList[3], RGBA_BLUE },


		{ posList[1], texcoordList[1], RGBA_RED },
		{ posList[6], texcoordList[0], RGBA_RED },
		{ posList[5], texcoordList[2], RGBA_RED },
		{ posList[2], texcoordList[3], RGBA_RED },

		{ posList[7], texcoordList[1], RGBA_RED },
		{ posList[0], texcoordList[0], RGBA_RED },
		{ posList[3], texcoordList[2], RGBA_RED },
		{ posList[4], texcoordList[3], RGBA_RED },

		{ posList[3], texcoordList[1], RGBA_RED },
		{ posList[2], texcoordList[0], RGBA_RED },
		{ posList[5], texcoordList[2], RGBA_RED },
		{ posList[4], texcoordList[3], RGBA_RED },

		{ posList[7], texcoordList[1], RGBA_RED },
		{ posList[6], texcoordList[0], RGBA_RED },
		{ posList[1], texcoordList[2], RGBA_RED },
		{ posList[0], texcoordList[3], RGBA_RED }
	};

	this->vertexBuffer = GraphicsEngine::CreateVertexBuffer();
	UINT vertexListSize = ARRAYSIZE(vertices);

	unsigned int indices[] =
	{
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		8,9,10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20
	};

	this->indexBuffer = GraphicsEngine::CreateIndexBuffer();
	UINT indexListSize = ARRAYSIZE(indices);

	this->vertexBuffer->Load(vertices, sizeof(Vertex), ARRAYSIZE(vertices), shaderBytes, shaderSize);
	this->indexBuffer->Load(indices, ARRAYSIZE(indices));

	Constant cc = Constant();
	cc.time = 0;

	this->constantBuffer = GraphicsEngine::CreateConstantBuffer();
	this->constantBuffer->Load(&cc, sizeof(Constant));

	this->SetPosition(Vector3D(0, 10, 0));
	
}

PhysicsCube::~PhysicsCube()
{

}

void PhysicsCube::Awake()
{
	PhysicsComponent* component = new PhysicsComponent("RigidBody", this);
	this->AttachComponent(component);
	std::cout << this->transform.mat[1][1] << "\n";

	Transform transform;
	transform.setFromOpenGL(this->transform.GetAs1DArray());
	component->GetRigidBody()->setTransform(transform);
}

void PhysicsCube::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
}

void PhysicsCube::Draw(Matrix4x4 view, Matrix4x4 proj)
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
	GraphicsEngine::GetImmediateDeviceContext()->SetIndexBuffer(this->indexBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->DrawIndexedTriangleList(this->indexBuffer->GetIndexListSize(), 0, 0);
}

void PhysicsCube::Destroy()
{
	GameObject::Destroy();

	this->vertexBuffer->Release();
	this->indexBuffer->Release();
	this->constantBuffer->Release();

	delete this;
}

void PhysicsCube::SetAnimationSpeed(float speed)
{
	this->speed = speed;
}
