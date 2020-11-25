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
#include "MathGeoLib/src/Algorithm/Random/LCG.h"

#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"

#include "JsonManager.h"

GameObject::GameObject(const char* _name, GameObject* _parent, int id)
{
	parent = _parent;
	name = _name;
	idGO = id;

	if (idGO == -1) {
		LCG randomizer;
		idGO = randomizer.Int();
		transform = (ComponentTransform*)CreateComponent(ComponentType::C_Transform);
	}

	if (parent != nullptr) {
		parent->children.push_back(this);
	}
	aabb.SetNegativeInfinity();
	UpdateAABB();
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
	if (ExternalApp->base_motor->options_window->GetDrawAABB() == true &&active==true) {
		RenderAABB(aabb);
	}

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

void GameObject::LoadGameObject(JSON_Array* _componentArray)
{
	for (int i = 0; i < json_array_get_count(_componentArray); i++) {
		JsonManager compMan(json_array_get_object(_componentArray, i));
		
		Component* comp = CreateComponent((ComponentType)compMan.GetInt("Type"));
		comp->LoadComponent(&compMan);
		if (comp->type == ComponentType::C_Transform)
			transform = dynamic_cast<ComponentTransform*>(comp);
	}
}

void GameObject::RenderAABB(AABB _aabb)
{
	float3 points[8];
	_aabb.GetCornerPoints(points);

	glColor3f(0, 1, 0);
	glLineWidth(1.5f);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);

	glVertex3fv(&points[0].x);
	glVertex3fv(&points[2].x);
	glVertex3fv(&points[2].x);
	glVertex3fv(&points[6].x);

	glVertex3fv(&points[6].x);
	glVertex3fv(&points[4].x);
	glVertex3fv(&points[4].x);
	glVertex3fv(&points[0].x);

	glVertex3fv(&points[0].x);
	glVertex3fv(&points[1].x);
	glVertex3fv(&points[1].x);
	glVertex3fv(&points[3].x);

	glVertex3fv(&points[3].x);
	glVertex3fv(&points[2].x);
	glVertex3fv(&points[4].x);
	glVertex3fv(&points[5].x);

	glVertex3fv(&points[6].x);
	glVertex3fv(&points[7].x);
	glVertex3fv(&points[5].x);
	glVertex3fv(&points[7].x);

	glVertex3fv(&points[3].x);
	glVertex3fv(&points[7].x);
	glVertex3fv(&points[1].x);
	glVertex3fv(&points[5].x);

	glVertex3fv(&points[1].x);
	glVertex3fv(&points[2].x);
	glVertex3fv(&points[2].x);
	glVertex3fv(&points[4].x);
	glVertex3fv(&points[4].x);
	glVertex3fv(&points[7].x);
	glVertex3fv(&points[7].x);
	glVertex3fv(&points[1].x);
	glVertex3fv(&points[2].x);
	glVertex3fv(&points[7].x);
	glVertex3fv(&points[4].x);
	glVertex3fv(&points[1].x);

	glEnd();
	glLineWidth(1);
	glColor3f(1, 1, 1);
	glEnable(GL_LIGHTING);
}

void GameObject::UpdateAABB()
{
	ComponentMesh* c_mesh = (ComponentMesh*)GetComponent(ComponentType::C_Mesh);
	ComponentCamera* c_cam = (ComponentCamera*)GetComponent(ComponentType::C_Camera);

	//Check if parent != nullptr to do not rootnode
	if (parent != nullptr) {
		if (c_mesh != nullptr) {
			obb = c_mesh->mesh->LocalAABB;
			obb.Transform(transform->global_transform);

			aabb.SetNegativeInfinity();
			aabb.Enclose(obb);
		}
		if (c_cam != nullptr) {
			float3 aabbpoints[8];

			aabbpoints[0] = { -0.5f,-0.5f,-0.5f };
			aabbpoints[1] = { -0.5f,-0.5f,0.5f };
			aabbpoints[2] = { -0.5f,0.5f,-0.5f };
			aabbpoints[3] = { -0.5f,0.5f,0.5f };
			aabbpoints[4] = { 0.5f,-0.5f,-0.5f };
			aabbpoints[5] = { 0.5f,-0.5f,0.5f };
			aabbpoints[6] = { 0.5f,0.5f,-0.5f };
			aabbpoints[7] = { 0.5f,0.5f,0.5f };

			aabb.SetNegativeInfinity();
			aabb.Enclose(aabbpoints, 8);
			obb = aabb;
			obb.Transform(transform->global_transform);
			aabb.SetNegativeInfinity();
			aabb.Enclose(obb);
		}
	}
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
