#pragma once
#include "vector"
#include "../WindowSystem/Window.h"
#include "../InputSystem/InputListener.h"

#include "../GraphicsEngine/SwapChain.h"
#include "../GraphicsEngine/VertexShader.h"
#include "../GraphicsEngine/PixelShader.h"
#include "../GraphicsEngine/DepthStencilState.h"

#include "../GameObjects/Quad.h"
#include "../GameObjects/Cube.h"
#include "../GameObjects/Circle.h"
#include "../GameObjects/Line.h"



class AppWindow : public Window, public InputListener
{
public:
	AppWindow();
	~AppWindow();

	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnFocus() override;
	virtual void OnKillFocus() override;
	virtual void OnDestroy() override;

	virtual void OnKey(int key) override;
	virtual void OnKeyDown(int key) override;
	virtual void OnKeyUp(int key) override;

	virtual void OnMouseMove(const Vector2D& deltaMousePos) override;
	virtual void OnMouseButton(int button) override;
	virtual void OnMouseButtonDown(int button) override;
	virtual void OnMouseButtonUp(int button) override;

private:
	float deltaRot = 0.0f;
	int spawnSize = 5;

	float speed = 2.0f;
	float rotX = 0.0f;
	float rotY = 0.0f;

	Vector3D camPos;
	bool mouseButtonHeld = false;

	Matrix4x4 cam;

private:
	VertexShader* vertexShader;
	PixelShader* pixelShader;

	void* vsBytes = nullptr;
	size_t vsSize = 0;

	SwapChain* swapChain;

private:
	static AppWindow* instance;
	friend class Camera;

	Line* CreateLine(const Vector3D& startPos, const Vector3D& endPos);
};

