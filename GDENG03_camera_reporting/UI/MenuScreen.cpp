#include "MenuScreen.h"
#include "UIManager.h"
#include "../GameObjects/GameObjectManager.h"
#include "../GameObjects/MeshObject.h"
#include "../Resource/MeshManager.h"
#include "../Resource/TextureManager.h"
#include "GameObjectSpawner.h"
#include "../SaveSystem/SaveSystem.h"
#include "../SceneCamera/SceneCameraHandler.h"


MenuScreen::MenuScreen() : UIScreen("MENU_SCREEN")
{
	
}

MenuScreen::~MenuScreen()
{

}

void MenuScreen::DrawUI()
{
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
	if (ImGui::BeginMainMenuBar())
	{
		//ImGui::DockSpaceOverViewport();

		if (ImGui::BeginMenu("File"))
		{
			this->ShowMenuFile();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Game Object"))
		{
			this->ShowMenuGameObject();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			this->ShowMenuWindow();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("About"))
		{
			this->ShowMenuAbout();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Scene Cameras"))
		{
			this->ShowMenuScreenCameras();
			ImGui::EndMenu();
		}
		
		ImGui::EndMainMenuBar();
	
	ImGui::PopStyleVar();
	}
}

void MenuScreen::ShowMenuFile()
{
	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "//Dummy Menu");
	if (ImGui::MenuItem("New Scene")) 
	{
	
		GameObjectManager::DeleteAllGameObjects();

	}
	if (ImGui::MenuItem("Save Scene")) 
	{
		SaveSystem::GetInstance()->SaveScene();
	}
	if (ImGui::MenuItem("Save Scene As...")) {}
	if (ImGui::MenuItem("Load Scene"))
	{
		SaveSystem::GetInstance()->LoadScene();
	}
	ImGui::Separator();

	if (ImGui::MenuItem("Project Settings")) {}
}

void MenuScreen::ShowMenuGameObject()
{
	if (ImGui::MenuItem("Create Quad"))
	{
		GameObjectManager::CreateGameObject(QUAD);
	}

	if (ImGui::MenuItem("Create Cube"))
	{
		GameObjectManager::CreateGameObject(CUBE);
	}

	if (ImGui::MenuItem("Create Sphere"))
	{
		GameObjectManager::CreateGameObject(SPHERE);
	}

	if (ImGui::MenuItem("Create Cylinder"))
	{
		GameObjectManager::CreateGameObject(CYLINDER);
	}

	if (ImGui::MenuItem("Create Camera"))
	{
		GameObjectManager::CreateGameObject(CAMERA);
	}

	if (ImGui::MenuItem("Create Physics Cube"))
	{
		GameObjectManager::CreateGameObject(PHYSICS_CUBE);
	}
	
	if (ImGui::MenuItem("Create Physics Quad"))
	{
		GameObjectManager::CreateGameObject(PHYSICS_QUAD);
	}
	
	if (ImGui::MenuItem("Create Physics Objects"))
	{
		GameObjectSpawner::SpawnPhysicsObjects();
	}

	if (ImGui::BeginMenu("Create Mesh"))
	{
		this->ShowMenuCreateMesh();
		ImGui::EndMenu();
	}
}

void MenuScreen::ShowMenuWindow()
{
	if (ImGui::MenuItem("Inspector"))
	{
		UIManager::SetEnabled(this->uiNames.INSPECTOR_SCREEN, true);
	}

	if (ImGui::MenuItem("Outliner"))
	{
		UIManager::SetEnabled(this->uiNames.OUTLINER_SCREEN, true);
	}
	
	if (ImGui::MenuItem("Profiler"))
	{
		UIManager::SetEnabled(this->uiNames.PROFILER_SCREEN, true);
	}
	
	if (ImGui::MenuItem("Console"))
	{
		UIManager::SetEnabled(this->uiNames.CONSOLE_SCREEN, true);
	}

	if (ImGui::MenuItem("Color Picker"))
	{
		UIManager::SetEnabled(this->uiNames.COLOR_PICKER_SCREEN, true);
	}

	ImGui::Separator();

	if (ImGui::BeginMenu("Themes"))
	{
		this->ShowMenuThemes();
		ImGui::EndMenu();
	}
}

void MenuScreen::ShowMenuAbout()
{
	if (ImGui::MenuItem("Credits"))
	{
		UIManager::SetEnabled(this->uiNames.CREDITS_SCREEN, true);
	}
}

void MenuScreen::ShowMenuScreenCameras()
{
	if (ImGui::MenuItem("Create Scene Camera"))
	{
		SceneCameraHandler::AddSceneCamera();
	}
	if (ImGui::MenuItem("Scene Cameras Cycle Forward"))
	{
		SceneCameraHandler::CycleGameCamerasForward();
	}
	if (ImGui::MenuItem("Scene Cameras Cycle Backward"))
	{
		SceneCameraHandler::CycleGameCamerasBackward();
	}
	if (ImGui::MenuItem("Delete Last Scene Camera"))
	{
		SceneCameraHandler::DeleteSceneCamera(SceneCameraHandler::GetSceneCameras().size()-1);
	}

}

void MenuScreen::ShowMenuThemes()
{
	if (ImGui::MenuItem("Dark"))
	{
		ImGui::StyleColorsDark();
	}

	if (ImGui::MenuItem("Light"))
	{
		ImGui::StyleColorsLight();
	}

	if (ImGui::MenuItem("Classic"))
	{
		ImGui::StyleColorsClassic();
	}

	if (ImGui::MenuItem("Crimson"))
	{
		this->styles.StyleColorsCrimson();
	}

	if (ImGui::MenuItem("Evangelion"))
	{
		this->styles.StyleColorsEvangelion();
	}
}

void MenuScreen::ShowMenuCreateMesh()
{
	if (ImGui::MenuItem("Create teapot"))
	{
		MeshObject* mesh = (MeshObject*)GameObjectManager::CreateGameObject(MESH, true);
		mesh->SetMesh(MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\teapot.obj"));
		mesh->SetTexture(TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\brick.png"));
	}
	
	if (ImGui::MenuItem("Create bunny"))
	{
		MeshObject* mesh = (MeshObject*)GameObjectManager::CreateGameObject(MESH, true);
		mesh->SetMesh(MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\bunny.obj"));
		mesh->SetTexture(TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\placeholder.jpg"));
	}
	
	if (ImGui::MenuItem("Create armadillo"))
	{
		MeshObject* mesh = (MeshObject*)GameObjectManager::CreateGameObject(MESH, true);
		mesh->SetMesh(MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\armadillo.obj"));
		mesh->SetTexture(TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\placeholder.jpg"));
	}

}
