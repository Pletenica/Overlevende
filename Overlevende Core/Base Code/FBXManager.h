#pragma once
//#include "ModuleRenderer3D.h"

#include<vector>
class Mesh;
class aiMesh;
class aiScene;
class GameObject;
class aiNode;
typedef unsigned int GLuint;

namespace FBXLoader 
{
	void EnableDebug();
	void DisableDebug();
	void ImportFBX(const char* full_path, int temporalTexID);
	int LoadTexture(const char* path);

	void aiMeshToMesh(const aiScene* scene, std::vector<Mesh*>& meshVector, std::vector<GLuint>& textureVector);

	void NodeToGameObject(const aiScene* scene, aiNode* node, GameObject* parent, std::vector<Mesh*>& meshVector);

};