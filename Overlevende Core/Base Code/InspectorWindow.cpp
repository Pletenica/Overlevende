#include "Globals.h"
#include "InspectorWindow.h"
#include "Application.h"
#include "ModuleInput.h"

#include "Assimp/include/scene.h"
#include "Glew/include/glew.h"
#include "ModuleGameObject.h"

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
				_selectedGO->components[i]->OnEditor();
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
	ImGui::TextColored(ImVec4(0.5f,0.5f,1,1), _selectedGO->name.c_str());
}

void InspectorWindow::PutNewSelectedGameObject(GameObject* _go)
{
	_selectedGO = nullptr;
	_selectedGO = _go;
}

void InspectorWindow::DeleteSelectedGameObject()
{
	_selectedGO = nullptr;
}