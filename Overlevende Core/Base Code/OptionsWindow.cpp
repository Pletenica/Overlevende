#include "Globals.h"
#include "Application.h"
#include "OptionsWindow.h"
#include "Glew/include/glew.h"

#include "Mesh.h"
#include "FBXManager.h"
#include "ComponentMesh.h"
#include "Time.h"

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
		ExternalApp->file_system->LoadFileFromPath("Assets/FBXs/Cube.fbx");
	}
	ImGui::SameLine();
	if(ImGui::Button("Add a sphere", ImVec2(110, 40))) {
		ExternalApp->file_system->LoadFileFromPath("Assets/FBXs/Sphere.fbx");
	}
	ImGui::SameLine();
	if(ImGui::Button("Add a cylinder", ImVec2(110, 40))) {
		ExternalApp->file_system->LoadFileFromPath("Assets/FBXs/Cylinder.fbx");
	}
	ImGui::SameLine();
	if (ImGui::Button("Add a plane", ImVec2(110, 40))) {
		ExternalApp->file_system->LoadFileFromPath("Assets/FBXs/Plane.fbx");
	}
	ImGui::SameLine(ImGui::GetWindowWidth() - 210);
	if (ImGui::Button("Play", ImVec2(60, 40))) {
		//Do the play configuration
		Time::Start();
		ExternalApp->scene_intro->Save("Library/Scenes/temp_Scene.json");
	}
	ImGui::SameLine();
	if (ImGui::Button("Pause", ImVec2(60, 40))) {
		//Do the pause configuration
		Time::Pause();
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop", ImVec2(60, 40))) {
		//Do the stop configuration
		Time::Stop();
		ExternalApp->scene_intro->Load("Library/Scenes/temp_Scene.json");
	}

	ImGui::Checkbox("Depth Test", &depth_bool);
	ImGui::SameLine();
	ImGui::Checkbox("Cull Face", &cullface_bool);
	ImGui::SameLine();
	ImGui::Checkbox("Light", &light_bool);
	ImGui::SameLine();
	ImGui::Checkbox("Texture", &texture_bool);
	ImGui::Checkbox("AABB Draw", &drawaabb_bool);
	ImGui::SameLine();
	ImGui::Checkbox("OBB Draw", &drawobb_bool);
	ImGui::SameLine();
	ImGui::Checkbox("Wireframe", &wireframe_bool);
	ImGui::SameLine();
	if (ImGui::Checkbox("Normals", &normals_bool)) {
		if (normals_bool == true) RecursiveNormals(ExternalApp->scene_intro->rootGO, true);
		else RecursiveNormals(ExternalApp->scene_intro->rootGO, false);
	}
	ImGui::SameLine(ImGui::GetWindowWidth() - 65);
	if (ImGui::Button(worldorlocalguizmo.c_str(), ImVec2(50, 20))) {
		if (worldorlocalguizmo == "WORLD") {
			worldorlocalguizmo = "LOCAL";

		}
		else if (worldorlocalguizmo == "LOCAL") {
			worldorlocalguizmo = "WORLD";
		}
		ExternalApp->base_motor->scene_window->ToogleModeGuizmo();
	}

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

void OptionsWindow::RecursiveNormals(GameObject* node, bool _active)
{
	ComponentMesh* c_mesh = (ComponentMesh*)node->GetComponent(ComponentType::C_Mesh);

	if (c_mesh != nullptr) {
		c_mesh->drawFaceNormals = _active;
		c_mesh->drawVertexNormals = _active;
	}
	if (node->active == true) {
		for (size_t i = 0; i < node->children.size(); i++)
		{
			RecursiveNormals(node->children[i], _active);
		}
	}
}