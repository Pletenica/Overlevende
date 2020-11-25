#ifndef __ComponentCamera_H__
#define __ComponentCamera_H__

#include "glmath.h"
#include "ModuleGameObject.h"
#include "SDL/include/SDL.h"
#include "MathGeoLib/src/Geometry/Frustum.h"
#include <string>

class JSONManager;

class ComponentCamera : public Component
{
public:

	ComponentCamera(GameObject* _go);
	ComponentCamera(float3 pos);
	virtual ~ComponentCamera();

	bool Enable();
	bool Update(float dt);
	bool Disable();
	void OnEditor(GameObject* _go);

	void SaveComponent(JsonManager* _man);
	void LoadComponent(JsonManager* _man);

	void UpdateCamera(const float4x4 &global);
	void SetAspectRatio(float wi, float he);

public:
	Frustum frustum;
	bool isCulling = false;
	bool isMainCamera = false;

	float degFov = 0;
};

#endif // __ComponentCamera_H__