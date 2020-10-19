#pragma once
//#include "ModuleRenderer3D.h"

#include<vector>
class Mesh;

namespace FBXLoader 
{
	void EnableDebug();
	void DisableDebug();
	void ImportFBX(const char* full_path, Mesh& _meshes, int temporalTexID);
};