#include "SceneCameraHandler.h"
#include "../EngineTime/EngineTime.h"

SceneCameraHandler* SceneCameraHandler::instance = NULL;

void SceneCameraHandler::Initialize()
{
	instance = new SceneCameraHandler();
}

void SceneCameraHandler::Update()
{
	instance->camera->Update(EngineTime::GetUnscaledDeltaTime());
}

void SceneCameraHandler::Release()
{
	instance->camera->Release();

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

void SceneCameraHandler::CreateNewCamera(float width, float height)
{
	if (instance->cameras.size() < instance->cameraLimit)
	{
		instance->cameraCount++;
		instance->cameras.push_back(new Camera("Scene Camera " + std::to_string(instance->cameraCount)));
		instance->cameras[instance->cameraCount - 1]->SetWindowSize(width, height);
		instance->cameras[instance->cameraCount - 1]->SetPerspProjection(1.57f, width / height, 0.01f, 1000.0f);
		instance->camera = instance->cameras[instance->cameraCount - 1];
		std::cout << instance->cameras[instance->cameraCount-1]->GetName() << std::endl;
		
	}
}

void SceneCameraHandler::SwitchNextCamera()
{
	instance->cameraIterator++;
	if (instance->cameraIterator >= instance->cameras.size())
	{
		instance->cameraIterator = 0;
		std::cout << "Max cameras reached returning to first camera" << std::endl;
	}
	std::cout << "Currently using camera: " << instance->cameraIterator+1 << std::endl;
	instance->camera = instance->cameras[instance->cameraIterator];
}

void SceneCameraHandler::SwitchPrevCamera()
{
	instance->cameraIterator--;
	if (instance->cameraIterator < 0)
	{
		instance->cameraIterator = instance->cameraLimit-1;
		std::cout << "First Camera Reached Going to last camera" << std::endl;
	}
	std::cout << "Currently using camera: " << instance->cameraIterator+1 << std::endl;
	instance->camera = instance->cameras[instance->cameraIterator];
}

SceneCameraHandler::SceneCameraHandler()
{

}

SceneCameraHandler::~SceneCameraHandler()
{

}
