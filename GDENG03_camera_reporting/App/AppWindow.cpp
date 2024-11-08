#include "AppWindow.h"
#include "Windows.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../EngineTime/EngineTime.h"
#include "../InputSystem/InputSystem.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../GameObjects/GameObjectManager.h"
#include "../GameObjects/RenderQueue.h"
#include "../UI/UIManager.h"


AppWindow* AppWindow::instance = NULL;
AppWindow::AppWindow()
{
	instance = this;

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

	SceneCameraHandler::Initialize(this->hwnd, width, height);
	GameObjectManager::Initialize();
	RenderQueue::Initialize();
	UIManager::Initialize(this->hwnd);

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

	GraphicsEngine::CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderBytes, &shaderSize);
	this->vertexShader = GraphicsEngine::CreateVertexShader(shaderBytes, shaderSize);

	this->vsBytes = shaderBytes;
	this->vsSize = shaderSize;

	GraphicsEngine::CompilePixelShader(L"PixelShader.hlsl", "psmain", &shaderBytes, &shaderSize);
	this->pixelShader = GraphicsEngine::CreatePixelShader(shaderBytes, shaderSize);



	GraphicsEngine::ReleaseCompiledShader();

	
	
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



	//std::vector<Vector3> renderLines = SceneCameraHandler::GetSceneCamera()->CreateRenderRegionOutliner(1.57f, width / height, 0.01f, 1000.0f);
	std::vector<Vector3> nearPlanePoints = SceneCameraHandler::GetSceneCamera()->CreateRenderRegionOutliner(1.57f, width / height, 0.01f);
	std::vector<Vector3> farPlanePoints = SceneCameraHandler::GetSceneCamera()->CreateRenderRegionOutliner(1.57f, width / height, 1000.0f);

	for (int i = 0; i < farPlanePoints.size(); i++) {
		CreateLine(nearPlanePoints[i], farPlanePoints[i])->SetParent(SceneCameraHandler::GetSceneCamera());
	}
	int cornerPairs[4][2]  = { {0,1}, {0,2}, {3,1}, {3,2} };
	for (int i = 0; i < 4; i++) {
		CreateLine(nearPlanePoints[cornerPairs[i][0]], nearPlanePoints[cornerPairs[i][1]])->SetParent(SceneCameraHandler::GetSceneCamera());
		CreateLine(farPlanePoints[cornerPairs[i][0]], farPlanePoints[cornerPairs[i][1]])->SetParent(SceneCameraHandler::GetSceneCamera());
	}

	Texture* tex = GraphicsEngine::GetTextureManager()->CreateTextureFromFile(L"..\\Assets\\Textures\\wood.jpg");
}

Line* AppWindow::CreateLine(const Vector3& startPos, const Vector3& endPos) {
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
	GameObjectManager::Update();

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
