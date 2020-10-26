#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "Mesh.h"
#include"SDL/include/SDL.h"

//Include ImGui
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"


#define MAX_LIGHTS 8

#define SQUARE_TEXTURE_W 128
#define SQUARE_TEXTURE_H 128

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);
	void GenerateSceneBuffers();

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

public:
	uint frameBuffer = 0;
	uint depthBuffer = 0;
	uint renderTexture = 0;

	//GLubyte checkerImage[SQUARE_TEXTURE_W][SQUARE_TEXTURE_H][4];
	uint imgID;
	std::vector<Mesh*> cleanUpMeshes;
	std::vector<GLuint> cleanUpTextures;

};