#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include"Primitive.h"
#include <gl/GL.h>

#include <algorithm>
#include"JsonManager.h"
#include"ComponentTransform.h"
#include "MathGeoLib/src/MathGeoLib.h"


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

	App->camera->Move(float3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(float3(0, 0, 0));

	showaxis = true;
	rootGO = CreateGameObject("Scene", nullptr);

	Load("Library/Scenes/Scene.json");

	//GameObject* camera = CreateGameObject("Camera 2", rootGO);
	//camera->CreateComponent(ComponentType::C_Camera);
	//App->file_system->LoadFileFromPath("Assets/FBXs/scene.DAE");
	//App->file_system->LoadFileFromPath("Assets/FBXs/BakerHouse.fbx");
	return ret;
}

update_status ModuleSceneIntro::PreUpdate(float dt)
{
	if (_toDeleteGO != nullptr) 
	{
		for (std::vector<GameObject*>::iterator i = _toDeleteGO->parent->children.begin(); i != _toDeleteGO->parent->children.end(); ++i) 
		{
			if (*i._Ptr == _toDeleteGO) 
			{
				_toDeleteGO->parent->children.erase(i);
				break;
			}
		}
		delete _toDeleteGO;
		_toDeleteGO = nullptr;
	}
	return UPDATE_CONTINUE;
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

	//if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	//	Save("Library/Scenes/Scene.json");
	//
	//if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	//	Load("Library/Scenes/Scene.json");

	//if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	//	LoadModel("Library/Models/Ghost.etesech");

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

GameObject* ModuleSceneIntro::CreateGameObject(std::string _name, GameObject* parent, int id) {
	GameObject* go = nullptr;

	go = new GameObject(_name.c_str(), parent, id);

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

	if (node != nullptr && node->active == true) {
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

void ModuleSceneIntro::Save(const char* _s)
{
	JSON_Value* sceneFile = json_value_init_object();
	JSON_Object* parentObject = json_value_get_object(sceneFile);

	JsonManager manager(parentObject);

	JSON_Value* camArray = json_value_init_array();
	App->camera->SaveCamera(json_value_get_array(camArray));
	json_object_set_value(parentObject, "Editor Camera Settings", camArray);

	JSON_Value* gArray = json_value_init_array();
	rootGO->SaveGameObject(json_value_get_array(gArray));
	json_object_set_value(parentObject, "GameObjects", gArray);

	

	json_serialize_to_file_pretty(sceneFile, _s);

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

		//Load Editor Camera Settings
		JSON_Array* _camarray = json_object_get_array(parentObject, "Editor Camera Settings");
		JsonManager jsoncamroot(json_array_get_object(_camarray, 0));
		App->camera->LoadCamera(&jsoncamroot);

		//Load GameObjects
		JSON_Array* _goarray = json_object_get_array(parentObject, "GameObjects");

		JsonManager jsonroot(json_array_get_object(_goarray, 0));
		rootGO = CreateGameObject(jsonroot.GetString("name"), nullptr, jsonroot.GetInt("GameObject id"));

		GameObject* parent = rootGO;
		for (int i = 1; i < json_array_get_count(_goarray); i++)
		{
			JsonManager jsonman(json_array_get_object(_goarray, i));

			while (parent != nullptr && jsonman.GetInt("Parent id") != parent->idGO) {
				parent = parent->parent;
			}
			if (parent == nullptr) {
				parent = rootGO;
			}
			parent = CreateGameObject(jsonman.GetString("name"),parent, jsonman.GetInt("GameObject id"));

			parent->LoadGameObject(jsonman.GetArray("components"));
			parent->UpdateAABB();
		}

		json_value_free(sceneFile);
	}
	GetActualCameraToCull(rootGO);
}

void ModuleSceneIntro::SaveModel(GameObject* _go, const char* _s)
{
	JSON_Value* sceneFile = json_value_init_object();
	JSON_Object* parentObject = json_value_get_object(sceneFile);

	JsonManager manager(parentObject);

	JSON_Value* gArray = json_value_init_array();
	_go->SaveGameObject(json_value_get_array(gArray));
	json_object_set_value(parentObject, "Model", gArray);

	json_serialize_to_file_pretty(sceneFile, _s);

	json_value_free(sceneFile);
}

void ModuleSceneIntro::LoadModel(const char* fileName)
{
	JSON_Value* sceneFile = json_parse_file(fileName);

	if (sceneFile != nullptr)
	{
		App->base_motor->inspector_window->_selectedGO = nullptr;

		JSON_Object* parentObject = json_value_get_object(sceneFile);

		JSON_Array* _goarray = json_object_get_array(parentObject, "Model");

		JsonManager jsonroot(json_array_get_object(_goarray, 0));

		GameObject* parent = CreateGameObject(jsonroot.GetString("name"), rootGO, jsonroot.GetInt("GameObject id"));

		for (int i = 1; i < json_array_get_count(_goarray); i++)
		{
			JsonManager jsonman(json_array_get_object(_goarray, i));

			while (parent != nullptr && jsonman.GetInt("Parent id") != parent->idGO) {
				parent = parent->parent;
			}
			if (parent == nullptr) {
				parent = rootGO;
			}
			parent = CreateGameObject(jsonman.GetString("name"), parent, jsonman.GetInt("GameObject id"));

			parent->LoadGameObject(jsonman.GetArray("components"));
			parent->UpdateAABB();
		}

		json_value_free(sceneFile);
	}
}

Frustum* ModuleSceneIntro::GetActualCameraToCull(GameObject* _go)
{
	if (_go->parent == nullptr) {
		allcameras.clear();
		actualcullingcam = nullptr;
	}

	//Frustum *_frustum = nullptr;

	ComponentCamera* c_cam = (ComponentCamera*)_go->GetComponent(ComponentType::C_Camera);

	if (c_cam != nullptr) {
		ComponentCamera* _ccam = c_cam;
		allcameras.push_back(_ccam);

		std::sort(allcameras.begin(), allcameras.end(), CompareCameraPriorities);
		actualcullingcam = allcameras[0];
		//if (_ccam->isCulling == true) {
		//	return &_ccam->frustum;
		//}
	}

	for (size_t i = 0; i < _go->children.size(); i++) {
		GetActualCameraToCull(_go->children[i]);
		//_frustum= GetActualCameraToCull(_go->children[i]);
		//if (_frustum != nullptr)break;
	}

	return &actualcullingcam->frustum;
}

bool CompareCameraPriorities(ComponentCamera* i1, ComponentCamera* i2)
{
	return (i1->priority > i2->priority);
}