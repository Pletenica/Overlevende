#include "Globals.h"
#include "InspectorWindow.h"
#include "Application.h"
#include "ModuleInput.h"

#include "Glew/include/glew.h"
#include "ModuleGameObject.h"

#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"

InspectorWindow::InspectorWindow():Window()
{
	_selectedGO = new GameObject;
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
	if (_selectedGO != nullptr) {
		CreateInitTab();
		
		if (_selectedGO != nullptr) {
			for (int i = 0; i < _selectedGO->components.size(); i++) {
				if (_selectedGO->components[i] != nullptr) {
					if (_selectedGO->components[i]->type == ComponentType::C_Transform) {
						CreateTransformTab(i);
					}
					if (_selectedGO->components[i]->type == ComponentType::C_Mesh) {
						CreateMeshTab(i);
					}
					if (_selectedGO->components[i]->type == ComponentType::C_Material) {
						CreateMaterialTab(i);
					}
				}
			}
		}
	}
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
	if (ExternalApp->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {
		DeleteSelectedGameObject();
	}
	return true;
}

void InspectorWindow::CreateInitTab()
{
	static char name_chars[20] = {};
	ImGui::Text("Options");
	ImGui::Checkbox(" Name:", &_selectedGO->active);
	ImGui::SameLine();
	const char* string_name = _selectedGO->name.c_str();
	ImGui::InputText("", name_chars, sizeof(name_chars));
	if (ImGui::Button("Delete GameObject", ImVec2(130, 20))) {
		//Delete GameObject from list into scene
		ExternalApp->scene_intro->DeleteGameObject(_selectedGO);
		//Put null the gameobject inspector properties (clean)
		_selectedGO = nullptr;
	}
}

void InspectorWindow::CreateMaterialTab(int i)
{
	ComponentMaterial* _compMat = (ComponentMaterial*)_selectedGO->components[i];
	if (ImGui::CollapsingHeader("Material")) {
		ImGui::Checkbox(" ", &_selectedGO->components[i]->active);
		ImGui::SameLine();
		if (ImGui::Button("Delete Component", ImVec2(120, 20))) {
			_selectedGO->DeleteComponent(_compMat);
		}
	}
}

void InspectorWindow::CreateMeshTab(int i)
{
	ComponentMesh* _compMesh = (ComponentMesh*)_selectedGO->components[i];
	if (ImGui::CollapsingHeader("Mesh Renderer")) {
		ImGui::Checkbox(" ", &_selectedGO->components[i]->active);
		ImGui::SameLine();
		if (ImGui::Button("Delete Component", ImVec2(120,20))) {
			_selectedGO->DeleteComponent(_compMesh);
		}
	}
}

void InspectorWindow::CreateTransformTab(int i)
{
	ComponentTransform *_compTrans = (ComponentTransform*)_selectedGO->components[i];
	if (ImGui::CollapsingHeader("Transform")) {
		ImGui::Checkbox(" ", &_selectedGO->components[i]->active);
		ImGui::SameLine();
		if (ImGui::Button("Delete Component", ImVec2(120, 20))) {
			_selectedGO->DeleteComponent(_compTrans);
		}
		ImGui::Text("Position:");
	}
}

void InspectorWindow::PutNewSelectedGameObject(GameObject* _go)
{
	_selectedGO = _go;
}

void InspectorWindow::DeleteSelectedGameObject()
{
	_selectedGO = nullptr;
}