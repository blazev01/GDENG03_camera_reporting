#pragma once
#include "../GameObjects/Camera.h"

class SceneCameraHandler
{
public:
	static void Initialize();
	static void Update();
	static void Release();

	static Camera* GetSceneCamera();
	static Matrix4x4 GetViewMatrix();
	static Matrix4x4 GetProjectionMatrix();
public:
	static void CreateNewCamera(float width, float height);
	static void SwitchNextCamera();
	static void SwitchPrevCamera();
private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};

	static SceneCameraHandler* instance;

	std::vector<Camera*> cameras;
	Camera* camera = NULL;
	int cameraLimit = 3;
	int cameraCount = 0;
	int cameraIterator = 0;

};

