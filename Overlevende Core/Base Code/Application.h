#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "p2List.h"
#include "Globals.h"

class ModuleFileSystem;
class ModuleBaseMotor;
class ModuleCamera3D;
class ModuleRenderer3D;
class ModuleSceneIntro;
class ModuleInput;
class WindowManager;
class ModuleWindow;
class Module;

#include "Timer.h"
#include <string>
#include <vector>

struct HardwareInfo
{
	int GPUs;
	int CACHE;
	float RAM;
	const char* GPU;
	const char* GPU_brand;
	bool RDTSC = false;
	bool MMX = false;
	bool SSE = false;
	bool SSE2 = false;
	bool SSE3 = false;
	bool SSE41 = false;
	bool SSE42 = false;
	bool AVX = false;
	bool AVX2 = false;
	bool AltiVec = false;
	std::string caps;
};

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

	HardwareInfo GetHardware();
	const char* GetEngineVersion();
private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
	const char* version;
};

extern Application* ExternalApp;

#endif 