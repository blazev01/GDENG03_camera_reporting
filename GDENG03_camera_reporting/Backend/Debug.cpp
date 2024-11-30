#include "Debug.h"
#include "../UI/UIManager.h"
#include "../UI/ConsoleScreen.h"

void Debug::Log(std::string message)
{
	UINames uiNames;
	ConsoleScreen* console = (ConsoleScreen*)UIManager::GetUIScreen(uiNames.CONSOLE_SCREEN);
	console->AddLog(ConsoleScreen::LOG, "LOG: " + message);
}

void Debug::LogWarning(std::string message)
{
	UINames uiNames;
	ConsoleScreen* console = (ConsoleScreen*)UIManager::GetUIScreen(uiNames.CONSOLE_SCREEN);
	console->AddLog(ConsoleScreen::LOG_WARNING, "WARNING: " + message);
}

void Debug::LogError(std::string message)
{
	UINames uiNames;
	ConsoleScreen* console = (ConsoleScreen*)UIManager::GetUIScreen(uiNames.CONSOLE_SCREEN);
	console->AddLog(ConsoleScreen::LOG_ERROR, "ERROR: " + message);
}
