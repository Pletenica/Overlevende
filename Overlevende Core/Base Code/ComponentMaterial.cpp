#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "FBXManager.h"
#include "ModuleFileSystem.h"

#include"Devil/include/ilu.h"
#include"Devil/include/ilut.h"

///WINDOW NOW
ComponentMaterial::ComponentMaterial(GameObject* _go) :Component(_go)
{
	gameobject = _go;
	type = ComponentType::C_Material;
}

// Destructor
ComponentMaterial::~ComponentMaterial()
{
}

// Called before render is available
bool ComponentMaterial::Enable()
{

	return true;
}

// Called before quitting
bool ComponentMaterial::Disable()
{

	return true;
}



// Called before quitting
bool ComponentMaterial::Update(float dt)
{

	return true;
}

void ComponentMaterial::ChangeTexture(GLuint _id, ComponentMesh* _mesh)
{
	if (_mesh != nullptr) {
		_mesh->mesh->textureID = _id;
	}
}

void ComponentMaterial::SaveComponent(JsonManager* _man)
{
	Component::SaveComponent(_man);

	_man->AddString("Material Path", textureLibraryPath.c_str());
}

void ComponentMaterial::LoadComponent(JsonManager* _man)
{
	std::string mPath = _man->GetString("Material Path");
	
	char* buffer = nullptr;
	std::string _p = mPath.substr(mPath.find_last_of("/"));
	std::string _texname = _p.substr(1, _p.find_first_of(".")-1);
	int size = ExternalApp->file_system->Load(mPath.c_str(), &buffer);
	
	ComponentMesh* c_mesh = (ComponentMesh*)gameobject->GetComponent(ComponentType::C_Mesh);
	c_mesh->mesh->textureID = FBXLoader::LoadTexture(buffer, size, &c_mesh->mesh->textureWidth, &c_mesh->mesh->textureHeight, _texname, false);
	textureID = c_mesh->mesh->textureID;

	textureLibraryPath = mPath;
	std::string aPath = "Assets/Textures/" + _texname + ".png";
	textureAssetsPath = aPath;
}

void ComponentMaterial::OnEditor(GameObject* _go)
{
	ImVec4 color = ImVec4(0.5f, 0.5f, 1, 1);
	ComponentMesh* c_mesh = (ComponentMesh *)_go->GetComponent(ComponentType::C_Mesh);
	if (ImGui::CollapsingHeader("Material")) {
		if (ImGui::Checkbox("Checker Material", &putCheckMaterial)) {
			ChangeTex();
		}
		ImTextureID id = (ImTextureID)textureID;
		ImGui::Image(id, ImVec2(100, 100));
		if (textureAssetsPath != "") {
			ImGui::TextColored(color, textureAssetsPath.c_str());
		}
		if (textureLibraryPath != "") {
			ImGui::TextColored(color, textureLibraryPath.c_str());
		}
		//c_mesh->mesh->textureHeight = ilGetInteger(IL_IMAGE_HEIGHT);
		//c_mesh->mesh->textureWidth = ilGetInteger(IL_IMAGE_WIDTH);
		ImGui::TextColored(color, "Height: ");
		ImGui::SameLine();
		ImGui::Text("%i", c_mesh->mesh->textureHeight);
		ImGui::TextColored(color, "Width: ");
		ImGui::SameLine();
		ImGui::Text("%i", c_mesh->mesh->textureWidth);

		//ilGetInteger()
	}
}

void ComponentMaterial::ChangeTex()
{
	ComponentMesh* c_mesh = (ComponentMesh*)ExternalApp->base_motor->inspector_window->_selectedGO->GetComponent(ComponentType::C_Mesh);
	if (ExternalApp->base_motor->inspector_window->_selectedGO != nullptr) {
		if (putCheckMaterial == true) {
			if (c_mesh != nullptr) {
				ChangeTexture((GLuint)ExternalApp->renderer3D->imgID, c_mesh);
			}
		}
		else {
			ChangeTexture(textureID, c_mesh);
		}
	}
}