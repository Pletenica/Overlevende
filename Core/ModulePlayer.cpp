#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"



ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(4, 0.5,5);
	car.chassis_offset.Set(0, 1, 0);
	car.backdecoration_size.Set(4, 0.2, 0.5);
	car.backdecoration_offset.Set(0, 2.75, -2.25);
	car.frontdecoration_size.Set(4, 0.2, 0.5);
	car.frontdecoration_offset.Set(0, 2.12, 2.25);
	car.frontwall_size.Set(4, 0.8, 1.25);
	car.frontwall_offset.Set(0, 1.66, 1.87);
	car.backwall_size.Set(4, 1.4, 2);
	car.backwall_offset.Set(0, 1.97, -1.5);

	car.stick1_size.Set(0.25, 4, 0.25);
	car.stick1_offset.Set(1.87, 3.5, -1.87);
	car.stick2_size.Set(0.25, 4, 0.25);
	car.stick2_offset.Set(-1.87, 3.5, -1.87);
	car.stick3_size.Set(0.25, 4, 0.25);
	car.stick3_offset.Set(1.87, 3.5, 1.87);
	car.stick4_size.Set(0.25, 4, 0.25);
	car.stick4_offset.Set(-1.87, 3.5, 1.87);
	car.techo_size.Set(4.1, 0.2, 5);
	car.techo_offset.Set(0, 5.5, 0);

	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 0, 10);
	
	loosesound=App->audio->LoadFx("Music/Loose.wav");
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		win = true;
		ResetWhenLoose();
	}

	if (App->input->GetKey(SDL_SCANCODE_F4) == KEY_DOWN)
	{
		if (godmode == false)godmode = true;
		else godmode = false;
	}

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() < -5) {
			brake = -BRAKE_POWER;
		}
		else {
			acceleration = MAX_ACCELERATION;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (vehicle->GetKmh() > 5) {
			brake = BRAKE_POWER;
		}
		else {
			acceleration = -MAX_ACCELERATION;
		}
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	time = (float)timer.Read()/1000;

	CreateMiniumVelocity();
	CheckMiniumVelocity();

	char title[200];
	sprintf_s(title, "Time: %.1f s || AVelocity: %.1f Km/h || Actual Minimun Velocity: %.1f Km/h || Future Minimun Velocity: %.1f Km/h || GodMode: %s", time, vehicle->GetKmh(), actual_minimum_vel, future_minimum_vel,godmode ? "ON" : "OFF");
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModulePlayer::CreateMiniumVelocity()
{
	if ((changevelocity == true) && (time >= 1) && (((uint)time % 10) == 0)) {

		actual_minimum_vel = future_minimum_vel;
		future_minimum_vel = rand() % 60 + 50;
		changevelocity = false;
	}
	if ((time >= 1) && (((uint)time % 10 - 1) == 0)) {

		changevelocity = true;
	}
}

void ModulePlayer::CheckMiniumVelocity()
{
	if (vehicle->GetKmh() < actual_minimum_vel) {
		if ((time >= 10)&&(godmode==false)){
			win = false;
			ResetWhenLoose();
		}
	}

}

void ModulePlayer::ResetWhenLoose()
{
	actual_minimum_vel = 0;
	App->audio->PlayFx(loosesound, 1);
	vehicle->ResetVelocityAndRotation();
	App->player->acceleration = 0;
	App->player->brake = 0;
	App->player->turn = 0;
	vehicle->SetPos(0, 0, 10);
}