#pragma once
#include "Module.h"
#include "Globals.h"


class ModuleScene : public Module
{
public:

	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Init();
	update_status PreUpdate(float dt);
	bool CleanUp();

	
private:

	
	//int mouse_z_motion;
};
