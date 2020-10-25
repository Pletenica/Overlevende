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
		
		for (int i = 0; i < _selectedGO->components.size(); i++) {
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
	ImGui::Checkbox(" ", &_selectedGO->active);
	ImGui::SameLine();
	ImGui::InputText(" ", name_chars, sizeof(name_chars));
	ImGui::Spacing();
}

void InspectorWindow::CreateMaterialTab(int i)
{
	ComponentMaterial* _compMat = (ComponentMaterial*)_selectedGO->components[i];
	if (ImGui::CollapsingHeader("Material")) {
		ImGui::Text("Hola.");
	}
}

void InspectorWindow::CreateMeshTab(int i)
{
	ComponentMesh* _compMesh = (ComponentMesh*)_selectedGO->components[i];
	if (ImGui::CollapsingHeader("Mesh Renderer")) {
		ImGui::Text("","",20);
	}
}

void InspectorWindow::CreateTransformTab(int i)
{
	ComponentTransform *_compTrans = (ComponentTransform*)_selectedGO->components[i];
	if (ImGui::CollapsingHeader("Transform")) {
		ImGui::Text("Position:");
		ImGui::SameLine();
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