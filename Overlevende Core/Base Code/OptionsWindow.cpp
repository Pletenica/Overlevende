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
	if(ImGui::Button("Add a cube", ImVec2(110, 40))) {
		//FBXLoader::ImportFBX("D:\\Documents\\GitHub\\Overlevende\\Overlevende Core\\Game\\Assets\\Basic Shapes\\Cube.fbx", ExternalApp->renderer3D->imgID);
	}
	ImGui::SameLine();
	if(ImGui::Button("Add a sphere", ImVec2(110, 40))) {
		//FBXLoader::ImportFBX("D:\\Documents\\GitHub\\Overlevende\\Overlevende Core\\Game\\Assets\\Basic Shapes\\Sphere.fbx", ExternalApp->renderer3D->imgID);
	}
	ImGui::SameLine();
	if(ImGui::Button("Add a cylinder", ImVec2(110, 40))) {
		//FBXLoader::ImportFBX("D:\\Documents\\GitHub\\Overlevende\\Overlevende Core\\Game\\Assets\\Basic Shapes\\Cylinder.fbx", ExternalApp->renderer3D->imgID);
	}
	ImGui::Checkbox("Depth Test", &depth_bool);
	ImGui::SameLine();
	ImGui::Checkbox("Cull Face", &cullface_bool);
	ImGui::SameLine();
	ImGui::Checkbox("Light", &light_bool);
	ImGui::Checkbox("Texture", &texture_bool);
	ImGui::SameLine();
	ImGui::Checkbox("WireFrame", &wireframe_bool);
	ImGui::SameLine();
	ImGui::Checkbox("Normals", &normals_bool);
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

	return true;
}

void OptionsWindow::DoCheckers()
{
	if (depth_bool == false) glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);
	if (cullface_bool == false) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);
	if (light_bool == false) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);
	if (texture_bool == true) glEnable(GL_TEXTURE_2D);
	else glDisable(GL_TEXTURE_2D);
	if (wireframe_bool == true) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}