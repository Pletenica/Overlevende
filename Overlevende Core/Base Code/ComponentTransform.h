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

public:
	float position_x;
	float position_y;
	float position_z;

	float rotation_x;
	float rotation_y;
	float rotation_z;

	float scale_x;
	float scale_y;
	float scale_z;
};

#endif // __ComponentTransform_H__