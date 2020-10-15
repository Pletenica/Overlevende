#include "Globals.h"
#include "Application.h"
#include "InspectorWindow.h"
#include "Glew/include/glew.h"

InspectorWindow::InspectorWindow():Window()
{

}

// Destructor
InspectorWindow::~InspectorWindow()
{
}

// Called before render is available
bool InspectorWindow::Init()
{
	bool ret = true;

	return ret;
}

bool InspectorWindow::Draw(float dt)
{
	ImGui::Begin("Inspector");
	ImGui::Text("This is the Inspector.");
	if (ImGui::Checkbox("WireFrame Mode", &wireframe_bool)) {
		(wireframe_bool) ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	ImGui::End();
	return true;
}

// Called before quitting
bool InspectorWindow::CleanUp()
{

	return true;
}