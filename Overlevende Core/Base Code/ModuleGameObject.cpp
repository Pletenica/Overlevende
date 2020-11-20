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
#include "ModuleSceneIntro.h"
#include "MathGeoLib/Algorithm/Random/LCG.h"

#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"

GameObject::GameObject()
{
	transform = (ComponentTransform*)CreateComponent(ComponentType::C_Transform);
	//CreateComponent(ComponentType::C_Mesh);
	//CreateComponent(ComponentType::C_Material);
	LCG randomizer;
	idGO = randomizer.Int();
}

// Destructor
GameObject::~GameObject()
{
	CleanUp();
}

// Called before render is available
bool GameObject::Init()
{
	bool ret = true;

	for (int i = 0; i < components.size(); i++)
	{
		if (components[i] != nullptr)
			components[i]->Enable();
	}

	return ret;
}

update_status GameObject::Update(float dt)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i] != nullptr)
			components[i]->Update(dt);
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool GameObject::CleanUp()
{
	for (int i = 0; i < components.size(); i++)
	{
		//if (components[i] != nullptr) 
		//	components[i]->Disable();
		delete components[i];
		components[i] = nullptr;
	}
	components.clear();

	for (size_t i = 0; i < children.size(); i++)
	{
		delete children[i];
		children[i] = nullptr;
	}
	children.clear();

	return true;
}


Component* GameObject::CreateComponent(ComponentType w_type) {
	Component* comp = nullptr;

	switch (w_type) {
	case(ComponentType::C_Material):
		comp = new ComponentMaterial(this);
		break;
	case(ComponentType::C_Transform):
		comp = new ComponentTransform(this);
		break;
	case(ComponentType::C_Mesh):
		comp = new ComponentMesh(this);
		break;
	case(ComponentType::C_Camera):
		comp = new ComponentCamera(this);
		break;
	//case(ComponentType::C_Particle):
	//	comp = new ComponentParticleSystem(this);
	//	break;
	}

	components.push_back(comp);
	return comp;
}

Component* GameObject::GetComponent(ComponentType w_type)
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i]->type == w_type)
			return components[i];
	}

	return nullptr;
}

void GameObject::DeleteComponent(Component* comp) {
	for (int i = 0; i < components.size(); i++) {
		if (components[i] == comp) {
			(components.erase(components.begin() + i));
		}
	}
}

void GameObject::SaveGameObject(JSON_Array* _goArray)
{
	JSON_Value* _val = json_value_init_object();
	JsonManager _man(json_value_get_object(_val));

	_man.AddString("name", name.c_str());
	_man.AddInt("GameObject id", idGO);
	if (parent != nullptr) {
		_man.AddInt("Parent id", parent->idGO);
	}

	json_array_append_value(_goArray, _val);

	JSON_Value* comp = json_value_init_array();
	JSON_Array* _arraybro = json_value_get_array(comp);
	for (int i = 0; i < components.size(); i++)
	{
		JSON_Value* _valcomponent = json_value_init_object();
		JsonManager _manager(json_value_get_object(_valcomponent));

		components[i]->SaveComponent(&_manager);
		json_array_append_value(_arraybro,_valcomponent);
	}
	json_object_set_value(json_value_get_object(_val), "components", comp);
	
	for (int i = 0; i < children.size(); i++) {
		children[i]->SaveGameObject(_goArray);
	}
}

void GameObject::LoadGameObject(JsonManager* _man)
{
	name = _man->GetString("name");
	idGO = _man->GetInt("GameObject id");

}


///WINDOW NOW
Component::Component(GameObject* _go)
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

void Component::OnEditor(GameObject* _go)
{

}

void Component::SaveComponent(JsonManager* _man)
{
	_man->AddInt("Type", (int)type);
}

void Component::LoadComponent(JsonManager* _man)
{
}
