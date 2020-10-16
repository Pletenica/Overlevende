#include "Globals.h"
#include "Application.h"
#include "ConsoleWindow.h"
#include "Glew/include/glew.h"

ConsoleWindow::ConsoleWindow() :Window()
{
}

// Destructor
ConsoleWindow::~ConsoleWindow()
{
}

// Called before render is available
bool ConsoleWindow::Init()
{
	bool ret = true;

	return ret;
}

bool ConsoleWindow::Draw(float dt)
{
	ImGui::Begin("Console", NULL);
	for (int i = 0; i < console_log.size(); i++)
	{
		ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), console_log[i].c_str());
	}
	ImGui::End();

	return true;
}

// Called before quitting
bool ConsoleWindow::CleanUp()
{
	console_log.clear();
	return true;
}

void ConsoleWindow::AddConsoleLog(const char* log)
{
	std::string message = log;
	console_log.push_back(message);
}