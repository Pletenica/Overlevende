#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "ModuleGameObject.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;
class GameObject;
class ComponentCamera;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();

	GameObject* CreateGameObject(std::string _name, GameObject* parent, int id = -1);
	void DeleteGameObject(GameObject* _go);
	void RecursiveUpdate(GameObject* node);
	void ClearHierarchy();

	void Save(const char* _s);
	void Load(const char* fileName);

	void SaveModel(GameObject* _go, const char* _s);
	void LoadModel(const char* _s);

	Frustum* GetActualCameraToCull(GameObject* _go);

	std::vector<ComponentCamera*> allcameras;
	ComponentCamera* actualcullingcam = nullptr;

public:
	/*Primitive primitive;*/
	GameObject* rootGO = nullptr;
	GameObject* _toDeleteGO = nullptr;
private:
	bool showaxis = true;
	bool wireSphere = true;
};

bool CompareCameraPriorities(ComponentCamera* i1, ComponentCamera* i2);