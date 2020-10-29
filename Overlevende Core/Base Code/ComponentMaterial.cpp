#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"

///WINDOW NOW
ComponentMaterial::ComponentMaterial() :Component()
{
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