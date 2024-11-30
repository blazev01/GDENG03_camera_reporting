#include "AppWindow.h"
#include "Windows.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../EngineTime/EngineTime.h"
#include "../InputSystem/InputSystem.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../GameObjects/RenderQueue.h"
#include "../GameObjects/GameObjectManager.h"
#include "../GraphicsEngine/ShaderLibrary.h"
#include "../Resource/MeshManager.h"
#include "../Resource/TextureManager.h"
#include "../UI/UIManager.h"
#include "../Components/BaseComponentSystem.h"
#include "../GameObjects/PhysicsQuad.h"
#include "../GameObjects/PhysicsCube.h"
#include "../Backend/EngineBackend.h"
#include "../Backend/ActionHistory.h"
#include "../UI/GameObjectSpawner.h"
#include "../Backend/Debug.h"
#include "../SaveSystem/SaveSystem.h"

AppWindow::AppWindow()
{
	
}

AppWindow::~AppWindow()
{

}

void AppWindow::OnCreate()
{
	InputSystem::Initialize();
	EngineBackend::Initialize();
	EngineTime::Initialize();
	ActionHistory::Initialize();
	GraphicsEngine::Initialize();
	ShaderLibrary::Initialize();
	MeshManager::Initialize();
	TextureManager::Initialize();
	GameObjectManager::Initialize();
	BaseComponentSystem::Initialize();

	RECT rect = this->GetWindowRect();
	float width = rect.right - rect.left;
	float height = rect.bottom - rect.top;

	RenderQueue::Initialize();
	UIManager::Initialize(this->hwnd);
	SceneCameraHandler::Initialize(this->hwnd, width, height);
	//SceneCameraHandler::GetSceneCamera()->SetOrthoProjection(width / 300.0f, height / 300.0f, -4.0f, 4.0f);
	//SceneCameraHandler::GetSceneCamera()->SetPerspProjection(1.57f, width / height, 0.01f, 1000.0f);
	//SceneCameraHandler::GetSceneCamera()->SetPerspProjection(1.0f, width / height, 0.01f, 1000.0f);

	TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\brick.png");
	MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\teapot.obj");
	MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\bunny.obj");
	MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\armadillo.obj");

	//Cube* cube = (Cube*)GameObjectManager::CreateGameObject(GameObjectManager::CUBE);
	//cube->SetAnimationSpeed(3.0f);
	//cube->SetScale(Vector3D(0.5f));

	//Quad* quad = (Quad*)GameObjectManager::CreateGameObject(GameObjectManager::QUAD);
	//quad->SetRotation(1.5708f, 0.0f, 0.0f);
	//quad->SetScale(Vector3D(4.0f));
	/*
	PhysicsQuad* quad = (PhysicsQuad*)GameObjectManager::CreateGameObject(GameObjectManager::PHYSICS_QUAD);

	for (int i = 0; i < 10; i++)
	{
		PhysicsCube* cube = (PhysicsCube*)GameObjectManager::CreateGameObject(GameObjectManager::PHYSICS_CUBE);
	}*/

	GameObjectSpawner::SpawnPhysicsObjects();
}

void AppWindow::OnUpdate()
{
	InputSystem::Update();
	SceneCameraHandler::Update();

	if (EngineBackend::GetMode() == EngineBackend::EDITOR)
	{
		GameObjectManager::Update();
	}

	else if (EngineBackend::GetMode() == EngineBackend::PLAY)
	{
		BaseComponentSystem::GetPhysicsSystem()->UpdateAllComponents();
		GameObjectManager::Update();
	}
	
	else if (EngineBackend::GetMode() == EngineBackend::PAUSED &&
		EngineBackend::InsideFrameStep())
	{
		BaseComponentSystem::GetPhysicsSystem()->UpdateAllComponents();
		GameObjectManager::Update();
		EngineBackend::EndFrameStep();
	}

	BaseComponentSystem::GetRendererSystem()->UpdateAllComponents();
	SceneCameraHandler::Render();
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
	UIManager::Destroy();
	GameObjectManager::Destroy();
	BaseComponentSystem::Destroy();
	SceneCameraHandler::Destroy();
	RenderQueue::Destroy();
	InputSystem::Destroy();
	ActionHistory::Destroy();
	EngineTime::Destroy();
	EngineBackend::Destroy();
	TextureManager::Destroy();
	MeshManager::Destroy();
	ShaderLibrary::Destroy();
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
		this->play = !this->play;
		break;
	}
	case VK_BACK:
	{
		std::cout << "BACKSPACE" << "\n";
		//this->DespawnCircles();
		break;
	}
	case VK_DELETE:
	{
		std::cout << "DELETE" << "\n";
		//this->DespawnAllCircles();
		break;
	}
	case VK_ESCAPE:
	{
		std::cout << "ESCAPE" << "\n";
		exit(0);
		break;
	}
	default:
		break;
	}
}

void AppWindow::OnKeyUp(int key)
{

}

void AppWindow::OnMouseMove(const Vector2D& deltaMousePos)
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

