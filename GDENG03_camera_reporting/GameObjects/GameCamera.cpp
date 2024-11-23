#include "GameCamera.h"
#include "../SceneCamera/SceneCameraHandler.h"
GameCamera::GameCamera(std::string name, SwapChain* swapChain, void* shaderBytes, size_t shaderSize):Camera(name,swapChain)
{
	Vector3D posList[] =
	{
		{ Vector3D(-0.5f,-0.5f,-0.5f)},
		{ Vector3D(-0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,0.5f,-0.5f) },
		{ Vector3D(0.5f,-0.5f,-0.5f) },

		{ Vector3D(0.5f,-0.5f,0.5f) },
		{ Vector3D(0.5f,0.5f,0.5f) },
		{ Vector3D(-0.5f,0.5f,0.5f) },
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
		{ posList[0], texcoordList[1], RGBA_GREY },
		{ posList[1], texcoordList[0], RGBA_GREY },
		{ posList[2], texcoordList[2], RGBA_GREY },
		{ posList[3], texcoordList[3], RGBA_GREY },

		{ posList[4], texcoordList[1], RGBA_GREY },
		{ posList[5], texcoordList[0], RGBA_GREY },
		{ posList[6], texcoordList[2], RGBA_GREY },
		{ posList[7], texcoordList[3], RGBA_GREY },

		{ posList[1], texcoordList[1], RGBA_GREY },
		{ posList[6], texcoordList[0], RGBA_GREY },
		{ posList[5], texcoordList[2], RGBA_GREY },
		{ posList[2], texcoordList[3], RGBA_GREY },

		{ posList[7], texcoordList[1], RGBA_GREY },
		{ posList[0], texcoordList[0], RGBA_GREY },
		{ posList[3], texcoordList[2], RGBA_GREY },
		{ posList[4], texcoordList[3], RGBA_GREY },

		{ posList[3], texcoordList[1], RGBA_GREY },
		{ posList[2], texcoordList[0], RGBA_GREY },
		{ posList[5], texcoordList[2], RGBA_GREY },
		{ posList[4], texcoordList[3], RGBA_GREY },

		{ posList[7], texcoordList[1], RGBA_GREY },
		{ posList[6], texcoordList[0], RGBA_GREY },
		{ posList[1], texcoordList[2], RGBA_GREY },
		{ posList[0], texcoordList[3], RGBA_GREY }
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
}

void GameCamera::Update(float deltaTime)
{
	if (isActive)
	{
		/*if (InputSystem::IsKeyDown(VK_RBUTTON))
		{
			std::cout << "RMB HELD" << "\n";
			InputSystem::ShowCursor(false);
		}
		else if (InputSystem::IsKeyUp(VK_RBUTTON))
		{
			std::cout << "RMB RELEASED" << "\n";
			InputSystem::ShowCursor(true);
		}

		if (InputSystem::IsKey(VK_RBUTTON))
		{
			Vector2 mousePos = InputSystem::GetCursorPosition();
			InputSystem::SetCursorPosition(this->swapChain->GetWidth() / 2.0f, this->swapChain->GetHeight() / 2.0f);

			if (mousePos != this->oldMousePos)
			{
				this->localRotation.x += (mousePos.y - (this->swapChain->GetHeight() / 2.0f)) * deltaTime * 0.2f;
				this->localRotation.y += (mousePos.x - (this->swapChain->GetWidth() / 2.0f)) * deltaTime * 0.2f;
				this->oldMousePos = mousePos;

			}
		}*/

		/*if (InputSystem::IsKey('W'))
		{
			std::cout << "W" << "\n";
			this->localPosition -= this->speed * deltaTime * this->GetForward();
		}

		if (InputSystem::IsKey('S'))
		{
			std::cout << "S" << "\n";
			this->localPosition += this->speed * deltaTime * this->GetForward();


		}

		if (InputSystem::IsKey('A'))
		{
			std::cout << "A" << "\n";
			this->localPosition -= this->speed * deltaTime * this->GetRight();
		}

		if (InputSystem::IsKey('D'))
		{
			std::cout << "D" << "\n";
			this->localPosition += this->speed * deltaTime * this->GetRight();
		}

		if (InputSystem::IsKey('Q'))
		{
			std::cout << "Q" << "\n";
			this->localPosition.y -= this->speed * deltaTime;
		}

		if (InputSystem::IsKey('E'))
		{
			std::cout << "E" << "\n";
			this->localPosition.y += this->speed * deltaTime;
		}*/
	}
	/*
	Matrix4x4 temp;
	Matrix4x4 temp2;
	this->transform.SetIdentity();
	this->gameCameraTransforms.SetIdentity();

	temp.SetIdentity();
	temp2.SetIdentity();
	temp.SetRotationX(this->localRotation.x);
	temp2.SetRotationX(this->localRotation.x);
	this->transform *= temp;
	this->gameCameraTransforms *= temp2;


	temp.SetIdentity();
	temp2.SetIdentity();
	temp.SetRotationY(this->localRotation.y);
	temp2.SetRotationY(this->localRotation.y);
	this->transform *= temp;
	this->gameCameraTransforms *= temp2;

	
	this->transform.SetPosition(this->localPosition);
	this->gameCameraTransforms.SetPosition(this->localPosition);


	this->transform.Inverse();*/
}

void GameCamera::Draw(Matrix4x4 view, Matrix4x4 proj)
{
	Constant cc = Constant();
	cc.time = this->ticks;
	cc.world = this->gameCameraTransforms;
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
	Camera::Destroy();
}

void GameCamera::SetActive(bool isActive)
{
	this->isActive = isActive;
}

GameCamera::~GameCamera()
{

}
