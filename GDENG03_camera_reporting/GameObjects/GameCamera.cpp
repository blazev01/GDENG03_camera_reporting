#include "GameCamera.h"
#include "../SceneCamera/SceneCameraHandler.h"
GameCamera::GameCamera(std::string name, SwapChain* swapChain, void* shaderBytes, size_t shaderSize):Camera(name,swapChain)
{
	Vector3D posList[] =
	{
		{ Vector3D(-0.25f,-0.25f,-1.0f)},
		{ Vector3D(-0.25f,0.25f,-1.0f) },
		{ Vector3D(0.25f,0.25f,-1.0f) },
		{ Vector3D(0.25f,-0.25f,-1.0f) },

		{ Vector3D(0.25f,-0.25f,-0.25f) },
		{ Vector3D(0.25f,0.25f,-0.25f) },
		{ Vector3D(-0.25f,0.25f,-0.25f) },
		{ Vector3D(-0.25f,-0.25f,-0.25f) },

		{ Vector3D(-0.25f,-0.25f,0.0f) },
		{ Vector3D(-0.25f,0.25f,0.0f) },
		{ Vector3D(0.25f,0.25f,0.0f) },
		{ Vector3D(0.25f,-0.25f,0.0f) },
		{ Vector3D(0.0f,0.0f,-0.5f) }
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
		//FRONT
		{ posList[0], texcoordList[1], RGBA_BLACK },
		{ posList[1], texcoordList[0], RGBA_GREY },
		{ posList[2], texcoordList[2], RGBA_GREY },
		{ posList[3], texcoordList[3], RGBA_BLACK },
		//BACK
		{ posList[4], texcoordList[1], RGBA_BLACK },
		{ posList[5], texcoordList[0], RGBA_GREY },
		{ posList[6], texcoordList[2], RGBA_GREY },
		{ posList[7], texcoordList[3], RGBA_BLACK },

		{ posList[1], texcoordList[1], RGBA_BLACK },
		{ posList[6], texcoordList[0], RGBA_GREY },
		{ posList[5], texcoordList[2], RGBA_GREY },
		{ posList[2], texcoordList[3], RGBA_BLACK },

		{ posList[7], texcoordList[1], RGBA_BLACK },
		{ posList[0], texcoordList[0], RGBA_GREY },
		{ posList[3], texcoordList[2], RGBA_GREY },
		{ posList[4], texcoordList[3], RGBA_BLACK },

		{ posList[3], texcoordList[1], RGBA_BLACK },
		{ posList[2], texcoordList[0], RGBA_GREY },
		{ posList[5], texcoordList[2], RGBA_GREY },
		{ posList[4], texcoordList[3], RGBA_BLACK },

		{ posList[7], texcoordList[1], RGBA_BLACK },
		{ posList[6], texcoordList[0], RGBA_GREY },
		{ posList[1], texcoordList[2], RGBA_GREY },
		{ posList[0], texcoordList[3], RGBA_BLACK },
		//PYRAMID BACK
		{ posList[11], texcoordList[1], RGBA_GREY },
		{ posList[10], texcoordList[0], RGBA_GREY },
		{ posList[9], texcoordList[2], RGBA_GREY },
		{ posList[8], texcoordList[3], RGBA_GREY },

		{ posList[8], texcoordList[1], RGBA_GREY },
		{ posList[9], texcoordList[0], RGBA_GREY },
		{ posList[12], texcoordList[2], RGBA_BLACK },
		
		{ posList[9], texcoordList[1], RGBA_GREY },
		{ posList[10], texcoordList[0], RGBA_GREY },
		{ posList[12], texcoordList[2], RGBA_BLACK },
		
		{ posList[10], texcoordList[1], RGBA_GREY },
		{ posList[11], texcoordList[0], RGBA_GREY },
		{ posList[12], texcoordList[2], RGBA_BLACK },
		
		{ posList[11], texcoordList[1], RGBA_GREY },
		{ posList[8], texcoordList[0], RGBA_GREY },
		{ posList[12], texcoordList[2], RGBA_BLACK }
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
		22,23,20,

		24,25,26,
		26,27,24,

		28,29,30,

		31,32,33,

		34,35,36,

		37,38,39
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

void GameCamera::Update(float deltaTime)
{
	
}

void GameCamera::Draw(Matrix4x4 view, Matrix4x4 proj)
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
	GraphicsEngine::GetImmediateDeviceContext()->SetIndexBuffer(this->indexBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->DrawIndexedTriangleList(this->indexBuffer->GetIndexListSize(), 0, 0);
}


void GameCamera::Destroy()
{
	GameObject::Destroy();

	this->viewTexture->Release();
	this->vertexBuffer->Release();
	this->indexBuffer->Release();
	this->constantBuffer->Release();

	delete this;
}

GameCamera::~GameCamera()
{

}
