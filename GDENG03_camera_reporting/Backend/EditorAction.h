#pragma once
#include "../GameObjects/GameObject.h"

class EditorAction
{
public:
	EditorAction(GameObject* gameObject);
	~EditorAction();

	std::string GetOwnerName();
	Vector3D GetStoredPosition();
	Vector3D GetStoredRotation();
	Vector3D GetStoredScale();
	Matrix4x4 GetStoredOrientation();
	Matrix4x4 GetStoredMatrix();

private:
	std::string objectName;
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;
	Matrix4x4 orientation;
	Matrix4x4 localMatrix;
};

