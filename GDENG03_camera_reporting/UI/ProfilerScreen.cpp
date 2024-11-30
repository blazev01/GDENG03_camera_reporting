#include "ProfilerScreen.h"
#include "../EngineTime/EngineTime.h"
#include "../GameObjects/GameObjectManager.h"
#include "../SceneCamera/SceneCameraHandler.h"

ProfilerScreen::ProfilerScreen() : UIScreen("PROFILER_SCREEN")
{

}

ProfilerScreen::~ProfilerScreen()
{

}

void ProfilerScreen::DrawUI()
{
	if (ImGui::Begin("Profiler", &this->enabled))
	{
		float deltaTime = EngineTime::GetUnscaledDeltaTime();
		this->ticks += deltaTime;

		this->frameCount++;
		int fps = frameCount / this->ticks;

		if (this->ticks >= 1.0f)
		{
			this->frameCount = 0;
			this->ticks = 0.0f;
		}

		std::string fpsText = "FPS: " + std::to_string(fps);
		ImGui::Text(fpsText.c_str());

		std::string gameObjectsText = "GameObjects: " + std::to_string(GameObjectManager::GetGameObjects().size());
		ImGui::Text(gameObjectsText.c_str());
	}
	ImGui::End();
}
