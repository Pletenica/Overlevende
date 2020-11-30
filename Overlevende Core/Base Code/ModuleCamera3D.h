#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

#include "ComponentCamera.h"
#include "MathGeoLib/src/Math/float3.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookView2(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const float3 &Spot);
	void Move(const float3& Movement);
	void SetBackgroundColor(float r, float g, float b, float w);

public:
	ComponentCamera _cam;
	float3 Position, Reference;

	float move_speed;
	float drag_speed;
	float zoom_speed;
	float sensitivity;

	Color background;
};