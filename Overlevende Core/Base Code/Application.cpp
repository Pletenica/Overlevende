#include "Application.h"

extern Application* ExternalApp = nullptr;
Application::Application()
{
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

	AddModule(base_motor);
	AddModule(window_manager);

	// Renderer last!
	AddModule(renderer3D);

}

Application::~Application()
{
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL)
	{
		delete item->data;
		item = item->prev;
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}
	
	ms_timer.Start();


	ExternalApp = this;
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
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
	
	p2List_item<Module*>* item = list_modules.getFirst();
	
	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->PreUpdate(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->Update(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		ret = item->data->PostUpdate(dt);
		item = item->next;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{

	ExternalApp = nullptr;
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
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