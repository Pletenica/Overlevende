#ifndef __InspectorWindow_H__
#define __InspectorWindow_H__

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "WindowManager.h"
#include "SDL/include/SDL.h"

class GameObject;
class ComponentMaterial;
class ComponentMesh;
class ComponentTransform;
typedef unsigned int GLuint;

class InspectorWindow : public Window
{
public:

	InspectorWindow();

	// Destructor
	virtual ~InspectorWindow();

	bool Init();
	bool Draw(float dt);
	bool PreUpdate(float dt);
	bool CleanUp();
	void PutNewSelectedGameObject(GameObject* _go);
	void DeleteSelectedGameObject();

public:
	GameObject* _selectedGO = nullptr;
	GLuint mainMeshTextureID;

private:
	void CreateInitTab();
	char name[50];
};

#endif // __InspectorWindow_H__