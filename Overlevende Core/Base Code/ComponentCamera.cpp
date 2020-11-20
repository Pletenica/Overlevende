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

	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);
	frustum.SetPos(float3(0, 0, 0));
	frustum.SetFront(float3::unitZ);
	frustum.SetUp(float3::unitY);
	frustum.SetViewPlaneDistances(0.1f, 1000.0f);
	frustum.SetPerspective(1.0f, 1.0f);

	frustum.GetPlanes(planes);
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

	return true;
}

void ComponentCamera::OnEditor(GameObject* _go)
{
	ImVec4 color = ImVec4(0.5f, 0.5f, 1, 1);
	ComponentMesh* c_mesh = (ComponentMesh*)_go->GetComponent(ComponentType::C_Mesh);
	if (ImGui::CollapsingHeader("Camera")) {

		ImGui::Checkbox("##isCulling", &isCulling);
		ImGui::SameLine();
		ImGui::Text("Culling");

		ImGui::PushItemWidth(90);
		if (ImGui::InputFloat("##NearPlaneInput", &nearPlaneDistance, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) {
			//Update Near Plane Distance
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Near Plane Distance");

		ImGui::PushItemWidth(90);
		if (ImGui::InputFloat("##FarPlaneInput", &farPlaneDistance, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) {
			//Update Far Plane Distance
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Far Plane Distance");

		ImGui::PushItemWidth(90);
		if (ImGui::InputFloat("##HorizontalFOVInput", &horizontalFOV, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) {
			//Update Horizontal FOV
		}
		ImGui::PopItemWidth();
		ImGui::SameLine();
		ImGui::Text("Horizontal FOV");

		ImGui::PushItemWidth(90);
		if (ImGui::InputFloat("##VerticalFOVInput", &verticalFOV, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) {
			//Update Horizontal FOV
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

}
