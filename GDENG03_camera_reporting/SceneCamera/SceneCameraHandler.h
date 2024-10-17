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
private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};

	static SceneCameraHandler* instance;

	Camera* camera = NULL;
};

