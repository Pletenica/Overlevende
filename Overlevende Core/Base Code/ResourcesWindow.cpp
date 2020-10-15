#include "Globals.h"
#include "Application.h"
#include "ResourcesWindow.h"
#include "Glew/include/glew.h"

ResourcesWindow::ResourcesWindow() :Window()
{

}

// Destructor
ResourcesWindow::~ResourcesWindow()
{
}

// Called before render is available
bool ResourcesWindow::Init()
{
	bool ret = true;

	return ret;
}

bool ResourcesWindow::Draw(float dt)
{
	ImGui::Begin("Resources", NULL);
	ImGui::Text("This is the resources.");
	ImGui::End();

	ImGui::Begin("Explorator", NULL);
	ImGui::Text("This is an explorator.");
	ImGui::End();

	return true;
}

// Called before quitting
bool ResourcesWindow::CleanUp()
{

	return true;
}