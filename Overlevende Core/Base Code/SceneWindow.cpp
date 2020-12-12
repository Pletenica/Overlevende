#include "Globals.h"
#include "Application.h"
#include "ModuleBaseMotor.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleInput.h"

#include "WindowManager.h"
#include "SceneWindow.h"
#include "Glew/include/glew.h"
#include "InspectorWindow.h"

#include "ComponentTransform.h"
#include "ComponentMesh.h"

#include "MathGeoLib/src/Geometry/Triangle.h"
#include "MathGeoLib/src/Geometry/Frustum.h"
#include "MathGeoLib/src/Math/float4x4.h"

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
			mode,
			globMat.ptr())) {
			globMat.Transpose();

			ExternalApp->base_motor->inspector_window->_selectedGO->transform->SetTransformWithGlobal(globMat);
		}
	}

	if (ImGui::IsMouseClicked(0) && ImGuizmo::IsUsing() == false) {
		ImVec2 pos = ImGui::GetMousePos();
		ImVec2 normalized = GlobalToWindow(ImRect(ImGui::GetWindowPos().x,
			ImGui::GetWindowPos().y + ImGui::GetFrameHeight(),
			ImGui::GetWindowSize().x,
			ImGui::GetWindowSize().y - ImGui::GetFrameHeight())
			, pos);

		if ((normalized.x >= -1 && normalized.x <= 1) && (normalized.y >= -1 && normalized.y <= 1)) {
			LineSegment pick = ExternalApp->camera->_cam.frustum.UnProjectLineSegment(normalized.x, normalized.y);
			
			GameObject* go = nullptr;
			go = MeshIntersection(pick);
			ExternalApp->base_motor->inspector_window->PutNewSelectedGameObject(go);
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

void SceneWindow::ToogleModeGuizmo()
{
	if (mode == ImGuizmo::MODE::WORLD) {
		mode = ImGuizmo::MODE::LOCAL;
	}
	else {
		if (mode == ImGuizmo::MODE::LOCAL) {
			mode = ImGuizmo::MODE::WORLD;
		}
	}
}

ImVec2 SceneWindow::GlobalToWindow(ImRect _rect, ImVec2 _point)
{
	ImVec2 nPoint;

	ImVec4 _vectemp = _rect.ToVec4();

	nPoint.x = (_point.x - _vectemp.x) / ((_vectemp.x + _vectemp.z) - _vectemp.x);
	nPoint.y = (_point.y - _vectemp.y) / ((_vectemp.y + _vectemp.w) - _vectemp.y);

	nPoint.x = (nPoint.x - 0.5f) * 2;
	nPoint.y = -((nPoint.y - 0.5f) * 2);

	return nPoint;
}

GameObject* SceneWindow::MeshIntersection(LineSegment _line)
{
	GameObject* _go = nullptr;
	float closestDistance = INT_MAX;

	for (auto i = ExternalApp->renderer3D->allGameobjects.begin(); i != ExternalApp->renderer3D->allGameobjects.end(); i++) {
		if (_line.Intersects((*i)->aabb)) {
			ComponentMesh* c_mesh = (ComponentMesh*)(*i)->GetComponent(ComponentType::C_Mesh);
			if (c_mesh != nullptr) {
				LineSegment localLine = _line;
				localLine.Transform((*i)->transform->global_transform.Inverted());
				for (uint j = 0; j < c_mesh->mesh->num_indices; j+=3)
				{
					float3 pointA(&c_mesh->mesh->vertices[c_mesh->mesh->indices[j] * 3]);
					float3 pointB(&c_mesh->mesh->vertices[c_mesh->mesh->indices[j+1] * 3]);
					float3 pointC(&c_mesh->mesh->vertices[c_mesh->mesh->indices[j+2] * 3]);

					Triangle triangle(pointA, pointB, pointC);
					float cDist = 0;
					if (localLine.Intersects(triangle, &cDist, nullptr)) 
					{
						if (cDist < closestDistance) {
							closestDistance = cDist;
							_go = (*i);
						}
					}
				}
			}
			else {
				_go = (*i);
				break;
			}
		}
	}

	return _go;
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