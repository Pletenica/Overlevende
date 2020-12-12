#include "Application.h"
#include "Time.h"

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

extern Application* ExternalApp = nullptr;
Application::Application()
{
	list_modules.clear();

	file_system = new ModuleFileSystem(this);
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	base_motor = new ModuleBaseMotor(this);

	window_manager = new WindowManager(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(file_system);
	AddModule(window);

	AddModule(input);
	
	// Scenes
	AddModule(scene_intro);
	AddModule(camera);

	AddModule(window_manager);
	AddModule(renderer3D);

	AddModule(base_motor);
}

Application::~Application()
{
	for (int i = 0;i< list_modules.size(); i++) {
		delete list_modules[i];
	}

	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	for (int i = 0; i < list_modules.size(); ++i) {
		ret = list_modules[i]->Init();
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");

	ExternalApp = this;

	for (int i = 0; i < list_modules.size(); ++i) {
		ret = list_modules[i]->Start();
		if (ret == false) return false;
	}
	
	ms_timer.Start();

	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;

	Time::realTimeDeltaTime = dt;
	Time::realTimeSinceStartup += dt;

	Time::Update(dt);
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	for (int i = 0; i < list_modules.size(); i++) {
		ret = list_modules[i]->PreUpdate(dt);
		if (ret == UPDATE_STOP) return ret;
	}

	for (int i = 0; i < list_modules.size(); i++) {
		ret = list_modules[i]->Update(dt);
		if (ret == UPDATE_STOP) return ret;
	}

	for (int i = 0; i < list_modules.size(); i++) {
		ret = list_modules[i]->PostUpdate(dt);
		if (ret == UPDATE_STOP) return ret;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{

	ExternalApp = nullptr;
	bool ret = true;

	for (int i = 0; i > list_modules.size(); i++) {
		if (list_modules[i] != nullptr) {
			ret = list_modules[i]->CleanUp();
		}
	}

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

HardwareInfo Application::GetHardware()
{
	HardwareInfo specs;

	//CPU
	specs.GPUs = SDL_GetCPUCount();
	specs.CACHE = SDL_GetCPUCacheLineSize();

	//RAM
	specs.RAM = SDL_GetSystemRAM() / 1000;

	//Caps
	specs.RDTSC = SDL_HasRDTSC();
	specs.MMX = SDL_HasMMX();
	specs.SSE = SDL_HasSSE();
	specs.SSE2 = SDL_HasSSE2();
	specs.SSE3 = SDL_HasSSE3();
	specs.SSE41 = SDL_HasSSE41();
	specs.SSE42 = SDL_HasSSE42();
	specs.AVX = SDL_HasAVX();
	specs.AVX2 = SDL_HasAVX2();
	specs.AltiVec = SDL_HasAltiVec();

	if (specs.RDTSC) { specs.caps += "SDTSC"; }
	if (specs.MMX) { specs.caps += ", MMX"; }
	if (specs.SSE) { specs.caps += ", SSE"; }
	if (specs.SSE2) { specs.caps += ", SSE2"; }
	if (specs.SSE3) { specs.caps += ", SSE3"; }
	if (specs.SSE41) { specs.caps += ", SSE41"; }
	if (specs.SSE42) { specs.caps += ", SSE42"; }
	if (specs.AVX) { specs.caps += ", AVX2"; }
	if (specs.AltiVec) { specs.caps += ", AltiVec"; }

	//GPU
	//GLubyte* vendor = 
	specs.GPU = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	specs.GPU_brand = reinterpret_cast<const char*>(glGetString(GL_VENDOR));

	return specs;
}

const char* Application::GetEngineVersion()
{
	return version;
}