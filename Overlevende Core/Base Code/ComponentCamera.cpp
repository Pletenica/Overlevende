#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ComponentCamera.h"
#include "MathGeoLib/Geometry/Frustum.h"
#include "MathGeoLib/MathGeoLib.h"

#include "JSONManager.h"

///WINDOW NOW
ComponentCamera::ComponentCamera(GameObject* _go) :Component(_go)
{
	gameobject = _go;
	type = ComponentType::C_Camera;

	horizontalFOV = 1.0f;
	verticalFOV = 1.0f;
	nearPlaneDistance = 0.1f;
	farPlaneDistance = 50;

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetPos(float3(0, 0, 0));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	frustum.SetViewPlaneDistances(nearPlaneDistance, farPlaneDistance);
	frustum.SetPerspective(horizontalFOV, verticalFOV);
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
	float3 points[8];

	frustum.GetCornerPoints(points);

	if (ExternalApp->base_motor->configuration_window->isBlueColor) {
		glColor3f(0, 0, 1);
	}
	if (ExternalApp->base_motor->configuration_window->isOrangeColor) {
		glColor3f(1, 0, 0);
	}
	if (ExternalApp->base_motor->configuration_window->isGreenColor) {
		glColor3f(0, 1, 0);
	}

	glLineWidth(5);
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

	return true;
}

void ComponentCamera::OnEditor(GameObject* _go)
{
	ImVec4 color = ImVec4(0.5f, 0.5f, 1, 1);

	if (ImGui::CollapsingHeader("Camera")) {

		ImGui::Checkbox("##isCulling", &isCulling);
		ImGui::SameLine();
		ImGui::Text("Culling");

		ImGui::PushItemWidth(90);
		if (ImGui::InputFloat("##NearPlaneInput", &nearPlaneDistance, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) {
			//Update Near Plane Distance
			frustum.SetViewPlaneDistances(nearPlaneDistance, farPlaneDistance);
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Near Plane Distance");

		ImGui::PushItemWidth(90);
		if (ImGui::InputFloat("##FarPlaneInput", &farPlaneDistance, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) {
			frustum.SetViewPlaneDistances(nearPlaneDistance, farPlaneDistance);
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Far Plane Distance");

		ImGui::PushItemWidth(90);
		if (ImGui::InputFloat("##HorizontalFOVInput", &horizontalFOV, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) {
			//Update Horizontal FOV
			frustum.SetPerspective(horizontalFOV, verticalFOV);
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Horizontal FOV");

		ImGui::PushItemWidth(90);
		if (ImGui::InputFloat("##VerticalFOVInput", &verticalFOV, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) {
			//Update Horizontal FOV
			frustum.SetPerspective(horizontalFOV, verticalFOV);
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Vertical FOV");
	}
}

void ComponentCamera::SaveComponent(JsonManager* _man)
{
	Component::SaveComponent(_man);

	_man->AddFloat("Vertical FOV", verticalFOV);
	_man->AddFloat("Horizontal FOV", horizontalFOV);
	_man->AddFloat("Far Plane Distance", farPlaneDistance);
	_man->AddFloat("Near Plane Distance", nearPlaneDistance);
}

void ComponentCamera::LoadComponent(JsonManager* _man)
{
	verticalFOV = _man->GetFloat("Vertical FOV");
	horizontalFOV = _man->GetFloat("Horizontal FOV");
	farPlaneDistance = _man->GetFloat("Far Plane Distance");
	nearPlaneDistance = _man->GetFloat("Near Plane Distance");
}
