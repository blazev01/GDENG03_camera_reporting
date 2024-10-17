#include "SceneCameraHandler.h"
#include "../EngineTime/EngineTime.h"

SceneCameraHandler* SceneCameraHandler::instance = NULL;

void SceneCameraHandler::Initialize()
{
	instance = new SceneCameraHandler();
	instance->camera = new Camera("Scene Camera");
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

SceneCameraHandler::SceneCameraHandler()
{

}

SceneCameraHandler::~SceneCameraHandler()
{

}
