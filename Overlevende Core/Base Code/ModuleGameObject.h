#ifndef __ModuleGameObject_H__
#define __ModuleGameObject_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "SDL/include/SDL.h"
#include <vector>
#include <string>
#include"JsonManager.h"

class Application;
class ComponentTransform;
class GameObject;

enum ComponentType {
	C_Transform,
	C_Mesh,
	C_Material,
	C_Camera,
	C_Particle
};

class Component
{
public:

	Component(GameObject* _go);
	virtual ~Component();

	virtual bool Enable();
	virtual bool Update(float dt);
	virtual bool Disable();
	virtual void OnEditor(GameObject* _go);

	virtual void SaveComponent(JsonManager* _man);
	virtual void LoadComponent(JsonManager* _man);

public:
	bool active = true;
	ComponentType type;
	GameObject* gameobject = nullptr;
};

class GameObject
{
public:

	GameObject();
	virtual ~GameObject();

	virtual bool Init();
	virtual update_status Update(float dt);
	virtual bool CleanUp();

	Component* CreateComponent(ComponentType w_type);
	Component* GetComponent(ComponentType w_type);
	void DeleteComponent(Component* comp);

	void SaveGameObject(JSON_Array* _goArray);
	void LoadGameObject(JsonManager* _man);

public:
	int idGO;
	bool active = true;
	std::string name;
	std::vector<Component*> components;
	ComponentTransform* transform;

	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
};

#endif // __ModuleGameObject_H__