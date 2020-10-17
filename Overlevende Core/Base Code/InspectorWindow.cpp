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
	ImGui::Checkbox("WireFrame Mode", &wireframe_bool);
	ImGui::End();

	return true;
}

// Called before quitting
bool InspectorWindow::CleanUp()
{

	return true;
}

// Called before quitting
bool InspectorWindow::PreUpdate(float dt)
{
	if (wireframe_bool == true) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	return true;
}