#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include"Primitive.h"
#include <gl/GL.h>

#include"JsonManager.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{
	delete rootGO;
}

bool ModuleSceneIntro::Init() {

	return true;
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	showaxis = true;
	rootGO = CreateGameObject("Scene", nullptr);

	GameObject* camera = CreateGameObject("Camera", rootGO);
	camera->CreateComponent(ComponentType::C_Camera);

	App->file_system->LoadFileFromPath("Assets/FBXs/BakerHouse.fbx");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	PrimitivePlane p(0, 1, 0, 0);
	p.axis = true;

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
		App->file_system->LoadFileFromPath("Assets/FBXs/BakerHouse.fbx");
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		Save();

	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		Load("Scene.json");

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		if (showaxis == true) {
			showaxis = false;
		}
		else {
			showaxis = true;
		}
	}

	if (showaxis == true) {
		p.Render();
	}

	return UPDATE_CONTINUE;
}

GameObject* ModuleSceneIntro::CreateGameObject(std::string _name, GameObject* parent) {
	GameObject* go = nullptr;

	go = new GameObject();
	go->name = _name;
	go->parent = parent;

	if(parent != nullptr)
		parent->children.push_back(go);

	return go;
}

void ModuleSceneIntro::DeleteGameObject(GameObject* _go) 
{
	if (App->base_motor->inspector_window->_selectedGO == _go) {
		App->base_motor->inspector_window->_selectedGO = nullptr;
	}
	if(_go!=nullptr)
		delete _go;
}

void ModuleSceneIntro::RecursiveUpdate(GameObject* node)
{
	node->Update(0.f);

	if (node->active == true) {
		for (size_t i = 0; i < node->children.size(); i++)
		{
			RecursiveUpdate(node->children[i]);
		}
	}
}

void ModuleSceneIntro::ClearHierarchy()
{
	for (int i = 0; i < rootGO->children.size(); i++) {
		delete rootGO->children[i];
		rootGO->children[i] = nullptr;
	}
	rootGO->children.clear();
}

void ModuleSceneIntro::Save()
{
	JSON_Value* sceneFile = json_value_init_object();
	JSON_Object* parentObject = json_value_get_object(sceneFile);

	JsonManager manager(parentObject);
	manager.AddString("Test", "This is a test");

	JSON_Value* gArray = json_value_init_array();
	rootGO->SaveGameObject(json_value_get_array(gArray));
	json_object_set_value(parentObject, "GameObjects", gArray);

	json_serialize_to_file_pretty(sceneFile, "Scene.json");

	json_value_free(sceneFile);
}

void ModuleSceneIntro::Load(const char* fileName)
{
	JSON_Value* sceneFile = json_parse_file(fileName);

	if (sceneFile != nullptr) 
	{
		delete rootGO;
		rootGO = nullptr;
		App->base_motor->inspector_window->_selectedGO = nullptr;


		JSON_Object* parentObject = json_value_get_object(sceneFile);

		JSON_Array* _goarray = json_object_get_array(parentObject, "GameObjects");

		JsonManager jsonroot(json_array_get_object(_goarray, 0));
		rootGO = CreateGameObject(jsonroot.GetString("name"), nullptr);

		for (int i = 0; i < json_array_get_count(_goarray); i++)
		{
			JsonManager _man(json_array_get_object(_goarray, i));
			CreateGameObject(_man.GetString("name"), rootGO);
		}

		json_value_free(sceneFile);
	}


}
