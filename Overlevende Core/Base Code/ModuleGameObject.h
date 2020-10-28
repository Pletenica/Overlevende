#ifndef __ModuleGameObject_H__
#define __ModuleGameObject_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "SDL/include/SDL.h"
#include <vector>
#include <string>

class Application;
class ComponentTransform;

enum ComponentType {
	C_Transform,
	C_Mesh,
	C_Material
};

class Component
{
public:

	Component();
	virtual ~Component();

	virtual bool Enable();
	virtual bool Update(float dt);
	virtual bool Disable();

public:
	bool active = true;
	ComponentType type;
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

public:
	bool active = true;
	std::string name;
	std::vector<Component*> components;
	ComponentTransform* transform;

	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
};

#endif // __ModuleGameObject_H__