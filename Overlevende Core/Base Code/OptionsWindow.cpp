#include "Globals.h"
#include "Application.h"
#include "OptionsWindow.h"
#include "Glew/include/glew.h"

#include "Mesh.h"
#include "FBXManager.h"

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
		FBXLoader::ImportFBX("/Game/Assets/Basic Shapes/Cube.fbx", ExternalApp->renderer3D->evangelion, ExternalApp->renderer3D->imgID);
	}
	ImGui::SameLine();
	if(ImGui::Button("Add a sphere", ImVec2(100, 40))) {
		FBXLoader::ImportFBX("/Game/Assets/Basic Shapes/Sphere.fbx", ExternalApp->renderer3D->evangelion, ExternalApp->renderer3D->imgID);
	}
	ImGui::SameLine();
	if(ImGui::Button("Add a cylinder", ImVec2(100, 40))) {
		FBXLoader::ImportFBX("/Game/Assets/Basic Shapes/Cylinder.fbx", ExternalApp->renderer3D->evangelion, ExternalApp->renderer3D->imgID);
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