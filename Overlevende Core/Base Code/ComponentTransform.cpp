#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ComponentTransform.h"

///WINDOW NOW
ComponentTransform::ComponentTransform() :Component()
{

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

	return true;
}