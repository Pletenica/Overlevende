#ifndef __ModuleGameObject_H__
#define __ModuleGameObject_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "SDL/include/SDL.h"
#include <vector>
#include <string>

class Application;

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
	ComponentType type;
	bool active = true;
};

class GameObject
{
public:

	GameObject();
	virtual ~GameObject();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();

	Component* CreateComponent(ComponentType w_type);

public:
	bool active = true;
	std::string name;
	std::vector<Component*> components;
};

#endif // __ModuleGameObject_H__