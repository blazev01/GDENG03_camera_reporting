#include "InspectorScreen.h"
#include "../SceneCamera/SceneCameraHandler.h"


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
    float rotation[3] = { currentRotation.x, currentRotation.y, currentRotation.z };

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
        if (selectedCam->GetName().find("Game Camera") == std::string::npos)
            SceneCameraHandler::SetSceneCameraRot(Vector3(rotation[0], rotation[1], rotation[2]));
    
        else
            selectedCam->SetRotation(rotation[0], rotation[1], rotation[2]);
    }

    ImGui::End(); 
}
