#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
//#include "PhysBody3D.h"
#include <gl/GL.h>
//#include <Glew/include/glew.h>

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

bool ModuleSceneIntro::Init() {

	//uint my_id = 0;
	//glGenBuffers(1, (GLuint*)&(my_id));
	//glBindBuffer(GL_ARRAY_BUFFER, my_id);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * 3, vertices, GL_STATIC_DRAW);
	return true;
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	showaxis = true;

	_sphere.radius = 2.5f;
	_sphere.SetPos(0,2.5f,0);
	_sphere.SetRotation(90, vec3(1, 0, 0));
	_sphere.wire = false;

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

	//DoCube(1);

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		if (showaxis == true) {
			showaxis = false;
		}
		else {
			showaxis = true;
		}
	}

	if (showaxis == true) {
		p.Render();
	}

	//_sphere.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::DoCube(int size) {
	glLineWidth(2.0f);

	glBegin(GL_POLYGON);
	//PRIMERA CARA
	glVertex3f(1.f*size, 0.f*size, 0.f*size);
	glVertex3f(1.f*size, 1.f*size, 0.f*size);
	glVertex3f(1.f*size, 0.f*size, 1.f*size);
	glVertex3f(1.f*size, 1.f*size, 0.f*size);
	glVertex3f(1.f*size, 1.f*size, 1.f*size);
	glVertex3f(1.f*size, 0.f*size, 1.f*size);

	//SEGONA CARA
	glVertex3f(1.f*size, 1.f*size, 0.f*size);
	glVertex3f(0.f*size, 1.f*size, 0.f*size);
	glVertex3f(1.f*size, 1.f*size, 1.f*size);
	glVertex3f(0.f*size, 1.f*size, 0.f*size);
	glVertex3f(0.f*size, 1.f*size, 1.f*size);
	glVertex3f(1.f*size, 1.f*size, 1.f*size);

	//TERCERA CARA
	glVertex3f(0.f*size, 1.f*size, 0.f*size);
	glVertex3f(0.f*size, 0.f*size, 0.f*size);
	glVertex3f(0.f*size, 1.f*size, 1.f*size);
	glVertex3f(0.f*size, 0.f*size, 0.f*size);
	glVertex3f(0.f*size, 1.f*size, 0.f*size);
	glVertex3f(0.f*size, 1.f*size, 1.f*size);

	//QUARTA CARA
	glVertex3f(0.f*size, 0.f*size, 0.f*size);
	glVertex3f(1.f*size, 0.f*size, 0.f*size);
	glVertex3f(0.f*size, 0.f*size, 1.f*size);
	glVertex3f(1.f*size, 0.f*size, 0.f*size);
	glVertex3f(1.f*size, 0.f*size, 1.f*size);
	glVertex3f(0.f*size, 0.f*size, 1.f*size);

	//QUINTA CARA
	glVertex3f(1.f*size, 0.f*size, 1.f*size);
	glVertex3f(1.f*size, 1.f*size, 1.f*size);
	glVertex3f(0.f*size, 0.f*size, 1.f*size);
	glVertex3f(1.f*size, 1.f*size, 1.f*size);
	glVertex3f(0.f*size, 1.f*size, 1.f*size);
	glVertex3f(0.f*size, 0.f*size, 1.f*size);

	//SEXTA CARA
	glVertex3f(1.f*size, 1.f*size, 0.f*size);
	glVertex3f(1.f*size, 0.f*size, 0.f*size);
	glVertex3f(0.f*size, 1.f*size, 0.f*size);
	glVertex3f(1.f*size, 0.f*size, 0.f*size);
	glVertex3f(0.f*size, 1.f*size, 0.f*size);
	glVertex3f(0.f*size, 0.f*size, 0.f*size);

	glEnd();

	glLineWidth(1.0f);
}