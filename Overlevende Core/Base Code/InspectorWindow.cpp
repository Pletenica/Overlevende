#include "Globals.h"
#include "InspectorWindow.h"
#include "Application.h"
#include "ModuleInput.h"

#include "Assimp/include/scene.h"
#include "Glew/include/glew.h"
#include "ModuleGameObject.h"

#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"

InspectorWindow::InspectorWindow():Window()
{
	_selectedGO = new GameObject;
	_selectedGO = nullptr;
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
				if (_selectedGO != nullptr && _selectedGO->components[i] != nullptr) {
					if (_selectedGO->components[i]!=nullptr && _selectedGO->components[i]->type == ComponentType::C_Transform) {
						CreateTransformTab(i);
					}
					if (_selectedGO->components[i] != nullptr && _selectedGO->components[i]->type == ComponentType::C_Mesh) {
						CreateMeshTab(i);
					}
					if (_selectedGO->components[i] != nullptr && _selectedGO->components[i]->type == ComponentType::C_Material) {
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
	/*delete(_selectedGO);*/
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
	ImGui::InputText("/", name_chars, sizeof(name_chars));

	if (ImGui::Button("Delete GameObject", ImVec2(130, 20))) {
		//Delete GameObject from list into scene
		_selectedGO = nullptr;
		ExternalApp->scene_intro->DeleteGameObject(_selectedGO);
		//Put null the gameobject inspector properties (clean)

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
		if(ImGui::Checkbox("Checker Material", &putCheckMaterial)) {
			ChangeTex();
		}
		ImTextureID id = (ImTextureID)c_mat->textureID;
		ImGui::Image(id, ImVec2(100, 100));
		ImGui::SameLine();
		//std::string _imagePath = "Assets/FBXs/" + c_mesh->mesh.
		//ImGui::Text();
	}
}

void InspectorWindow::CreateMeshTab(int i)
{
	ComponentMesh* _compMesh = (ComponentMesh*)_selectedGO->components[i];
	if (ImGui::CollapsingHeader("Mesh Renderer")) {
		ImGui::Checkbox("Active", &_selectedGO->components[i]->active);
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
		ImGui::Text("Position: %i  %i  %i", 1,2,3);
		ImGui::Text("Rotation: %i  %i  %i", 1, 2, 3);
		ImGui::Text("Scale: %i  %i  %i", 1, 2, 3);
	}
}

void InspectorWindow::PutNewSelectedGameObject(GameObject* _go)
{
	_selectedGO = nullptr;
	_selectedGO = _go;
	c_mat = (ComponentMaterial*)_selectedGO->GetComponent(ComponentType::C_Material);
	c_mesh = (ComponentMesh*)_selectedGO->GetComponent(ComponentType::C_Mesh);
	c_transform = (ComponentTransform*)_selectedGO->GetComponent(ComponentType::C_Transform);
	if (c_mat != nullptr) {
		mainMeshTextureID = c_mat->textureID;
	}
}

void InspectorWindow::DeleteSelectedGameObject()
{
	_selectedGO = nullptr;
	mainMeshTextureID = NULL;
}

void InspectorWindow::ChangeTex()
{
	if (_selectedGO != nullptr) {
		if (putCheckMaterial == true) {
			if (c_mat != nullptr && c_mesh !=nullptr) {
				c_mat->ChangeTexture((GLuint)ExternalApp->renderer3D->checkerImage, c_mesh);
			}
		}
		else {
			c_mat = (ComponentMaterial*)_selectedGO->GetComponent(ComponentType::C_Material);
			c_mat->ChangeTexture(mainMeshTextureID, c_mesh);
		}
	}
}