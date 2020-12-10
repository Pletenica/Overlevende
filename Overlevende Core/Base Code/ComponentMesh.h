#ifndef __ComponentMesh_H__
#define __ComponentMesh_H__

#include "glmath.h"
#include "ModuleGameObject.h"
#include "SDL/include/SDL.h"

class Mesh;
class Component;
class GameObject;
class JsonManager;

class ComponentMesh : public Component
{
public:

	ComponentMesh(GameObject* _go);
	virtual ~ComponentMesh();

	bool Enable();
	bool Update(float dt);
	bool Disable();
	void OnEditor(GameObject* _go);
	bool isInsideFrustrum(Frustum *_frustrum);
	bool isInsideFrustrumOptimized(const Plane* planes);

	void SaveComponent(JsonManager* _man);
	void LoadComponent(JsonManager* _man);

private:
	void DrawVertexNormals(Mesh* _mesh);
	void DrawFaceNormals(Mesh* _mesh);

public:
	Mesh* mesh = nullptr;
	bool drawVertexNormals = false;
	bool drawFaceNormals = false;
};

#endif // __ComponentMesh_H__