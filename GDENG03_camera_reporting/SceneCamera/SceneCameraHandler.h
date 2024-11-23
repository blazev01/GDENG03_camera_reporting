#pragma once
#include "../GameObjects/Camera.h"
#include "../GameObjects/GameCamera.h"
#include "../GameObjects/Cube.h"
#include "../GameObjects/GameObjectManager.h"
#include "../GameObjects/RenderQueue.h"

class SceneCameraHandler
{
public:
	static void Initialize(HWND hwnd, float width, float height);
	static void Update();
	static void Render();
	static void Present();
	static void Destroy();

	static Camera* GetSceneCamera();
	static Matrix4x4 GetViewMatrix();
	static Matrix4x4 GetProjectionMatrix();

public:
	static void CreateNewCamera();
	static GameCamera* CreateGameCamera(void* shaderBytes, size_t shaderSize);
	static Camera* GetCurCamera();
	static Camera* GetCamera(int index);
	static Camera* GetGameCamera();
	static GameCamera* GetGameCamera(unsigned int index);
	static std::vector<GameCamera*>& GetGameCameras();
	static void SwitchNextCamera();
	static void SwitchPrevCamera();
	static void SwitchCameraType();

	static void SetSceneCameraPos(Vector3D pos);
	static void SetSceneCameraRot(Vector3D rot);

	static void AlignGameCamerasToView();

	static std::vector<Camera*>* GetCameraList();

private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};

	static SceneCameraHandler* instance;

private:
	std::vector<Camera*> cameras;
	std::vector<GameCamera*> gameCameras;
	Camera* camera = NULL;
	SwapChain* swapChain = NULL;

	int cameraLimit = 1;
	int gameCameraLimit = 4;
	int cameraCount = 0;
	int gameCameraCount = 0;
	int cameraIterator = 0;

	HWND hwnd = NULL;
	int width = 0;
	int height = 0;

	float speed = 2.0f;
	bool isSceneCamera = true;

	Vector2D oldMousePos;

	Vector3D position;
	Vector3D rotation;
};