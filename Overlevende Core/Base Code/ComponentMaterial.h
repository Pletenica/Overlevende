#ifndef __ComponentMaterial_H__
#define __ComponentMaterial_H__

#include "glmath.h"
#include "ModuleGameObject.h"
#include "SDL/include/SDL.h"

class ComponentMaterial : public Component
{
public:

	ComponentMaterial();
	virtual ~ComponentMaterial();

	bool Enable();
	bool Update(float dt);
	bool Disable();

};

#endif // __ComponentMaterial_H__