#pragma once
#include "../GameObjects/Camera.h"
#include "../GameObjects/GameCamera.h"
#include "../GameObjects/Cube.h"

class SceneCameraHandler
{
public:
	static void Initialize(float width, float height);
	static void Update();
	static void Draw();
	static void Present();
	static void Release();

	static Camera* GetSceneCamera();
	static Matrix4x4 GetViewMatrix();
	static Matrix4x4 GetProjectionMatrix();

public:
	static void CreateNewCamera(SwapChain* swapChain);
	static void CreateGameCamera(SwapChain* swapchain, Cube* cube);
	static Camera* GetCamera(int index);
	static void SwitchNextCamera();
	static void SwitchPrevCamera();
	static void SwitchCameraType();

private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};

	static SceneCameraHandler* instance;

	std::vector<Camera*> cameras;
	std::vector<GameCamera*> gameCameras;
	Camera* camera = NULL;

	int cameraLimit = 3;
	int cameraCount = 0;
	int cameraIterator = 0;

	int width = 0;
	int height = 0;

	float speed = 2.0f;
	bool isSceneCamera = true;

	Vector2 oldMousePos;

	Vector3 position;
	Vector3 rotation;
};

