#include "ProfilerScreen.h"
#include "../SceneCamera/SceneCameraHandler.h"

ProfilerScreen::ProfilerScreen() : UIScreen("PROFILER_SCREEN")
{

}

ProfilerScreen::~ProfilerScreen()
{

}

void ProfilerScreen::DrawUI()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse; 

	std::vector<GameCamera*> cameras = SceneCameraHandler::GetGameCameras();
	for (GameCamera* camera : cameras)
	{
		if (camera)
		{
			if (!camera->GetViewTexture()->GetSRV())
				camera->GetViewTexture()->Initialize(350, 200);

			ImGui::Begin("Game Camera Viewport", (bool*)0, flags);
			ID3D11ShaderResourceView* texture = camera->GetViewTexture()->GetSRV();

			if (texture) ImGui::Image((ImTextureID)texture, ImVec2(350, 200));
			else ImGui::Text("Failed to render camera to texture");

			ImGui::End();
		}
	}
}
