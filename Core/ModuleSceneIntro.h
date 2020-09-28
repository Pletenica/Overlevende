#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	//Create the Boxes
	void CreateBox(int nangle, vec3 angle,vec3 offset, vec3 size, Color color);
	void CreateCylinder(float, vec3 , float, float, vec3, Color);

	//Do the START boxes and Collisions
	void StartPodium();

	//Do all the Map Boxes and Collisions
	void CreateBoxesMap();

	//Create a Constraint
	void CreateRectConstraint(int index,int nangle, vec3 angle, vec3 offset, vec3 size);

public:
	Primitive primitive;

	mat4x4 mat;
	p2DynArray<Cube> listcubes;

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;

private:
	bool donecolliders = false;
};
