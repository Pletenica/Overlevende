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
	ImGui::Begin("Scene", NULL, ImGuiWindowFlags_NoScrollbar);
	ImGui::Image((ImTextureID)ExternalApp->renderer3D->renderTexture, ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
	ExternalApp->camera->_cam.SetAspectRatio(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);


	ImVec2 size = ImGui::GetContentRegionMax();
	ImVec2 pos = ImGui::GetWindowPos();

	ImGuizmo::SetRect(pos.x, pos.y, size.x, size.y);
	ImGuizmo::SetDrawlist();

	if (ExternalApp->base_motor->inspector_window->_selectedGO != nullptr)
	{
		float4x4 test = ExternalApp->camera->_cam.frustum.ViewMatrix();
		test.Transpose();

		float4x4 globMat= ExternalApp->base_motor->inspector_window->_selectedGO->transform->global_transform.Transposed();

		if (ImGuizmo::Manipulate(test.v[0],
			ExternalApp->camera->_cam.frustum.ProjectionMatrix().Transposed().v[0],
			gOperation,
			ImGuizmo::MODE::LOCAL,
			globMat.ptr())) {
			globMat.Transpose();

			ExternalApp->base_motor->inspector_window->_selectedGO->transform->SetTransformWithGlobal(globMat);
		}
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