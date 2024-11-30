#include "ConsoleScreen.h"

void ConsoleScreen::AddLog(LogType type, std::string log)
{
	this->types.push_back(type);
	this->logs.push_back(log);
}

ConsoleScreen::ConsoleScreen() : UIScreen("CONSOLE_SCREEN")
{

}

ConsoleScreen::~ConsoleScreen()
{

}

void ConsoleScreen::DrawUI()
{
	if (ImGui::Begin("Console", &this->enabled))
	{
		for (int i = 0; i < this->logs.size(); i++)
		{
			switch (this->types[i])
			{
			case LOG:
			{
				ImGui::Text(this->logs[i].c_str());
				break;
			}
			case LOG_WARNING:
			{
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), this->logs[i].c_str());
				break;
			}
			case LOG_ERROR:
			{
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), this->logs[i].c_str());
				break;
			}
			default:
				break;
			}
		}
	}
	ImGui::End();
}
