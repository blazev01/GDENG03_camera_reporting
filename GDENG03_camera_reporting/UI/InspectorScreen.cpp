#include "InspectorScreen.h"
#include "../SceneCamera/SceneCameraHandler.h"

#define RAD2DEG 57.2958
#define DEG2RAD 0.0174533

InspectorScreen::InspectorScreen() : UIScreen("INSPECTOR_SCREEN")
{

}

InspectorScreen::~InspectorScreen()
{

}

void InspectorScreen::DrawUI()
{
Camera* sceneCam = SceneCameraHandler::GetCamera(0);
    if (sceneCam) {
        Vector3 sceneCamPosition = sceneCam->GetLocalPosition();
        Vector3 sceneCamRotation = sceneCam->GetLocalRotation();

        float position_scene[3] = { sceneCamPosition.x, sceneCamPosition.y, sceneCamPosition.z };
        float rotation_scene[3] = { sceneCamRotation.x * RAD2DEG, sceneCamRotation.y * RAD2DEG, sceneCamRotation.z * RAD2DEG };

        ImGui::Begin("Camera Controls");

        ImGui::Text("Scene Camera");

        // Position controls
        if (ImGui::InputFloat3("SCam Pos", position_scene))
            SceneCameraHandler::SetSceneCameraPos(Vector3(position_scene[0], position_scene[1], position_scene[2]));

        // Rotation controls
        if (ImGui::InputFloat3("SCam Rot", rotation_scene)) {
            rotation_scene[0] *= DEG2RAD;
            rotation_scene[1] *= DEG2RAD;
            rotation_scene[2] *= DEG2RAD;

            SceneCameraHandler::SetSceneCameraRot(Vector3(rotation_scene[0], rotation_scene[1], rotation_scene[2]));
        }
    }

    // Game Camera position and rotation
    std::vector<GameCamera*> cameras = SceneCameraHandler::GetGameCameras();
	int i = 0;
	for (GameCamera* camera : cameras)
	{
        if (camera)
        {
            Vector3 cameraPosition = camera->GetLocalPosition();
            Vector3 cameraRotation = camera->GetLocalRotation();

            float position_game[3] = { cameraPosition.x, cameraPosition.y, cameraPosition.z };
            float rotation_game[3] = { cameraRotation.x * RAD2DEG, cameraRotation.y * RAD2DEG, cameraRotation.z * RAD2DEG };

            std::string name = "Game Camera " + std::to_string(i);
            ImGui::Text(name.c_str());

            // Position controls
            name = "GCam Pos " + std::to_string(i);
            if (ImGui::InputFloat3(name.c_str(), position_game))
                camera->SetPosition(Vector3(position_game[0], position_game[1], position_game[2]));

            // Rotation controls
            name = "GCam Rot " + std::to_string(i);
            if (ImGui::InputFloat3(name.c_str(), rotation_game))
            {
                rotation_game[0] *= DEG2RAD;
                rotation_game[1] *= DEG2RAD;
                rotation_game[2] *= DEG2RAD;

                camera->SetRotation(Vector3(rotation_game[0], rotation_game[1], rotation_game[2]));
            }
            i++;
        }
    }
    
    ImGui::End();
}
