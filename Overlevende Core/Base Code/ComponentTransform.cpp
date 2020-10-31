#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ComponentTransform.h"
#include "MathGeoLib/Math/float3.h"
#include "MathGeoLib/Math/Quat.h"


#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

///WINDOW NOW
ComponentTransform::ComponentTransform() :Component()
{
	type = ComponentType::C_Transform;
	position = { 0,0,0 };
	rotation = { 0,0,0 };
	scale = { 1,1,1 };
}

// Destructor
ComponentTransform::~ComponentTransform()
{
}

// Called before render is available
bool ComponentTransform::Enable()
{

	return true;
}

// Called before quitting
bool ComponentTransform::Disable()
{

	return true;
}

// Called before quitting
bool ComponentTransform::Update(float dt)
{
	//node->mTransformation.Decompose(scaling, rotation, translation);
	//
	//float3 pos(translation.x, translation.y, translation.z);
	//float3 scale(scaling.x, scaling.y, scaling.z);
	//Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

	return true;
}

void ComponentTransform::OnEditor(GameObject* _go)
{
	ComponentTransform* transform = (ComponentTransform*)_go->GetComponent(ComponentType::C_Transform);
	
	if (ImGui::CollapsingHeader("Transform")) {
		///////// POSITION ///////////
		float3 pos = transform->position;
		bool newPos = false;

		ImGui::Text("Position");

		ImGui::Text("X");
		ImGui::SameLine();
		ImGui::PushItemWidth(70);
		if (ImGui::InputFloat("##posx", &pos.x, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) newPos = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Text("Y");
		ImGui::SameLine();
		ImGui::PushItemWidth(70);
		if (ImGui::InputFloat("##posy", &pos.y, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) newPos = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Text("Z");
		ImGui::SameLine();
		ImGui::PushItemWidth(70);
		if (ImGui::InputFloat("##posz", &pos.z, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) newPos = true;
		ImGui::PopItemWidth();
		if (newPos) _go->transform->position = pos;

		///////// ROTATION ///////////
		float3 rot = transform->rotation;
		bool newRot = false;

		ImGui::Text("Rotation");

		ImGui::Text("X");
		ImGui::SameLine();
		ImGui::PushItemWidth(70);
		if (ImGui::InputFloat("##rotx", &rot.x, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) newRot = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Text("Y");
		ImGui::SameLine();
		ImGui::PushItemWidth(70);
		if (ImGui::InputFloat("##roty", &rot.y, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) newRot = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Text("Z");
		ImGui::SameLine();
		ImGui::PushItemWidth(70);
		if (ImGui::InputFloat("##rotz", &rot.z, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) newRot = true;
		ImGui::PopItemWidth();
		if (newRot) _go->transform->rotation = rot;

		///////// SCALE ///////////
		float3 scale = transform->scale;
		bool newScale = false;

		ImGui::Text("Scale");

		ImGui::Text("X");
		ImGui::SameLine();
		ImGui::PushItemWidth(70);
		if (ImGui::InputFloat("##scalex", &scale.x, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) newScale = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Text("Y");
		ImGui::SameLine();
		ImGui::PushItemWidth(70);
		if (ImGui::InputFloat("##scaley", &scale.y, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) newScale = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::Text("Z");
		ImGui::SameLine();
		ImGui::PushItemWidth(70);
		if (ImGui::InputFloat("##scalez", &scale.z, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)) newScale = true;
		ImGui::PopItemWidth();
		if (newScale) _go->transform->scale = scale;
	}
}

void ComponentTransform::SetTransform(float3 _pos, Quat _rot, float3 _scale)
{
	position = _pos;
	rotation = _rot.ToEulerXYZ()*RADTODEG;
	scale = _scale;

	local_transform.FromTRS(position, _rot, scale);
}