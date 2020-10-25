#ifndef __ComponentMesh_H__
#define __ComponentMesh_H__

#include "glmath.h"
#include "ModuleGameObject.h"
#include "SDL/include/SDL.h"

class ComponentMesh : public Component
{
public:

	ComponentMesh();
	virtual ~ComponentMesh();

	virtual bool Enable();
	virtual bool Update(float dt);
	virtual bool Disable();

};

#endif // __ComponentMesh_H__