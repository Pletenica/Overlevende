#include "Globals.h"
#include "Application.h"
#include "SceneWindow.h"
#include "Glew/include/glew.h"

SceneWindow::SceneWindow() :Window()
{

}

// Destructor
SceneWindow::~SceneWindow()
{
}

// Called before render is available
bool SceneWindow::Init()
{
	bool ret = true;

	return ret;
}

bool SceneWindow::Draw(float dt)
{
	ImGui::Begin("Scene");
	ImGui::Image((ImTextureID)ExternalApp->renderer3D->renderTexture, ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();

	return true;
}

// Called before quitting
bool SceneWindow::CleanUp()
{

	return true;
}

// Called before quitting
bool SceneWindow::PreUpdate(float dt)
{

	return true;
}