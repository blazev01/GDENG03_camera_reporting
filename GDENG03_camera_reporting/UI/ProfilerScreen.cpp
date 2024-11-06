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

	ImGui::Begin("Game Camera Viewport", (bool*)0, flags);

	ID3D11ShaderResourceView* texture = SceneCameraHandler::GetCamera(0)->GetViewTexture()->GetSRV();
	if (texture) 
		ImGui::Image((ImTextureID)texture, ImVec2(350, 200)); 

	else 
		ImGui::Text("Failed to render camera to texture"); 

	ImGui::End();
}
