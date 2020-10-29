#ifndef __ComponentMaterial_H__
#define __ComponentMaterial_H__

#include "glmath.h"
#include "ModuleGameObject.h"
#include "SDL/include/SDL.h"

#include <string>

class ComponentMesh;

class ComponentMaterial : public Component
{
public:

	ComponentMaterial();
	virtual ~ComponentMaterial();

	bool Enable();
	bool Update(float dt);
	bool Disable();
	void OnEditor();
	void ChangeTex();
	void ChangeTexture(GLuint _id, ComponentMesh* _mesh);

public:
	GLuint textureID;
	std::string texturePath;
	bool putCheckMaterial = false;
};

#endif // __ComponentMaterial_H__