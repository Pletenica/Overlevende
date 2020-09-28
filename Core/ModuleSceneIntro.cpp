#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
//#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));



	App->audio->PlayMusic("Music/Back.ogg", 1);
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	//This is to Make the Future minium velocity in the first frame,
	//because the future vel changes after the firsts 10 sec.
	if (donecolliders == false) {
		App->player->future_minimum_vel = rand() % 60 + 50;
	}

	CreateRectConstraint(1, 0, { 0,1,0 }, { 0,1.5,30 }, { 1,3,1 });

	CreateBoxesMap();

	donecolliders = true;
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

void ModuleSceneIntro::CreateBoxesMap()
{
	for (int g = 0; g < 31; g++) {

		if ((int)g % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { 10, 1.5,57 - g * 3.0f }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { -10, 1.5,57 - g * 3.0f }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { 10, 1.5,57 - g * 3.0f }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { -10, 1.5,57 - g * 3.0f }, { 1,3,1 }, White);
		}
	}

	CreateBox(45, { 0, 1, 0 }, { -9.5,1.5,63 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -9,1.5,66 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { -8.5,1.5,69 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -7,1.5,72 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { -4.5,1.5,74.5 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -2,1.5,76.25 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 1,1.5,77.5 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 4.5,1.5,78 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 7,1.5,78 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 10,1.5,78 }, { 1,3,1 }, Blue);

	CreateBox(45, { 0, 1, 0 }, { 12, 1.5,78 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 15, 1.5,78 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 18, 1.5,78 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 21, 1.5,78 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 24, 1.5,78 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 27, 1.5,78 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 30, 1.5,78 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 33, 1.5,78 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 36, 1.5,78 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 39, 1.5,78 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 12, 1.5,60 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 15, 1.5,60 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 18, 1.5,60 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 21, 1.5,60 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 24, 1.5,60 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 27, 1.5,60 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 30, 1.5,60 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 33, 1.5,60 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 36, 1.5,60 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 39, 1.5,60 }, { 1,3,1 }, Blue);

	//FIRST BRIDGE
	for (float i = 0; i < 19; i++) {
		CreateBox(0, { 0, 1, 0 }, { i * 3 + 42,(float)i / 2 + 0.2f,69 }, { 3,0.5,25 }, Brown);
		if ((int)i % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { i * 3 + 39, i / 2 + 1.5f, 60 }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { i * 3 + 39, i / 2 + 1.5f,78 }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { i * 3 + 39, i / 2 + 1.5f, 60 }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { i * 3 + 39, i / 2 + 1.5f,78 }, { 1,3,1 }, White);
		}

	}
	for (float i = 19; i > 0; i--) {
		CreateBox(0, { 0, 1, 0 }, { i * -3 + 172.2f,(float)i / 2.07f ,69 }, { 3,0.5,25 }, Brown);
		if ((int)i % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { i * -3 + 172.2f, i / 2.05f + 1.5f, 60 }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { i * -3 + 172.2f, i / 2.05f + 1.5f,78 }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { i * -3 + 172.2f, i / 2.05f + 1.5f, 60 }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { i * -3 + 172.2f, i / 2.05f + 1.5f,78 }, { 1,3,1 }, White);
		}
	}
	for (float k = 0; k < 6; k++) {
		if (k < 5) CreateBox(0, { 0, 1, 0 }, { k * 3.2f + 99.2f,9.2f,69 }, { 3,0.5,25 }, Brown);
		if ((int)k % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { k * 3.2f + 96.2f, 10.7f, 60 }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { k * 3.2f + 96.2f, 10.7f,78 }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { k * 3.2f + 96.2f, 10.7f, 60 }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { k * 3.2f + 96.2f, 10.7f,78 }, { 1,3,1 }, White);
		}
	}

	//CURVA
	CreateBox(45, { 0, 1, 0 }, { 173, 1.5,78 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 176, 1.5,78 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 179, 1.5,77 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 182, 1.5,75.5 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 184.5, 1.5,73 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 186.5, 1.5,70 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 188, 1.5,67 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 188.5, 1.5,64 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 189, 1.5,61 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 189.5, 1.5,58 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 170, 2,58 }, { 1,3,1 }, White);
	for (int g = 0; g < 30; g++) {

		if ((int)g % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { 190, 1.5,55.0f - g * 3.0f }, { 1,3,1 }, Blue);
			if (g < 25) {
				CreateBox(45, { 0, 1, 0 }, { 170, 1.5,55.0f - g * 3.0f }, { 1,3,1 }, Blue);
			}

		}
		else {
			CreateBox(45, { 0, 1, 0 }, { 190, 1.5,55.0f - g * 3.0f }, { 1,3,1 }, White);
			if (g < 25) {
				CreateBox(45, { 0, 1, 0 }, { 170, 1.5,55.0f - g * 3.0f }, { 1,3,1 }, White);
			}
		}
	}

	CreateBox(45, { 0, 1, 0 }, { 189, 1.5,-35 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 186.5, 1.5,-38 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 183, 1.5,-40 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 179, 1.5,-41 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 176, 1.5,-41 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 173, 1.5,-41 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 170, 1.5,-41 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 170, 1.5,-21 }, { 1,3,1 }, White);

	for (int g = 0; g < 19; g++) {

		if ((int)g % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { 170 - g * 3.0f, 1.5,-21 }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { 170 - g * 3.0f, 1.5,-41 }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { 170 - g * 3.0f, 1.5,-21 }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { 170 - g * 3.0f, 1.5,-41 }, { 1,3,1 }, White);
		}
	}



	for (int g = 0; g < 54; g++) {

		if ((int)g % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { 95, 1.5,140.0f - g * 3.0f }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { 115, 1.5,140.0f - g * 3.0f }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { 95, 1.5,140.0f - g * 3.0f }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { 115, 1.5,140.0f - g * 3.0f }, { 1,3,1 }, White);
		}
	}

	CreateBox(45, { 0, 1, 0 }, { 113.5, 1.5,-39.85 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 110, 1.5,-38.85 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 107, 1.5,-37 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 103, 1.5,-34 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 99, 1.5,-31 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 97, 1.5,-27 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 96, 1.5, -22.5 }, { 1,3,1 }, White);

	//CURVA
	CreateBox(45, { 0, 1, 0 }, { 95, 1.5,163 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 99, 1.5,163 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 102, 1.5,163 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 105, 1.5,162 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 108, 1.5,160.5 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 110.5, 1.5,158 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 112.5, 1.5,155 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 114, 1.5,152 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 114.5, 1.5,149 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 115.1, 1.5,146 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 115.5, 1.5,143 }, { 1,3,1 }, Blue);

	for (int g = 0; g < 15; g++) {

		if ((int)g % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { 95 - g * 3.0f, 1.5,143 }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { 95 - g * 3.0f, 1.5,163 }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { 95 - g * 3.0f, 1.5,143 }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { 95 - g * 3.0f, 1.5,163 }, { 1,3,1 }, White);
		}
	}

	//SECOND BRIDGE
	for (float i = 0; i < 19; i++) {
		CreateBox(0, { 0, 1, 0 }, { i * -3 + 50,(float)i / 2 + 0.2f,153 }, { 3,0.5,25 }, Brown);
		if ((int)i % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { i * -3 + 50, i / 2 + 1.5f, 143 }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { i * -3 + 50, i / 2 + 1.5f,163 }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { i * -3 + 50, i / 2 + 1.5f, 143 }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { i * -3 + 50, i / 2 + 1.5f,163 }, { 1,3,1 }, White);
		}
	}
	for (float k = 0; k < 25; k++) {
		CreateBox(0, { 0, 1, 0 }, { k * -3.2f - 7.2f,9.2f,153 }, { 3,0.5,25 }, Brown);
		if ((int)k % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { k * -3.2f - 7.2f, 10.7f, 163 }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { k * -3.2f - 7.2f, 10.7f,143 }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { k * -3.2f - 7.2f, 10.7f, 163 }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { k * -3.2f - 7.2f, 10.7f,143 }, { 1,3,1 }, White);
		}
	}
	for (float i = 0; i < 19; i++) {
		CreateBox(0, { 0, 1, 0 }, { i * 3 - 141.2f,(float)i / 2 + 0.2f,153 }, { 3,0.5,25 }, Brown);
		if ((int)i % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { i * 3 - 141.2f, i / 2 + 1.5f, 143 }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { i * 3 - 141.2f, i / 2 + 1.5f, 163 }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { i * 3 - 141.2f, i / 2 + 1.5f, 143 }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { i * 3 - 141.2f, i / 2 + 1.5f, 163 }, { 1,3,1 }, White);
		}
	}



	CreateBox(45, { 0, 1, 0 }, { -164.25,1.5,144.5 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -163,1.5,148 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { -161.5,1.5,151 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -159.5,1.5,154 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { -156.5,1.5,156.5 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -153,1.5,158.25 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { -148.5,1.5,161 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -144,1.5,162.4 }, { 1,3,1 }, Blue);


	for (int g = 0; g < 59; g++) {

		if ((int)g % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { -145, 1.5,141.2f - g * 3.0f }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { -165, 1.5,141.2f - g * 3.0f }, { 1,3,1 }, Blue);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { -145, 1.5,141.2f - g * 3.0f }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { -165, 1.5,141.2f - g * 3.0f }, { 1,3,1 }, White);
		}
	}

	CreateBox(45, { 0, 1, 0 }, { -164, 1.5,-37.5 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -163, 1.5,-43 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { -160, 1.5,-47.5 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -157, 1.5,-51 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { -152, 1.5,-53.5 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -148, 1.5, -54.5 }, { 1,3,1 }, Blue);

	for (int g = 0; g < 45; g++) {

		if ((int)g % 2 == 0) {
			CreateBox(45, { 0, 1, 0 }, { -145 + g * 3.0f, 1.5, -35 }, { 1,3,1 }, White);
			CreateBox(45, { 0, 1, 0 }, { -145 + g * 3.0f, 1.5, -55 }, { 1,3,1 }, White);
		}
		else {
			CreateBox(45, { 0, 1, 0 }, { -145 + g * 3.0f, 1.5, -35 }, { 1,3,1 }, Blue);
			CreateBox(45, { 0, 1, 0 }, { -145 + g * 3.0f, 1.5, -55 }, { 1,3,1 }, Blue);
		}
	}

	CreateBox(45, { 0, 1, 0 }, { 10, 1.5,-37.5 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { 7, 1.5,-43.25 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { 3, 1.5,-47.5 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -1.5, 1.5,-51 }, { 1,3,1 }, Blue);
	CreateBox(45, { 0, 1, 0 }, { -5.5, 1.5,-53.5 }, { 1,3,1 }, White);
	CreateBox(45, { 0, 1, 0 }, { -10, 1.5, -54.5 }, { 1,3,1 }, Blue);

	StartPodium();

}

void ModuleSceneIntro::StartPodium()
{
	//START PODIO
	CreateBox(0, { 0, 1, 0 }, { 14, 7.5,30 }, { 2.5,15,1.5 }, White);
	CreateBox(0, { 0, 1, 0 }, { -14, 7.5,30 }, { 2.5,15,1.5 }, White);
	CreateBox(0, { 0, 1, 0 }, { 0, 12.5,30 }, { 25.5,5,1.5 }, White);

	//S
	CreateBox(0, { 0, 1, 0 }, { 7, 14,29 }, { 4,0.75,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { 8.62, 13.25,29 }, { 0.75,0.75,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { 7, 11,29 }, { 4,0.75,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { 5.38, 11.75,29 }, { 0.75,0.75,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { 7, 12.5,29 }, { 4,0.75,0.5 }, Black);

	//T
	CreateBox(0, { 0, 1, 0 }, { 3, 12.12,29 }, { 0.75,3,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { 3, 14,29 }, { 3,0.75,0.5 }, Black);

	//A
	CreateBox(0, { 0, 1, 0 }, { 0.62, 12.12,29 }, { 0.75,3,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { -2.12, 12.12,29 }, { 0.75,3,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { -0.75, 14,29 }, { 3.5,0.75,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { -0.75, 12.5,29 }, { 2,0.75,0.5 }, Black);

	//R
	CreateBox(0, { 0, 1, 0 }, { -3.37, 12.12,29 }, { 0.75,3,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { -5.62, 13.25,29 }, { 0.75,0.75,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { -4.5, 14,29 }, { 3,0.75,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { -4.87, 12.5,29 }, { 2.25,0.75,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { -5, 11.5,29 }, { 0.75,1.75,0.5 }, Black);

	//T
	CreateBox(0, { 0, 1, 0 }, { -8, 12.12,29 }, { 0.75,3,0.5 }, Black);
	CreateBox(0, { 0, 1, 0 }, { -8, 14,29 }, { 3,0.75,0.5 }, Black);

}

void ModuleSceneIntro::CreateBox(int nangle,vec3 angle,vec3 offset, vec3 size, Color color) {

	Cube cube;
	cube.size = size;
	cube.SetPos(offset.x, offset.y, offset.z);
	cube.color = color;
	cube.SetRotation(nangle, angle);
	if (donecolliders == false) {
		App->physics->AddBody(cube, 0);
	}
	cube.Render();
}

void ModuleSceneIntro::CreateCylinder(float nangle, vec3 angle, float height, float radius, vec3 pos, Color color) {
	Cylinder c;
	c.height = height;
	c.radius = radius;
	c.SetPos(pos.x, pos.y, pos.z);
	c.color = color;
	c.SetRotation(nangle, angle);

	if (donecolliders == false) {
		App->physics->AddBody(c, 0);
	}
	c.Render();
}

void ModuleSceneIntro::CreateRectConstraint(int index, int nangle, vec3 angle, vec3 offset, vec3 size) {
	Cube cube;
	cube.size = size;
	cube.SetPos(offset.x, offset.y, offset.z);
	cube.color = White;
	cube.SetRotation(nangle, angle);

	Cube cube2;
	PhysBody3D *cubephys;
	
	listcubes.Insert(cube2, 0);
	cube2.size = {size.x*12,size.y*0.65f,size.z};
	cube2.SetPos(offset.x, offset.y, offset.z);
	cube2.color = Purple;
	cube2.SetRotation(nangle, angle);

	if (donecolliders == false) {
		cubephys = App->physics->AddBody(cube2, 1);
		cube.body = App->physics->AddBody(cube, 1000000);


		App->physics->AddConstraintHinge(*cubephys, *cube.body, { 0,0,0 }, { 0,0,0 }, {0 ,-4,0}, { 0,-2,0}, true);
		cube2.body = cubephys;
		primitive.body = cubephys;
	}

	primitive.body->GetTransform(&cube2.transform);

	cube.Render();
	cube2.Render();
}