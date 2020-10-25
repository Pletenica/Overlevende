#include "Globals.h"
#include "Application.h"
#include "InspectorWindow.h"
#include "AboutWindow.h"
#include "ResourcesWindow.h"
#include "ConfigurationWindow.h"
#include "ConsoleWindow.h"
#include "OptionsWindow.h"
#include "SceneWindow.h"
#include "ModuleGameObject.h"

#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"


GameObject::GameObject()
{
}

// Destructor
GameObject::~GameObject()
{
}

// Called before render is available
bool GameObject::Init()
{
	bool ret = true;

	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Enable();
	}

	return ret;
}

update_status GameObject::Update(float dt)
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Update(dt);
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool GameObject::CleanUp()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->Disable();
		delete components[i];
	}

	return true;
}


Component* GameObject::CreateComponent(ComponentType w_type) {
	Component* comp = nullptr;

	switch (w_type) {
	case(ComponentType::C_Material):
		comp = new ComponentMaterial();
		break;
	case(ComponentType::C_Transform):
		comp = new ComponentTransform();
		break;
	case(ComponentType::C_Mesh):
		comp = new ComponentMesh();
		break;
	}

	components.push_back(comp);
	return comp;
}

///WINDOW NOW
Component::Component()
{

}

// Destructor
Component::~Component()
{
}

// Called before render is available
bool Component::Enable()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool Component::Disable()
{

	return true;
}

// Called before quitting
bool Component::Update(float dt)
{

	return true;
}