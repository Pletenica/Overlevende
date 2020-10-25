#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ComponentMesh.h"

///WINDOW NOW
ComponentMesh::ComponentMesh() :Component()
{
	type = ComponentType::C_Mesh;
}

// Destructor
ComponentMesh::~ComponentMesh()
{
}

// Called before render is available
bool ComponentMesh::Enable()
{

	return true;
}

// Called before quitting
bool ComponentMesh::Disable()
{

	return true;
}

// Called before quitting
bool ComponentMesh::Update(float dt)
{

	return true;
}