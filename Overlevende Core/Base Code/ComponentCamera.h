#ifndef __ComponentCamera_H__
#define __ComponentCamera_H__

#include "glmath.h"
#include "ModuleGameObject.h"
#include "SDL/include/SDL.h"
#include "MathGeoLib/Geometry/Frustum.h"
#include <string>

class JSONManager;

class ComponentCamera : public Component
{
public:

	ComponentCamera(GameObject* _go);
	virtual ~ComponentCamera();

	bool Enable();
	bool Update(float dt);
	bool Disable();
	void OnEditor(GameObject* _go);

	void SaveComponent(JsonManager* _man);
	void LoadComponent(JsonManager* _man);

public:
	Frustum frustum;
	bool isCulling = false;
	bool isMainCamera = false;
	Plane planes[6];

	float nearPlaneDistance = 1;
	float farPlaneDistance = 100;
	float horizontalFOV = 1;
	float verticalFOV = 1;
};

#endif // __ComponentCamera_H__