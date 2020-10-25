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

	virtual bool Enable();
	virtual bool Update(float dt);
	virtual bool Disable();

};

#endif // __ComponentMaterial_H__