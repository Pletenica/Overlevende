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
	void ImportFBX(char* _buffer, int _size, int temporalTexID);
	int LoadTexture(char* _buffer, int _size);

	void aiMeshToMesh(const aiScene* scene, std::vector<Mesh*>& meshVector, std::vector<GLuint>& textureVector);

	void NodeToGameObject(const aiScene* scene, aiNode* node, GameObject* parent, std::vector<Mesh*>& meshVector);

};