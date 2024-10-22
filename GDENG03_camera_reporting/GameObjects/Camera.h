#pragma once
#include "bitset"
#include "GameObject.h"
#include "../InputSystem/InputListener.h"
#include "RenderQueue.h"

class Camera : public GameObject
{
public:
	Camera(std::string name);
	~Camera();

	virtual void Update(float deltaTime) override;
	virtual void Draw(VertexShader* vertexShader, PixelShader* pixelShader) override;
	virtual void Release() override;

	Matrix4x4 GetViewMatrix();
	Matrix4x4 GetProjectionMatrix();
	void SetOrthoProjection(float width, float height, float nearPlane, float farPlane);
	void SetPerspProjection(float fov, float aspect, float zNear, float zFar);
	void SetWindowSize(float width, float height);

	std::bitset<4> GetCullingMask() const;
	void SetCullingMask(std::bitset<4> cullingMask);

private:
	Matrix4x4 projection;

	float width = 0.0f;
	float height = 0.0f;

	float deltaTime = 0.0f;
	float speed = 2.0f;
	float rotX = 0.0f;
	float rotY = 0.0f;

	Vector3 camPos;
	Vector2 oldMousePos;

	std::bitset<4> cullingMask;
};

