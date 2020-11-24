#include "Globals.h"
#include "Application.h"
#include "SceneWindow.h"
#include "Glew/include/glew.h"

#include "ComponentTransform.h"

SceneWindow::SceneWindow() :Window()
{

}

// Destructor
SceneWindow::~SceneWindow()
{
}

// Called before render is available
bool SceneWindow::Init()
{
	bool ret = true;

	return ret;
}

bool SceneWindow::Draw(float dt)
{
	DoGuizmo();
	ImGui::Begin("Scene");
	ImGui::Image((ImTextureID)ExternalApp->renderer3D->renderTexture, ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
	
	ImVec2 size = ImGui::GetWindowSize();
	ImVec2 pos = ImGui::GetWindowPos();
	ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);
	ImGuizmo::SetDrawlist();
	if (ExternalApp->base_motor->inspector_window->_selectedGO != nullptr) {
		ImGuizmo::Enable(true);
		ImGuizmo::Manipulate(ExternalApp->camera->GetViewMatrix(),
			&ExternalApp->renderer3D->ProjectionMatrix,
			gOperation,
			ImGuizmo::MODE::LOCAL,
			ExternalApp->base_motor->inspector_window->_selectedGO->transform->global_transform.ptr());
	}

	ImGui::End();

	return true;
}

void SceneWindow::DoGuizmo()
{
	if (ExternalApp->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		gOperation = ImGuizmo::TRANSLATE;
	}
	if (ExternalApp->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		gOperation = ImGuizmo::ROTATE;
	}
	if (ExternalApp->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN) {
		gOperation = ImGuizmo::SCALE;
	}


}

// Called before quitting
bool SceneWindow::CleanUp()
{

	return true;
}

// Called before quitting
bool SceneWindow::PreUpdate(float dt)
{

	return true;
}