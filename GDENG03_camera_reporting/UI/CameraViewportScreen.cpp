#include "CameraViewportScreen.h"
#include "../SceneCamera/SceneCameraHandler.h"

CameraViewportScreen::CameraViewportScreen() : UIScreen("CAMERA_VIEWPORT_SCREEN")
{

}

CameraViewportScreen::~CameraViewportScreen()
{

}

void CameraViewportScreen::DrawUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

	std::vector<GameCamera*> cameras = SceneCameraHandler::GetGameCameras();
	Camera* camera = SceneCameraHandler::GetSceneCamera();

	if (camera)
	{
		if (!camera->GetViewTexture()->GetSRV())
			camera->GetViewTexture()->Initialize(350, 200);

		std::string name = camera->GetName();
		if (ImGui::Begin(name.c_str(), (bool*)0, flags))
		{
			ID3D11ShaderResourceView* texture = camera->GetViewTexture()->GetSRV();

			if (texture) ImGui::Image((ImTextureID)texture, ImVec2(350, 200));
			else ImGui::Text("Failed to render camera to texture.");
		}
		ImGui::End();
	}

	int i = 0;
	for (GameCamera* camera : cameras)
	{
		if (camera)
		{
			if (!camera->GetViewTexture()->GetSRV())
				camera->GetViewTexture()->Initialize(350, 200);

			std::string name = camera->GetName();
			if (ImGui::Begin(name.c_str(), (bool*)0, flags))
			{
				ID3D11ShaderResourceView* texture = camera->GetViewTexture()->GetSRV();

				if (texture) ImGui::Image((ImTextureID)texture, ImVec2(350, 200));
				else ImGui::Text("Failed to render camera to texture.");
			}
			ImGui::End();
			i++;
		}
	}
}
