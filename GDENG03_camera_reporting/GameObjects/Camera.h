#pragma once
#include "bitset"
#include "GameObject.h"
#include "../GraphicsEngine/SwapChain.h"
#include "../GraphicsEngine/ViewTexture.h"
#include "../InputSystem/InputListener.h"

class Camera : public GameObject
{
public:
	Camera(std::string name, SwapChain* swapChain);
	~Camera();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Matrix4x4 view, Matrix4x4 proj) override;
	virtual void Destroy() override;

	void Recalculate() override;
	void Render();
	void RenderViewTexture();
	void Present();

	Matrix4x4 GetView() const;
	Matrix4x4 GetProjection() const;
	ViewTexture* GetViewTexture();

	void SetOrthoProjection(float width, float height, float nearPlane, float farPlane);
	void SetPerspProjection(float fov, float aspect, float zNear, float zFar);

	std::vector<Vector3D> CreateRenderRegionOutliner(float fov, float aspect, float z);
	std::bitset<4> GetCullingMask() const;
	void SetCullingMask(std::bitset<4> cullingMask);

protected:
	Matrix4x4 view;
	Matrix4x4 projection;

	SwapChain* swapChain;
	ViewTexture* viewTexture;
	std::bitset<4> cullingMask;

	float deltaTime = 0.0f;
	float speed = 2.0f;
	float rotX = 0.0f;
	float rotY = 0.0f;

	Vector3D camPos;
	Vector2D oldMousePos;
};

