#include "SceneCameraHandler.h"
#include "../EngineTime/EngineTime.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../InputSystem/InputSystem.h"

SceneCameraHandler* SceneCameraHandler::instance = NULL;

void SceneCameraHandler::Initialize(HWND hwnd, float width, float height)
{
	instance = new SceneCameraHandler();

	instance->hwnd = hwnd;
	instance->width = width;
	instance->height = height;

	instance->swapChain = GraphicsEngine::CreateSwapChain();
	instance->swapChain->Init(hwnd, width, height);

	instance->position = Vector3(0.0f, 2.0f, -2.0f);
	instance->rotation = Vector3(1.0f, 0.0f, 0.0f);
}

void SceneCameraHandler::Update()
{
	float deltaTime = EngineTime::GetUnscaledDeltaTime();
	if (instance->isSceneCamera)
	{
		if (InputSystem::IsKeyDown(VK_LBUTTON))
		{
			std::cout << "LMB HELD" << "\n";
			InputSystem::ShowCursor(false);
		}
		else if (InputSystem::IsKeyUp(VK_LBUTTON))
		{
			std::cout << "LMB RELEASED" << "\n";
			InputSystem::ShowCursor(true);
		}

		if (InputSystem::IsKey(VK_LBUTTON))
		{
			Vector2 mousePos = InputSystem::GetCursorPosition();
			InputSystem::SetCursorPosition(instance->width / 2.0f, instance->height / 2.0f);

			if (mousePos != instance->oldMousePos)
			{
				instance->rotation.x += (mousePos.y - (instance->height / 2.0f)) * deltaTime * 0.1f;
				instance->rotation.y += (mousePos.x - (instance->width / 2.0f)) * deltaTime * 0.1f;
				instance->oldMousePos = mousePos;
			}
		}

		if (InputSystem::IsKey('W'))
		{
			std::cout << "W" << "\n";
			instance->position -= instance->speed * deltaTime * instance->camera->GetForward();
		}

		if (InputSystem::IsKey('S'))
		{
			std::cout << "S" << "\n";
			instance->position += instance->speed * deltaTime * instance->camera->GetForward();
		}

		if (InputSystem::IsKey('A'))
		{
			std::cout << "A" << "\n";
			instance->position -= instance->speed * deltaTime * instance->camera->GetRight();
		}

		if (InputSystem::IsKey('D'))
		{
			std::cout << "D" << "\n";
			instance->position += instance->speed * deltaTime * instance->camera->GetRight();
		}

		if (InputSystem::IsKey('Q'))
		{
			std::cout << "Q" << "\n";
			instance->position.y -= instance->speed * deltaTime;
		}

		if (InputSystem::IsKey('E'))
		{
			std::cout << "E" << "\n";
			instance->position.y += instance->speed * deltaTime;
		}
		if (InputSystem::IsKeyDown('G') && !instance->gameCameras.empty())
		{
			std::cout << "G" << "\n";
			instance->gameCameras[0]->SetPosition(instance->position);
			instance->gameCameras[0]->SetRotation(instance->rotation);

		}
	}
		for (Camera* camera : instance->cameras)
		{
			camera->SetRotation(instance->rotation);
			camera->SetPosition(instance->position);
			camera->Update(deltaTime);
		}


}

void SceneCameraHandler::Render()
{
	for (Camera* camera : instance->gameCameras)
		camera->RenderViewTexture();

	instance->camera->Render();
}

void SceneCameraHandler::Present()
{
	instance->camera->Present();
}

void SceneCameraHandler::Release()
{
	if (!instance->cameras.empty())
	{
		for (int i = instance->cameras.size() - 1; i >= 0; i--)
		{
			instance->cameras[i]->Release();
			instance->cameras.pop_back();
		}
	}
	if (!instance->gameCameras.empty())
	{
		for (int i = instance->gameCameras.size() - 1; i >= 0; i--)
		{
			instance->gameCameras[i]->Release();
			instance->gameCameras.pop_back();
		}
	}

	delete instance;
}

Camera* SceneCameraHandler::GetSceneCamera()
{
	return instance->camera;
}

Matrix4x4 SceneCameraHandler::GetViewMatrix()
{
	return instance->camera->GetViewMatrix();
}

Matrix4x4 SceneCameraHandler::GetProjectionMatrix()
{
	return instance->camera->GetProjectionMatrix();
}

void SceneCameraHandler::CreateNewCamera()
{
	if (instance->cameras.size() < instance->cameraLimit)
	{
		instance->cameraCount++;
		instance->cameras.push_back(new Camera("Scene Camera " + std::to_string(instance->cameraCount), instance->swapChain));
		instance->cameras[instance->cameraCount - 1]->SetPerspProjection(1.57f, instance->width / (float)instance->height, 0.01f, 1000.0f);

		if (instance->camera == NULL)
			instance->camera = instance->cameras[instance->cameraCount - 1];

		std::cout << instance->cameras[instance->cameraCount-1]->GetName() << std::endl;
		
	}
}

GameCamera* SceneCameraHandler::CreateGameCamera(void* shaderBytes, size_t shaderSize)
{
	if (instance->gameCameras.size() < instance->gameCameraLimit)
	{
		instance->gameCameraCount++;
		instance->gameCameras.push_back(new GameCamera("Game Camera" + std::to_string(instance->gameCameraCount), instance->swapChain, shaderBytes, shaderSize));
		instance->gameCameras[instance->gameCameraCount - 1]->SetPerspProjection(1.57f, instance->width / (float)instance->height,
			0.01f, 1000.0f);
		instance->gameCameras[instance->gameCameraCount - 1]->SetScale(Vector3(0.5f));
		instance->gameCameras[instance->gameCameraCount - 1]->SetPosition(Vector3(0,0,0));
		instance->gameCameras[instance->gameCameraCount - 1]->SetPriority(1);
		instance->gameCameras[instance->gameCameraCount - 1]->SetLayer(1);
		std::cout << instance->gameCameras[instance->gameCameraCount - 1]->GetName() << std::endl;
		return instance->gameCameras[instance->gameCameraCount - 1];
	}
}

Camera* SceneCameraHandler::GetCurCamera()
{
	return instance->camera;
}


Camera* SceneCameraHandler::GetCamera(int index)
{
	if (index < 0 || index >= instance->cameras.size())
		return NULL;

	return instance->cameras[index];
}

Camera* SceneCameraHandler::GetGameCamera()
{
	if (instance->gameCameraCount > 0)
		return instance->gameCameras[instance->gameCameraCount - 1];

	else
		return nullptr;
}

GameCamera* SceneCameraHandler::GetGameCamera(unsigned int index)
{
	if (!instance->gameCameras.empty() && index < instance->gameCameras.size())
		return instance->gameCameras[index];
	else return nullptr;
}

void SceneCameraHandler::SwitchNextCamera()
{
	if (instance->camera->GetName().find("Game Camera") == std::string::npos)
	{
		instance->cameraIterator++;
		if (instance->cameraIterator >= instance->cameras.size())
		{
			instance->cameraIterator = 0;
			std::cout << "Max cameras reached returning to first camera" << std::endl;
		}
		std::cout << "Currently using camera: " << instance->cameraIterator + 1 << std::endl;
		instance->camera = instance->cameras[instance->cameraIterator];
	}
	
}

void SceneCameraHandler::SwitchPrevCamera()
{
	if (instance->camera->GetName().find("Game Camera") != std::string::npos)
	{
		instance->cameraIterator--;
		if (instance->cameraIterator < 0)
		{
			instance->cameraIterator = instance->cameraLimit - 1;
			std::cout << "First Camera Reached Going to last camera" << std::endl;
		}
		std::cout << "Currently using camera: " << instance->cameraIterator + 1 << std::endl;
		instance->camera = instance->cameras[instance->cameraIterator];
	}
}

void SceneCameraHandler::SwitchCameraType()
{
	if (instance->isSceneCamera && !instance->gameCameras.empty())
	{
		instance->gameCameras[0]->SetActive(true);
		instance->camera = instance->gameCameras[0];
		instance->isSceneCamera = false;
		
	}
	else if(!instance->isSceneCamera && !instance->gameCameras.empty())
	{
		instance->camera = instance->cameras[instance->cameraIterator];
		instance->gameCameras[0]->SetActive(false);
		instance->isSceneCamera = true;
	}
	std::cout << "Currently using camera: " << instance->camera->GetName()<< std::endl;
}

void SceneCameraHandler::SetSceneCameraPos(Vector3 pos)
{
	instance->position = pos;
}

void SceneCameraHandler::SetSceneCameraRot(Vector3 rot)
{
	instance->rotation = rot;
}

void SceneCameraHandler::AlignGameCamerasToView()
{
	if (!instance->cameras.empty() && !instance->gameCameras.empty())
	{
		Camera* sceneCamera = instance->cameras[0]; // Assuming cameras[0] is the main scene camera
		Vector3 scenePosition = sceneCamera->GetLocalPosition();
		Vector3 sceneRotation = sceneCamera->GetLocalRotation();

		for (GameCamera* gameCamera : instance->gameCameras)
		{
			gameCamera->SetPosition(scenePosition);
			gameCamera->SetRotation(sceneRotation);
			std::cout << "Aligned " << gameCamera->GetName() << " to Scene Camera view." << std::endl;
		}
	}
}

SceneCameraHandler::SceneCameraHandler()
{

}

SceneCameraHandler::~SceneCameraHandler()
{

}
