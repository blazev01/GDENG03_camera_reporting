#include "MenuScreen.h"
#include "UIManager.h"
#include "../GameObjects/GameObjectManager.h"
#include "../GameObjects/MeshObject.h"
#include "../Resource/MeshManager.h"
#include "../Resource/TextureManager.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "GameObjectSpawner.h"

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
		if (ImGui::SmallButton("Align with View"))
			SceneCameraHandler::AlignGameCamerasToView();

		ImGui::EndMainMenuBar();
	
	ImGui::PopStyleVar();
	}
}

void MenuScreen::ShowMenuFile()
{
	ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "//Dummy Menu");
	if (ImGui::MenuItem("New Scene")) {}
	if (ImGui::MenuItem("Save Scene")) {}
	if (ImGui::MenuItem("Save Scene As...")) {}
	ImGui::Separator();

	if (ImGui::MenuItem("Project Settings")) {}
}

void MenuScreen::ShowMenuGameObject()
{
	if (ImGui::MenuItem("Create Quad"))
	{
		GameObjectManager::CreateGameObject(GameObjectManager::QUAD);
	}

	if (ImGui::MenuItem("Create Cube"))
	{
		GameObjectManager::CreateGameObject(GameObjectManager::CUBE);
	}

	if (ImGui::MenuItem("Create Circle")) {}

	if (ImGui::MenuItem("Create Physics Cube"))
	{
		GameObjectManager::CreateGameObject(GameObjectManager::PHYSICS_CUBE);
	}
	
	if (ImGui::MenuItem("Create Physics Quad"))
	{
		GameObjectManager::CreateGameObject(GameObjectManager::PHYSICS_QUAD);
	}

	if (ImGui::MenuItem("Create Game Camera"))
	{
		GameObjectManager::CreateGameObject(GameObjectManager::GAME_CAMERA);
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
		MeshObject* mesh = (MeshObject*)GameObjectManager::CreateGameObject(GameObjectManager::MESH, true);
		mesh->SetMesh(MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\teapot.obj"));
		mesh->SetTexture(TextureManager::CreateTextureFromFile(L"..\\Assets\\Textures\\brick.png"));
	}
	
	if (ImGui::MenuItem("Create bunny"))
	{
		MeshObject* mesh = (MeshObject*)GameObjectManager::CreateGameObject(GameObjectManager::MESH);
		mesh->SetMesh(MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\bunny.obj"));
	}
	
	if (ImGui::MenuItem("Create armadillo"))
	{
		MeshObject* mesh = (MeshObject*)GameObjectManager::CreateGameObject(GameObjectManager::MESH);
		mesh->SetMesh(MeshManager::CreateMeshFromFile(L"..\\Assets\\Meshes\\armadillo.obj"));
	}

}
