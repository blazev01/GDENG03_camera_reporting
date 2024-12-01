#include "GizmoLayer.h"
#include "../IMGUI/imgui.h"
#include "../IMGUI/ImGuizmo.h"
#include"../IMGUI/imGuIZMOquat.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../GameObjects/GameObjectManager.h"

#define DEG2RAD 0.0174533

GizmoLayer* GizmoLayer::instance = nullptr;

void GizmoLayer::Initialize()
{
	instance = new GizmoLayer();
}

void GizmoLayer::Destroy()
{
	delete instance;
}

void GizmoLayer::Draw()
{
	ImGuizmo::BeginFrame();

	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_AlwaysAutoResize;

	if (ImGui::Begin("Gizmos", nullptr, flags))
	{
		Vector3D cameraRot = SceneCameraHandler::GetSceneCamera()->GetLocalRotation();
		quat rot(1.0f, cameraRot.x, cameraRot.y, cameraRot.z);

		Vector3D cameraPos  = SceneCameraHandler::GetSceneCamera()->GetLocalPosition();
		vec3 pos(cameraPos.x, cameraPos.y, cameraPos.z);

		if (ImGui::gizmo3D("Camera Rotation", rot, 128, imguiGizmo::mode3Axes | imguiGizmo::cubeAtOrigin))
		{
			SceneCameraHandler::GetSceneCamera()->SetRotation(rot.x, rot.y, rot.z);
			SceneCameraHandler::GetSceneCamera()->Recalculate();
		}
		
		ImGui::SameLine();
		if (ImGui::gizmo3D("Camera Translation", pos, 128, imguiGizmo::modePanDolly | imguiGizmo::cubeAtOrigin))
		{
			SceneCameraHandler::GetSceneCamera()->SetPosition(pos.x, pos.y, pos.z);
			SceneCameraHandler::GetSceneCamera()->Recalculate();
		}

		if (ImGui::Button("Reset Rotation", ImVec2(128, 20)))
		{
			SceneCameraHandler::GetSceneCamera()->SetRotation(0.0f, 0.0f, 0.0f);
			SceneCameraHandler::GetSceneCamera()->Recalculate();
		}
		
		ImGui::SameLine();
		if (ImGui::Button("Reset Translation", ImVec2(128, 20)))
		{
			SceneCameraHandler::GetSceneCamera()->SetPosition(0.0f, 0.0f, 0.0f);
			SceneCameraHandler::GetSceneCamera()->Recalculate();
		}

		ImGui::Checkbox("Show Grid", &instance->showGrid);

		float* camView = SceneCameraHandler::GetSceneCamera()->GetView().GetAs1DArray();
		float* camProj = SceneCameraHandler::GetSceneCamera()->GetView().GetAs1DArray();
		//float* camLoc = SceneCameraHandler::GetSceneCamera()->GetView().GetAs1DArray();
		Matrix4x4 identity;
		identity.SetIdentity();
		float* camLoc = identity.GetAs1DArray();

		if (instance->showGrid) ImGuizmo::DrawGrid(camView, camProj, camLoc, 10);

		if (ImGui::RadioButton("Translate", instance->translate))
		{
			instance->translate = true;
			instance->rotate = false;
			instance->scale = false;
		}
		
		ImGui::SameLine();
		if (ImGui::RadioButton("Rotate", instance->rotate))
		{
			instance->translate = false;
			instance->rotate = true;
			instance->scale = false;
		}
		
		ImGui::SameLine();
		if (ImGui::RadioButton("Scale", instance->scale))
		{
			instance->translate = false;
			instance->rotate = false;
			instance->scale = true;
		}
	}
	ImGui::End();

	instance->selectedObject = GameObjectManager::GetSelectedObject();
	if (instance->selectedObject != NULL)
		instance->EnableGizmo(instance->selectedObject);
}

void GizmoLayer::EnableGizmo(GameObject* selectedObject)
{
	float* camView = SceneCameraHandler::GetSceneCamera()->GetView().GetAs1DArray();
	float* camProj = SceneCameraHandler::GetSceneCamera()->GetView().GetAs1DArray();
	float* selectedMat = selectedObject->GetTransform().GetAs1DArray();

	bool manipulated = false;
	if (instance->translate) manipulated = ImGuizmo::Manipulate(camView, camProj, ImGuizmo::TRANSLATE, ImGuizmo::LOCAL, selectedMat);
	if (instance->rotate) manipulated = ImGuizmo::Manipulate(camView, camProj, ImGuizmo::ROTATE, ImGuizmo::LOCAL, selectedMat);
	if (instance->scale) manipulated = ImGuizmo::Manipulate(camView, camProj, ImGuizmo::SCALE, ImGuizmo::LOCAL, selectedMat);

	if (manipulated)
	{
		float translate[] = { 0.0f, 0.0f, 0.0f };
		float rotate[] = { 0.0f, 0.0f, 0.0f };
		float scale[] = { 0.0f, 0.0f, 0.0f };
		ImGuizmo::DecomposeMatrixToComponents(selectedMat, translate, rotate, scale);

		selectedObject->SetPosition(translate[0], translate[1], translate[2]);
		selectedObject->SetRotation(Vector3D(rotate[0], rotate[1], rotate[2]) * DEG2RAD);
		selectedObject->SetScale(scale[0], scale[1], scale[2]);
		selectedObject->Recalculate();
	}
}

GizmoLayer::GizmoLayer()
{

}

GizmoLayer::~GizmoLayer()
{

}
