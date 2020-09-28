#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Timer.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateMiniumVelocity();
	void CheckMiniumVelocity();
	void ResetWhenLoose();

public:
	//Vehicle variables
	float* mattrans;
	Timer timer;
	float time = 0.0f;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	//Change Speed Variables
	float actual_minimum_vel = 0.0f;
	float future_minimum_vel = 0.0f;
	bool changevelocity = false;

	//Player conditions
	unsigned int loosesound;
	bool win = true;
	bool godmode = false;
};