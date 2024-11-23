#include "EditorAction.h"

EditorAction::EditorAction(GameObject* gameObject)
{
	this->objectName = gameObject->GetName();
	this->localPosition = gameObject->GetLocalPosition();
	this->localScale = gameObject->GetLocalScale();
	this->orientation = gameObject->GetTransform();
	this->localMatrix = gameObject->GetTransform();
}

EditorAction::~EditorAction()
{

}

std::string EditorAction::GetOwnerName()
{
	return this->objectName;
}

Vector3D EditorAction::GetStoredPosition()
{
	return this->localPosition;
}

Vector3D EditorAction::GetStoredRotation()
{
	return this->localRotation;
}

Vector3D EditorAction::GetStoredScale()
{
	return this->localScale;
}

Matrix4x4 EditorAction::GetStoredOrientation()
{
	return this->orientation;
}

Matrix4x4 EditorAction::GetStoredMatrix()
{
	return this->localMatrix;
}
