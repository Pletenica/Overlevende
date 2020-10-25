#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ComponentMaterial.h"

///WINDOW NOW
ComponentMaterial::ComponentMaterial() :Component()
{

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