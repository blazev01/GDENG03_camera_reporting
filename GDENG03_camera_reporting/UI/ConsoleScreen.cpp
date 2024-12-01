#include "ConsoleScreen.h"

void ConsoleScreen::AddLog(LogType type, std::string log)
{
	this->types.push_back(type);
	this->logs.push_back(log);
	this->newLine = true;
}

ConsoleScreen::ConsoleScreen() : UIScreen("CONSOLE_SCREEN")
{

}

ConsoleScreen::~ConsoleScreen()
{

}

void ConsoleScreen::DrawUI()
{
	if (ImGui::Begin("Console", &this->enabled, ImGuiWindowFlags_MenuBar))
	{
		this->ShowMenuBar();
		this->ShowLogs();

		if (this->newLine)
		{
			this->newLine = false;
			ImGui::SetScrollHereY(1.0f);
		}
	}
	ImGui::End();
}

void ConsoleScreen::ShowMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::MenuItem("Logs", (const char*)0, this->showLogs))
		{
			this->showLogs = !this->showLogs;
		}

		if (ImGui::MenuItem("Warnings", (const char*)0, this->showWarnings))
		{
			this->showWarnings = !this->showWarnings;
		}

		if (ImGui::MenuItem("Errors", (const char*)0, this->showErrors))
		{
			this->showErrors = !this->showErrors;
		}

		ImGui::EndMenuBar();
	}
}

void ConsoleScreen::ShowLogs()
{

	for (int i = 0; i < this->logs.size(); i++)
	{
		switch (this->types[i])
		{
		case LOG:
		{
			if (this->showLogs)
				ImGui::Text(this->logs[i].c_str());
			break;
		}
		case LOG_WARNING:
		{
			if (this->showWarnings)
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), this->logs[i].c_str());
			break;
		}
		case LOG_ERROR:
		{
			if (this->showErrors)
				ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), this->logs[i].c_str());
			break;
		}
		default:
			break;
		}
	}

}