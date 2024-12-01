#pragma once
#include "../GameObjects/Camera.h"
#include "../GameObjects/GameCamera.h"

class SceneCameraHandler
{
public:
	static void Initialize(HWND hwnd, int width, int height);
	static void Update();
	static void Render();
	static void Present();
	static void Destroy();

	static void AddSceneCamera();
	static void DeleteSceneCamera(int index);
	static GameCamera* AddGameCamera(void* shaderBytes, size_t shaderSize);
	static void DeleteGameCamera(GameCamera* gameCamera);

	static Camera* GetSceneCamera();
	static const std::vector<Camera*>& GetSceneCameras();
	static const std::vector<GameCamera*>& GetGameCameras();

	static SwapChain* GetSwapChain();
	static Matrix4x4 GetView();
	static Matrix4x4 GetProjection();
private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};

	static SceneCameraHandler* instance;

	SwapChain* swapChain = NULL;
	Camera* camera = NULL;
	std::vector<Camera*> sceneCameras;
	std::vector<GameCamera*> gameCameras;

	float speed = 5;
	Vector3D camPos;
	Vector2D oldMousePos;
};

