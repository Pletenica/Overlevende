#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ComponentMesh.h"
#include "Mesh.h"

///WINDOW NOW
ComponentMesh::ComponentMesh() :Component()
{
	type = ComponentType::C_Mesh;
}

// Destructor
ComponentMesh::~ComponentMesh()
{
}

// Called before render is available
bool ComponentMesh::Enable()
{

	return true;
}

// Called before quitting
bool ComponentMesh::Disable()
{

	return true;
}

// Called before quitting
bool ComponentMesh::Update(float dt)
{
	if (active == true) {
		if (mesh != nullptr)
			mesh->Render();
	}
	return true;
}

void ComponentMesh::OnEditor()
{
	if (ImGui::CollapsingHeader("Mesh Renderer")) {
		ImGui::Checkbox("Active", &this->active);
		ImGui::SameLine();
		if (ImGui::Button("Delete Component", ImVec2(120, 20))) {
			ExternalApp->base_motor->inspector_window->_selectedGO->DeleteComponent(this);
		}
	}
}