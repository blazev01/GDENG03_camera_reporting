#pragma once
#include "UIScreen.h"
#include "vector"

class ConsoleScreen : public UIScreen
{
public:
	enum LogType
	{
		LOG = 0,
		LOG_WARNING = 1,
		LOG_ERROR = 2,
	};

	void AddLog(LogType type, std::string log);

protected:
	ConsoleScreen();
	~ConsoleScreen();
	virtual void DrawUI() override;

private:
	void ShowMenuBar();
	void ShowLogs();

private:
	std::vector<LogType> types;
	std::vector<std::string> logs;
	int lineNumber = 0;
	bool newLine = false;

	bool showLogs = true;
	bool showWarnings = true;
	bool showErrors = true;

	friend class UIManager;
};

