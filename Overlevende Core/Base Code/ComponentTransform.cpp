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

void ComponentTransform::OnEditor()
{
	if (ImGui::CollapsingHeader("Transform")) {
		char* position = "";
		//ImGui::Text("X:");
		//ImGui::SameLine();
		//ImGui::InputTextEx("Y:", "hola", position, 5,ImVec2(60,20),0);
		//ImGui::SameLine();
		//ImGui::InputTextEx("Z:", "hola", position, 5, ImVec2(60, 20), 0);
		//ImGui::SameLine();
		//ImGui::InputTextEx("Position", "hola", position, 5, ImVec2(60, 20), 0);
		ImGui::Text("Position: %i  %i  %i", 1, 2, 3);
		ImGui::Text("Rotation: %i  %i  %i", 1, 2, 3);
		ImGui::Text("Scale: %i  %i  %i", 1, 2, 3);
	}
}