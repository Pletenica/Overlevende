#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "Libraries/SDL\include\SDL_opengl.h"

ModuleScene::ModuleScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
ModuleScene::~ModuleScene()
{

}

// Called before render is available
bool ModuleScene::Init()
{
	
	return true;
}

// Called every draw update
update_status ModuleScene::PreUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleScene::CleanUp()
{
	LOG("Quitting SDL scene event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}