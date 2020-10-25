#ifndef __ComponentTransform_H__
#define __ComponentTransform_H__

#include "glmath.h"
#include "ModuleGameObject.h"
#include "SDL/include/SDL.h"

class ComponentTransform : public Component
{
public:

	ComponentTransform();
	virtual ~ComponentTransform();

	bool Enable();
	bool Update(float dt);
	bool Disable();

};

#endif // __ComponentTransform_H__