#include "SceneCameraHandler.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../EngineTime/EngineTime.h"
#include "../InputSystem/InputSystem.h"
#include "../Backend/Debug.h"

SceneCameraHandler* SceneCameraHandler::instance = NULL;

void SceneCameraHandler::Initialize(HWND hwnd, int width, int height)
{
	instance = new SceneCameraHandler();

	instance->swapChain = GraphicsEngine::CreateSwapChain();
	instance->swapChain->Init(hwnd, width, height);

	instance->AddSceneCamera();
	instance->camera->SetPosition(0.0f, 2.0f, -10.0f);
}

void SceneCameraHandler::Update()
{
	float deltaTime = EngineTime::GetDeltaTime();

	if (InputSystem::IsKeyDown(VK_RBUTTON))
	{
		//std::cout << "RMB HELD" << "\n";
		InputSystem::ShowCursor(false);
	}
	else if (InputSystem::IsKeyUp(VK_RBUTTON))
	{
		//std::cout << "RMB RELEASED" << "\n";
		InputSystem::ShowCursor(true);
	}

	Vector3D rotation = instance->camera->GetLocalRotation();
	if (InputSystem::IsKey(VK_RBUTTON))
	{
		Vector2D mousePos = InputSystem::GetCursorPosition();
		InputSystem::SetCursorPosition(instance->swapChain->GetWidth() / 2.0f, instance->swapChain->GetHeight() / 2.0f);

		if (mousePos != instance->oldMousePos)
		{
			rotation.x -= (mousePos.y - (instance->swapChain->GetHeight() / 2.0f)) * deltaTime * 0.1f;
			rotation.y -= (mousePos.x - (instance->swapChain->GetWidth() / 2.0f)) * deltaTime * 0.1f;
			instance->oldMousePos = mousePos;
		}
	}

	Vector3D position = instance->camera->GetLocalPosition();
	if (InputSystem::IsKey('W'))
	{
		position -= instance->speed * deltaTime * instance->camera->GetForward();
	}

	if (InputSystem::IsKey('S'))
	{
		position += instance->speed * deltaTime * instance->camera->GetForward();
	}

	if (InputSystem::IsKey('A'))
	{
		position -= instance->speed * deltaTime * instance->camera->GetRight();
	}

	if (InputSystem::IsKey('D'))
	{
		position += instance->speed * deltaTime * instance->camera->GetRight();
	}

	if (InputSystem::IsKey('Q'))
	{
		position.y -= instance->speed * deltaTime;
	}

	if (InputSystem::IsKey('E'))
	{
		position.y += instance->speed * deltaTime;
	}

	instance->camera->SetRotation(rotation);
	instance->camera->SetPosition(position);
	instance->camera->Recalculate();

	instance->camera->Update(deltaTime);
}

void SceneCameraHandler::Render()
{
	for (GameCamera* camera : instance->gameCameras)
		camera->RenderViewTexture();

	instance->camera->RenderViewTexture();
	instance->camera->Render();
}

void SceneCameraHandler::Present()
{
	instance->camera->Present();
}

void SceneCameraHandler::Destroy()
{
	instance->camera->Destroy();
	instance->swapChain->Release();

	delete instance;
}

void SceneCameraHandler::AddSceneCamera()
{
	Camera* camera = new Camera("Scene Camera", instance->swapChain);
	camera->SetPerspProjection(1.0f, (float)instance->swapChain->GetWidth() / instance->swapChain->GetHeight(), 0.01f, 1000.0f);
	if (!instance->camera) instance->camera = camera;
	instance->sceneCameras.push_back(camera);
}

void SceneCameraHandler::DeleteSceneCamera(int index)
{
	if (index < 1 || index >= instance->sceneCameras.size())
	{
		Debug::Log("this is the first Scene Camera");
		return;
	}
	if (instance->sceneCameras[index] == instance->camera)
	{
		Debug::Log("You are Currently using this camera");
		return;
	}
	instance->sceneCameras[index]->Destroy();
	instance->sceneCameras.erase(instance->sceneCameras.begin() + index);
}

GameCamera* SceneCameraHandler::AddGameCamera(void* shaderBytes, size_t shaderSize)
{
	GameCamera* gameCamera = new GameCamera("Camera", instance->swapChain, shaderBytes, shaderSize);
	gameCamera->SetPerspProjection(1.0f, (float)instance->swapChain->GetWidth() / instance->swapChain->GetHeight(), 0.01f, 1000.0f);
	instance->gameCameras.push_back(gameCamera);
	return gameCamera;
}

void SceneCameraHandler::DeleteGameCamera(GameCamera* gameCamera)
{
	if (instance->gameCameras.empty()) return;

	std::vector<GameCamera*>::iterator it = instance->gameCameras.begin();
	while (it != instance->gameCameras.end() && *it != gameCamera) it++;
	if (*it == gameCamera) instance->gameCameras.erase(it);
}

void SceneCameraHandler::CycleGameCamerasForward()
{
	instance->iterator++;
	if (instance->iterator >= instance->sceneCameras.size())
	{
		Debug::Log("Last scene camera");
		instance->iterator = instance->sceneCameras.size() - 1;
	}
	instance->camera = instance->sceneCameras[instance->iterator];
}

void SceneCameraHandler::CycleGameCamerasBackward()
{
	instance->iterator--;
	if (instance->iterator < 0)
	{
		Debug::Log("First scene camera");
		instance->iterator = 0;
	}
	instance->camera = instance->sceneCameras[instance->iterator];
}

Camera* SceneCameraHandler::GetSceneCamera()
{
	return instance->camera;
}

const std::vector<Camera*>& SceneCameraHandler::GetSceneCameras()
{
	return instance->sceneCameras;
}

const std::vector<GameCamera*>& SceneCameraHandler::GetGameCameras()
{
	return instance->gameCameras;
}

SwapChain* SceneCameraHandler::GetSwapChain()
{
	return instance->swapChain;
}

Matrix4x4 SceneCameraHandler::GetView()
{
	return instance->camera->GetView();
}

Matrix4x4 SceneCameraHandler::GetProjection()
{
	return instance->camera->GetProjection();
}

SceneCameraHandler::SceneCameraHandler()
{

}

SceneCameraHandler::~SceneCameraHandler()
{

}
