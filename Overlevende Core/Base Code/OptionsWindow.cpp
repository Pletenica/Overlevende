#include "Globals.h"
#include "Application.h"
#include "OptionsWindow.h"
#include "Glew/include/glew.h"

OptionsWindow::OptionsWindow() :Window()
{

}

// Destructor
OptionsWindow::~OptionsWindow()
{
}

// Called before render is available
bool OptionsWindow::Init()
{
	bool ret = true;

	return ret;
}

bool OptionsWindow::Draw(float dt)
{
	ImGui::Begin("Options");
	if(ImGui::Button("Add a cube", ImVec2(100, 40))) {

	}
	ImGui::SameLine();
	if(ImGui::Button("Add a pyramid", ImVec2(100, 40))) {

	}
	ImGui::SameLine();
	if(ImGui::Button("Add a mesh", ImVec2(100, 40))) {

	}
	ImGui::SameLine();
	ImGui::Checkbox("WireFrame Mode", &wireframe_bool);
	ImGui::End();
	return true;
}

// Called before quitting
bool OptionsWindow::CleanUp()
{

	return true;
}

// Called before quitting
bool OptionsWindow::PreUpdate(float dt)
{
	if (wireframe_bool == true) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	return true;
}