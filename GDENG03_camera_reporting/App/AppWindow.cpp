#include "AppWindow.h"
#include "Windows.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../EngineTime/EngineTime.h"
#include "../InputSystem/InputSystem.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../GameObjects/GameObjectManager.h"
#include "../GameObjects/RenderQueue.h"
#include "../UI/UIManager.h"

AppWindow::AppWindow()
{
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

	RECT rect = this->GetWindowRect();

	float width = rect.right - rect.left;
	float height = rect.bottom - rect.top;

	SceneCameraHandler::Initialize(width, height);
	GameObjectManager::Initialize();
	RenderQueue::Initialize();
	UIManager::Initialize(this->hwnd);

	SwapChain* swapChain1 = GraphicsEngine::CreateSwapChain();
	swapChain1->Init(this->hwnd, width, height, false);
	SceneCameraHandler::CreateNewCamera(swapChain1);
	
	SwapChain* swapChain2 = GraphicsEngine::CreateSwapChain();
	swapChain2->Init(this->hwnd, width, height);
	SceneCameraHandler::CreateNewCamera(swapChain2);
	
	SwapChain* swapChain3 = GraphicsEngine::CreateSwapChain();
	swapChain3->Init(this->hwnd, width, height);
	SceneCameraHandler::CreateNewCamera(swapChain3);

	std::bitset<4> cullingMask1 = SceneCameraHandler::GetCamera(0)->GetCullingMask();
	std::bitset<4> cullingMask2 = SceneCameraHandler::GetCamera(0)->GetCullingMask();
	cullingMask1[0] = false;
	cullingMask2[1] = false;
	SceneCameraHandler::GetCamera(1)->SetCullingMask(cullingMask1);
	SceneCameraHandler::GetCamera(2)->SetCullingMask(cullingMask2);

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
	Cube* gameCube = new Cube("Camera Indicator", this->vsBytes, this->vsSize);
	gameCube->SetScale(Vector3(1.f));
	gameCube->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	gameCube->SetVertexShader(this->vertexShader);
	gameCube->SetPixelShader(this->pixelShader);
	gameCube->SetPriority(0);
	gameCube->SetLayer(0);


	SceneCameraHandler::CreateGameCamera(swapChain1,gameCube);
	SceneCameraHandler::GetSceneCamera()->SetWindowSize(width, height);
	SceneCameraHandler::GetSceneCamera()->SetPerspProjection(1.57f, width / height, 0.01f, 1000.0f);

	GameObjectManager::AddGameObject(gameCube);
	RenderQueue::AddRenderer(gameCube);
	for (int i = 0; i < 3; i++)
	{
		Cube* cube = new Cube("coob" + std::to_string(i), this->vsBytes, this->vsSize);
		cube->SetAnimationSpeed(0.0f);
		cube->SetScale(Vector3(0.5f));
		cube->SetPosition(Vector3(i - 1, 0.0f, i - 1));
		cube->SetVertexShader(this->vertexShader);
		cube->SetPixelShader(this->pixelShader);
		cube->SetPriority(1);
		if (i != 1) cube->SetLayer(1);

		GameObjectManager::AddGameObject(cube);
		RenderQueue::AddRenderer(cube);
	}
	
	for (int i = 0; i < 2; i++)
	{
		Quad* quad = new Quad("kwad" + std::to_string(i), this->vsBytes, this->vsSize);
		if (i == 0) quad->SetRotation(1.5708f, 0.0f, 0.0f);
		else quad->SetRotation(-1.5708f, 0.0f, 0.0f);
		quad->SetScale(Vector3(4.0f));
		quad->SetVertexShader(this->vertexShader);
		quad->SetPixelShader(this->pixelShader);
		quad->SetLayer(1);

		GameObjectManager::AddGameObject(quad);
		RenderQueue::AddRenderer(quad);
	}
}

void AppWindow::OnUpdate()
{
	InputSystem::Update();
	SceneCameraHandler::Update();
	GameObjectManager::Update();

	SceneCameraHandler::Draw();
	UIManager::DrawAllUI();
	SceneCameraHandler::Present();
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
	this->vertexShader->Release();
	this->pixelShader->Release();

	GameObjectManager::Release();
	GraphicsEngine::Release();
	SceneCameraHandler::Release();
}

void AppWindow::OnKey(int key)
{
	
}

void AppWindow::OnKeyDown(int key)
{
	switch (key)
	{
	case 'V':
	{
		GameObject* cube = GameObjectManager::FindGameObject("coob2");
		if (cube->GetPriority() == -1) cube->SetPriority(1);
		else cube->SetPriority(-1);
		break;
	}
	case VK_SPACE:
	{
		std::cout << "SPACE" << "\n";
		//this->SpawnCircles();
		SceneCameraHandler::SwitchCameraType();
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
