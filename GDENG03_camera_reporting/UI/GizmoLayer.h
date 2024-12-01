#pragma once
#include "../GameObjects/GameObject.h"

class GizmoLayer
{
public:
	static void Initialize();
	static void Destroy();

	static void Draw();
	static void EnableGizmo(GameObject* selectedObject);
private:
	GizmoLayer();
	~GizmoLayer();
	GizmoLayer(GizmoLayer const&) {};
	GizmoLayer& operator=(GizmoLayer const&) {};

	static GizmoLayer* instance;

	bool showGrid = true;
	bool translate = true;
	bool rotate = false;
	bool scale = false;
	GameObject* selectedObject = nullptr;
};

