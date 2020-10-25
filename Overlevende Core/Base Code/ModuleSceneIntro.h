#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
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
	void DoCube(int size);
	GameObject* CreateGameObject(std::string _name);

public:
	Primitive primitive;
	std::vector<GameObject*> game_objects;
	GameObject* prova_gameobject;
private:
	bool showaxis = true;
	bool wireSphere = true;
};
