#ifndef __ModuleCamera3D_H__
#define __ModuleCamera3D_H__

#include "Module.h"
#include "Globals.h"

#include "ComponentCamera.h"
#include "MathGeoLib/src/Math/float3.h"

class vec3;
typedef struct json_array_t  JSON_Array;
class JsonManager;
#include "Color.h"

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
	void SaveCamera(JSON_Array* _goArray);
	void LoadCamera(JsonManager* _man);

public:
	ComponentCamera _cam;
	float3 Position, Reference;

	float move_speed;
	float drag_speed;
	float zoom_speed;
	float sensitivity;

	Color background;
};

#endif // __ModuleCamera3D_H__