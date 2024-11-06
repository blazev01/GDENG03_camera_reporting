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
	virtual void Draw() override;
	virtual void Release() override;

	void Render();
	void RenderViewTexture();
	ViewTexture* GetViewTexture();

	Matrix4x4 GetViewMatrix();
	Matrix4x4 GetProjectionMatrix();
	void SetOrthoProjection(float width, float height, float nearPlane, float farPlane);
	void SetPerspProjection(float fov, float aspect, float zNear, float zFar);
	void SetWindowSize(float width, float height);
	void Present();
	

	std::bitset<4> GetCullingMask() const;
	void SetCullingMask(std::bitset<4> cullingMask);

	float getWidth();
	float getHeight();

protected:
	SwapChain* swapChain;
	Matrix4x4 projection;

	float width = 0.0f;
	float height = 0.0f;

	float deltaTime = 0.0f;
	float speed = 2.0f;

	Vector2 oldMousePos;

	std::bitset<4> cullingMask;
	ViewTexture* viewTexture;
};

