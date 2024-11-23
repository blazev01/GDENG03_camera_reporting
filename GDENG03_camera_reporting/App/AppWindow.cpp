#include "AppWindow.h"
#include "Windows.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../EngineTime/EngineTime.h"
#include "../InputSystem/InputSystem.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../GameObjects/GameObjectManager.h"
#include "../GameObjects/RenderQueue.h"
#include "../GraphicsEngine/ShaderLibrary.h"
#include "../Resource/MeshManager.h"
#include "../Resource/TextureManager.h"
#include "../UI/UIManager.h"
#include "../Components/BaseComponentSystem.h"
#include "../GameObjects/PhysicsQuad.h"
#include "../GameObjects/PhysicsCube.h"
#include "../Backend/EngineBackend.h"
#include "../Backend/ActionHistory.h"

AppWindow* AppWindow::instance = NULL;

AppWindow::AppWindow()
{
	instance = this;
	this->vertexShader = NULL;
	this->pixelShader = NULL;
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

	SceneCameraHandler::CreateNewCamera();
	
	//SwapChain* swapChain2 = GraphicsEngine::CreateSwapChain();
	//swapChain2->Init(this->hwnd, width, height);
	//SceneCameraHandler::CreateNewCamera(swapChain2);
	//
	//SwapChain* swapChain3 = GraphicsEngine::CreateSwapChain();
	//swapChain3->Init(this->hwnd, width, height);
	//SceneCameraHandler::CreateNewCamera(swapChain3);


	//std::bitset<4> cullingMask1 = SceneCameraHandler::GetCamera(0)->GetCullingMask();
	//std::bitset<4> cullingMask2 = SceneCameraHandler::GetCamera(0)->GetCullingMask();
	//cullingMask1[0] = false;
	//cullingMask2[1] = false;
	//SceneCameraHandler::GetCamera(1)->SetCullingMask(cullingMask1);
	//SceneCameraHandler::GetCamera(2)->SetCullingMask(cullingMask2);

	//SceneCameraHandler::SetOrthoProjection(width / 300.0f, height / 300.0f, -4.0f, 4.0f);
	SceneCameraHandler::GetSceneCamera()->SetPerspProjection(1.57f, width / height, 0.01f, 1000.0f);

	void* shaderBytes = nullptr;
	size_t shaderSize = 0;

	ShaderLibrary::RequestVertexShaderData(L"VertexMeshLayout.hlsl", &shaderBytes, &shaderSize);
	this->pixelShader = ShaderLibrary::GetPixelShader(L"PixelShader.hlsl");
	this->vertexShader = ShaderLibrary::GetVertexShader(L"VertexShader.hlsl");
	
	for (int i = 0; i < 3; i++)
	{
		Cube* cube = (Cube*)GameObjectManager::CreateGameObject(GameObjectManager::CUBE);
		cube->SetAnimationSpeed(0.0f);
		cube->SetScale(Vector3D(0.5f));
		cube->SetPosition(Vector3D(i - 1, 0.0f, i - 1));
		cube->SetPriority(1);
		if (i != 1) cube->SetLayer(1);
	}
	
	for (int i = 0; i < 2; i++)
	{
		Quad* quad = (Quad*)GameObjectManager::CreateGameObject(GameObjectManager::QUAD);
		if (i == 0) quad->SetRotation(1.5708f, 0.0f, 0.0f);
		else quad->SetRotation(-1.5708f, 0.0f, 0.0f);
		quad->SetScale(Vector3D(4.0f));
		quad->SetLayer(1);
	}



	//std::vector<Vector3D> renderLines = SceneCameraHandler::GetSceneCamera()->CreateRenderRegionOutliner(1.57f, width / height, 0.01f, 1000.0f);
	/*
	std::vector<Vector3D> nearPlanePoints = SceneCameraHandler::GetSceneCamera()->CreateRenderRegionOutliner(1.57f, width / height, 0.01f);
	std::vector<Vector3D> farPlanePoints = SceneCameraHandler::GetSceneCamera()->CreateRenderRegionOutliner(1.57f, width / height, 1000.0f);

	for (int i = 0; i < farPlanePoints.size(); i++) {
		CreateLine(nearPlanePoints[i], farPlanePoints[i])->SetParent(SceneCameraHandler::GetSceneCamera());
	}
	int cornerPairs[4][2]  = { {0,1}, {0,2}, {3,1}, {3,2} };
	for (int i = 0; i < 4; i++) {
		CreateLine(nearPlanePoints[cornerPairs[i][0]], nearPlanePoints[cornerPairs[i][1]])->SetParent(SceneCameraHandler::GetSceneCamera());
		CreateLine(farPlanePoints[cornerPairs[i][0]], farPlanePoints[cornerPairs[i][1]])->SetParent(SceneCameraHandler::GetSceneCamera());
	}*/

}

Line* AppWindow::CreateLine(const Vector3D& startPos, const Vector3D& endPos) {
	Line* line = new Line("lyn", AppWindow::instance->vsBytes, AppWindow::instance->vsSize, startPos, endPos);
	line->SetVertexShader(AppWindow::instance->vertexShader);
	line->SetPixelShader(AppWindow::instance->pixelShader);
	GameObjectManager::AddGameObject(line);
	RenderQueue::AddRenderer(line);

	return line;
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
		SceneCameraHandler::SwitchCameraType();
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
	case VK_OEM_PERIOD:
		std::cout << "Greater Than" << std::endl;
		SceneCameraHandler::SwitchNextCamera();
		break;
	case VK_OEM_COMMA:
		std::cout << "Less Than" << std::endl;
		SceneCameraHandler::SwitchPrevCamera();
		break;
	case VK_RETURN:
		std::cout << "Enter" << std::endl;
		//SceneCameraHandler::CreateGameCamera(this->vsBytes, this->vsSize);
		
		break;
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

