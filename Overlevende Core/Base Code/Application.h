#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "p2List.h"
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "WindowManager.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleBaseMotor.h"
#include "ModuleFileSystem.h"

class Application
{
public:
	ModuleWindow* window;
	WindowManager* window_manager;
	ModuleInput* input;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleFileSystem* file_system;
	ModuleCamera3D* camera;
	ModuleBaseMotor* base_motor;

private:

	Timer	ms_timer;
	float	dt;
	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};

extern Application* ExternalApp;

#endif 