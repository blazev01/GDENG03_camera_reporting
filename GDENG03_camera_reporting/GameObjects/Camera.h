#pragma once
#include "bitset"
#include "GameObject.h"
#include "ViewTexture.h"
#include "../InputSystem/InputListener.h"
#include "../GraphicsEngine/SwapChain.h"

class Camera : public GameObject
{
public:
	Camera(std::string name, SwapChain* swapChain);
	~Camera();

	virtual void Update(float deltaTime) override;
	virtual void Draw(Matrix4x4 view, Matrix4x4 proj) override;
	virtual void Release() override;

	void Render();
	void RenderViewTexture();
	ViewTexture* GetViewTexture();

	Matrix4x4 GetViewMatrix();
	Matrix4x4 GetProjectionMatrix();
	void SetOrthoProjection(float width, float height, float nearPlane, float farPlane);
	void SetPerspProjection(float fov, float aspect, float zNear, float zFar);
	void Present();
	

	std::vector<Vector3> CreateRenderRegionOutliner(float fov, float aspect, float z);

	std::bitset<4> GetCullingMask() const;
	void SetCullingMask(std::bitset<4> cullingMask);

	float getWidth();
	float getHeight();


	Matrix4x4 worldTransform;

protected:
	SwapChain* swapChain;
	Matrix4x4 view;
	Matrix4x4 projection;

	float deltaTime = 0.0f;
	float speed = 2.0f;

	Vector2 oldMousePos;

	std::bitset<4> cullingMask;
	ViewTexture* viewTexture;
};

