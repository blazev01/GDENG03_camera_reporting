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
    Camera* selectedCam = SceneCameraHandler::GetCurCamera();

    Vector3 currentPosition = selectedCam->GetLocalPosition();
    Vector3 currentRotation = selectedCam->GetLocalRotation();

    float position[3] = { currentPosition.x, currentPosition.y, currentPosition.z };
    float rotation[3] = { currentRotation.x * RAD2DEG, currentRotation.y * RAD2DEG, currentRotation.z * RAD2DEG };

    ImGui::Begin("Camera Controls");

    // Position controls
    if (ImGui::InputFloat3("Position", position)) {
        if (selectedCam->GetName().find("Game Camera") == std::string::npos)
            SceneCameraHandler::SetSceneCameraPos(Vector3(position[0], position[1], position[2]));

        else
           selectedCam->SetPosition(position[0], position[1], position[2]);
    }   

    // Rotation controls
    if (ImGui::InputFloat3("Rotation", rotation)) {
        rotation[0] *= DEG2RAD;
        rotation[1] *= DEG2RAD;
        rotation[2] *= DEG2RAD;

        if (selectedCam->GetName().find("Game Camera") == std::string::npos)
            SceneCameraHandler::SetSceneCameraRot(Vector3(rotation[0], rotation[1], rotation[2]));
    
        else
            selectedCam->SetRotation(rotation[0], rotation[1], rotation[2]);
    }

    ImGui::End(); 
}
