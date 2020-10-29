#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"

///WINDOW NOW
ComponentMaterial::ComponentMaterial() :Component()
{
	type = ComponentType::C_Material;
}

// Destructor
ComponentMaterial::~ComponentMaterial()
{
}

// Called before render is available
bool ComponentMaterial::Enable()
{

	return true;
}

// Called before quitting
bool ComponentMaterial::Disable()
{

	return true;
}



// Called before quitting
bool ComponentMaterial::Update(float dt)
{

	return true;
}

void ComponentMaterial::ChangeTexture(GLuint _id, ComponentMesh* _mesh)
{
	if (_mesh != nullptr) {
		_mesh->mesh->textureID = _id;
	}
}

void ComponentMaterial::OnEditor()
{
	if (ImGui::CollapsingHeader("Material")) {
		ImGui::Checkbox(" ", &this->active);
		ImGui::SameLine();
		if (ImGui::Button("Delete Component", ImVec2(120, 20))) {
			ExternalApp->base_motor->inspector_window->_selectedGO->DeleteComponent(this);
		}
		if (ImGui::Checkbox("Checker Material", &putCheckMaterial)) {
			ChangeTex();
		}
		ImTextureID id = (ImTextureID)textureID;
		ImGui::Image(id, ImVec2(100, 100));
		if (texturePath != "") {
			ImGui::TextColored(ImVec4(0.5f, 0.5f, 1, 1), texturePath.c_str());
		}
	}
}

void ComponentMaterial::ChangeTex()
{
	ComponentMesh* c_mesh = (ComponentMesh*)ExternalApp->base_motor->inspector_window->_selectedGO->GetComponent(ComponentType::C_Mesh);
	if (ExternalApp->base_motor->inspector_window->_selectedGO != nullptr) {
		if (putCheckMaterial == true) {
			if (c_mesh != nullptr) {
				ChangeTexture((GLuint)ExternalApp->renderer3D->checkerImage, c_mesh);
			}
		}
		else {
			ChangeTexture(textureID, c_mesh);
		}
	}
}