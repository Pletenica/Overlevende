#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ModuleSceneIntro.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"
#include "MathGeoLib/src/Geometry/Frustum.h"
#include "MathGeoLib/src/MathGeoLib.h"

#include "ModuleRenderer3D.h"
#include "JSONManager.h"
#include "glmath.h"

//Include ImGui
#include "Glew/include/glew.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"

///WINDOW NOW
ComponentCamera::ComponentCamera(GameObject* _go) :Component(_go)
{
	gameobject = _go;
	type = ComponentType::C_Camera;

	frustum.type = FrustumType::PerspectiveFrustum;

	frustum.verticalFov = 40.f;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov / 2) * (16 / 9));

	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 300.f;

	frustum.pos = (float3(0, 0, 0));
	frustum.front = (float3::unitZ);
	frustum.up = (float3::unitY);
	//frustum.SetPerspective(horizontalFOV, verticalFOV);

	gameobject->UpdateAABB();
}

ComponentCamera::ComponentCamera(float3 pos) :Component(nullptr)
{
	gameobject = nullptr;
	type = ComponentType::C_Camera;

	frustum.type = FrustumType::PerspectiveFrustum;

	frustum.verticalFov = 40.f * DEGTORAD;
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov / 2) * (16 / 9));

	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 300.f;

	frustum.pos = pos;
	frustum.front = (float3::unitZ);
	frustum.up = (float3::unitY);
}

// Destructor
ComponentCamera::~ComponentCamera()
{
}

// Called before render is available
bool ComponentCamera::Enable()
{

	return true;
}

// Called before quitting
bool ComponentCamera::Disable()
{

	return true;
}

// Called before quitting
bool ComponentCamera::Update(float dt)
{
	UpdateCamera(gameobject->transform->global_transform);
	ExternalApp->renderer3D->allGameobjects.push_back(gameobject);
	float3 points[8];

	frustum.GetCornerPoints(points);

	glColor3f(1, 0, 0);
	glLineWidth(3);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);

	glVertex3fv(&points[0].x);
	glVertex3fv(&points[2].x);
	glVertex3fv(&points[2].x);
	glVertex3fv(&points[6].x);

	glVertex3fv(&points[6].x);
	glVertex3fv(&points[4].x);
	glVertex3fv(&points[4].x);
	glVertex3fv(&points[0].x);

	glVertex3fv(&points[0].x);
	glVertex3fv(&points[1].x);
	glVertex3fv(&points[1].x);
	glVertex3fv(&points[3].x);

	glVertex3fv(&points[3].x);
	glVertex3fv(&points[2].x);
	glVertex3fv(&points[4].x);
	glVertex3fv(&points[5].x);
	glVertex3fv(&points[6].x);
	glVertex3fv(&points[7].x);
	glVertex3fv(&points[5].x);
	glVertex3fv(&points[7].x);
	glVertex3fv(&points[3].x);
	glVertex3fv(&points[7].x);
	glVertex3fv(&points[1].x);
	glVertex3fv(&points[5].x);

	glEnd();
	glLineWidth(1);
	glColor3f(1, 1, 1);
	glEnable(GL_LIGHTING);

	return true;
}

void ComponentCamera::OnEditor(GameObject* _go)
{
	ImVec4 color = ImVec4(0.5f, 0.5f, 1, 1);

	if (ImGui::CollapsingHeader("Camera")) {

		ImGui::PushItemWidth(150);
		if (ImGui::DragFloat("##PriorityInput", &priority, 0.1f, 0, 100)) {
			ExternalApp->scene_intro->GetActualCameraToCull(ExternalApp->scene_intro->rootGO);
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Priority");

		ImGui::Checkbox("##isCulling", &isCulling);
		ImGui::SameLine();
		ImGui::Text("Culling");

		ImGui::PushItemWidth(90);
		ImGui::DragFloat("##NearPlaneInput", &frustum.nearPlaneDistance, 0.1f, 1.0f, frustum.farPlaneDistance);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Near Plane Distance");

		ImGui::PushItemWidth(90);
		ImGui::DragFloat("##FarPlaneInput", &frustum.farPlaneDistance, 0.1f, frustum.nearPlaneDistance, 3000.f);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Far Plane Distance");

		ImGui::PushItemWidth(90);
		if (ImGui::DragFloat("##General FOV", &degFov, 0.1f, 1.0f, 180.f)) {
			//Update Horizontal FOV
			frustum.verticalFov = degFov * DEGTORAD;
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Vertical FOV");
	}
}

void ComponentCamera::SaveComponent(JsonManager* _man)
{
	Component::SaveComponent(_man);

	_man->AddFloat("Prority", priority);
	_man->AddFloat("Vertical FOV", frustum.verticalFov);
	_man->AddFloat("Horizontal FOV", frustum.horizontalFov);
	_man->AddFloat("Far Plane Distance", frustum.farPlaneDistance);
	_man->AddFloat("Near Plane Distance", frustum.nearPlaneDistance);
}

void ComponentCamera::LoadComponent(JsonManager* _man)
{
	priority = _man->GetFloat("Prority");
	frustum.verticalFov = _man->GetFloat("Vertical FOV");
	frustum.horizontalFov = _man->GetFloat("Horizontal FOV");
	frustum.farPlaneDistance = _man->GetFloat("Far Plane Distance");
	frustum.nearPlaneDistance = _man->GetFloat("Near Plane Distance");
}

void ComponentCamera::UpdateCamera(const float4x4& global)
{
	float3 pos, scale;
	Quat rot;

	global.Decompose(pos, rot, scale);

	frustum.pos = pos;
	frustum.front = global.WorldZ();
	frustum.up = global.WorldY();
}

void ComponentCamera::SetAspectRatio(float wi, float he)
{
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov / 2) * (wi / he));
}
