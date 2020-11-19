#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "ModuleGameObject.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;
class GameObject;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Init();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	GameObject* CreateGameObject(std::string _name, GameObject* parent);
	void DeleteGameObject(GameObject* _go);
	void RecursiveUpdate(GameObject* node);
	void ClearHierarchy();

	void Save();
	void Load(const char* fileName);

public:
	/*Primitive primitive;*/
	GameObject* rootGO = nullptr;
private:
	bool showaxis = true;
	bool wireSphere = true;
};
