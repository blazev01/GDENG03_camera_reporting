#include "AppWindow.h"
#include "Windows.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../EngineTime/EngineTime.h"
#include "../InputSystem/InputSystem.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../GameObjects/GameObjectManager.h"

AppWindow::AppWindow()
{
	this->swapChain = NULL;
	this->vertexShader = NULL;
	this->pixelShader = NULL;
	this->cube = NULL;
}

AppWindow::~AppWindow()
{

}

void AppWindow::OnCreate()
{
	InputSystem::Initialize();
	EngineTime::Initialize();
	GraphicsEngine::Initialize();
	SceneCameraHandler::Initialize();
	GameObjectManager::Initialize();

	this->swapChain = GraphicsEngine::CreateSwapChain();

	RECT rect = this->GetWindowRect();
	this->swapChain->Init(this->hwnd, rect.right - rect.left, rect.bottom - rect.top);

	float width = this->GetWindowRect().right - this->GetWindowRect().left;
	float height = this->GetWindowRect().bottom - this->GetWindowRect().top;

	SceneCameraHandler::CreateNewCamera(width, height);
	SceneCameraHandler::CreateNewCamera(width, height);
	SceneCameraHandler::CreateNewCamera(width, height);
	//SceneCameraHandler::GetSceneCamera()->SetWindowSize(width, height);
	//SceneCameraHandler::SetOrthoProjection(width / 300.0f, height / 300.0f, -4.0f, 4.0f);
	//SceneCameraHandler::GetSceneCamera()->SetPerspProjection(1.57f, width / height, 0.01f, 1000.0f);
	
	void* shaderBytes = nullptr;
	size_t shaderSize = 0;

	GraphicsEngine::CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderBytes, &shaderSize);
	this->vertexShader = GraphicsEngine::CreateVertexShader(shaderBytes, shaderSize);

	this->vsBytes = shaderBytes;
	this->vsSize = shaderSize;

	GraphicsEngine::CompilePixelShader(L"PixelShader.hlsl", "psmain", &shaderBytes, &shaderSize);
	this->pixelShader = GraphicsEngine::CreatePixelShader(shaderBytes, shaderSize);

	GraphicsEngine::ReleaseCompiledShader();

	Cube* cube = new Cube("coob", this->vsBytes, this->vsSize);
	cube->SetAnimationSpeed(0.0f);
	cube->SetScale(Vector3(0.5f));
	GameObjectManager::AddGameObject(cube);

	Quad* quad = new Quad("kwad", this->vsBytes, this->vsSize);
	quad->SetRotation(1.5708f, 0.0f, 0.0f);
	quad->SetScale(Vector3(4.0f));
	GameObjectManager::AddGameObject(quad);

	this->camPos = Vector3(0.0f, 0.0f, -2.0f);
}

void AppWindow::OnUpdate()
{
	InputSystem::Update();
	SceneCameraHandler::Update();
	GameObjectManager::Update();
}

void AppWindow::OnRender()
{
	GraphicsEngine::GetImmediateDeviceContext()->ClearRenderTargetColor(this->swapChain, 0.0f, 0.45f, 0.5f, 1.0f);

	RECT rect = this->GetWindowRect();
	GraphicsEngine::GetImmediateDeviceContext()->SetViewportSize(rect.right - rect.left, rect.bottom - rect.top);

	GameObjectManager::Draw(this->vertexShader, this->pixelShader);

	this->swapChain->Present(true);
}

void AppWindow::OnFocus()
{
	InputSystem::AddListener(this);
	InputSystem::SetEnabled(true);
}

void AppWindow::OnKillFocus()
{
	InputSystem::RemoveListener(this);
	InputSystem::SetEnabled(false);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	this->swapChain->Release();
	this->vertexShader->Release();
	this->pixelShader->Release();

	GameObjectManager::Release();
	GraphicsEngine::Release();
}

void AppWindow::OnKey(int key)
{
	
}

void AppWindow::OnKeyDown(int key)
{
	switch (key)
	{
	case VK_SPACE:
	{
		std::cout << "SPACE" << "\n";
		this->SpawnCircles();
		break;
	}
	case VK_BACK:
	{
		std::cout << "BACKSPACE" << "\n";
		this->DespawnCircles();
		break;
	}
	case VK_DELETE:
	{
		std::cout << "DELETE" << "\n";
		this->DespawnAllCircles();
		break;
	}
	case VK_ESCAPE:
	{
		std::cout << "ESCAPE" << "\n";
		exit(0);
		break;
	}
	case VK_OEM_PERIOD:
		std::cout << "Greater Than" << std::endl;
		SceneCameraHandler::SwitchNextCamera();
		break;
	case VK_OEM_COMMA:
		std::cout << "Less Than" << std::endl;
		SceneCameraHandler::SwitchPrevCamera();
		break;
	default:
		break;
	}
}

void AppWindow::OnKeyUp(int key)
{

}

void AppWindow::OnMouseMove(const Vector2& deltaMousePos)
{
	
}

void AppWindow::OnMouseButton(int button)
{
	
}

void AppWindow::OnMouseButtonDown(int button)
{
	
}

void AppWindow::OnMouseButtonUp(int button)
{
	
}

void AppWindow::SpawnCircles()
{
	int size = this->circles.size();
	for (int i = size; i < size + this->spawnSize; i++)
	{
		Circle* circle = new Circle("circle", this->vsBytes, this->vsSize);
		circle->SetScale(Vector3(0.2f));
		circle->SetVelocity(Vector3(sinf(rand()), sinf(rand()), 0.0f));

		this->circles.push_back(circle);
		GameObjectManager::AddGameObject(circle);
	}
}

void AppWindow::DespawnCircles()
{
	if (!this->circles.empty())
	{
		int size = this->circles.size();
		for (int i = size - 1; i >= size - this->spawnSize; i--)
		{
			GameObjectManager::DeleteGameObject(this->circles[i]);
			this->circles.pop_back();
		}
	}
}

void AppWindow::DespawnAllCircles()
{
	if (!this->circles.empty())
	{
		int size = this->circles.size();
		for (int i = size - 1; i >= 0; i--)
		{
			GameObjectManager::DeleteGameObject(this->circles[i]);
			this->circles.pop_back();
			
		}
	}
}
