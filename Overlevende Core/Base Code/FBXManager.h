#pragma once
//#include "ModuleRenderer3D.h"

#include<vector>
#include<string>
#include<map>
class Mesh;
class aiMesh;
class aiScene;
class aiString;
class GameObject;
class aiNode;
typedef unsigned int GLuint;
typedef unsigned int uint;

namespace FBXLoader 
{
	void EnableDebug();
	void DisableDebug();
	void ImportFBX(char* _buffer, int _size, int temporalTexID, const char* _name);
	int LoadTexture(char* _buffer, int _size, int* _width, int* _height, std::string _texname, bool loadDDS = true);

	void aiMeshToMesh(const aiScene* scene, std::vector<Mesh*>& meshVector, std::vector<GLuint>& textureVector);

	void NodeToGameObject(const aiScene* scene, aiNode* node, GameObject* parent, std::vector<Mesh*>& meshVector, std::map<uint, std::string> textureMap);

	void SaveMeshToOwnFormat(Mesh *_mesh);
	Mesh* LoadMeshFromOwnFormat(std::string _meshname);

	void ImageToDDS(std::string _texturename);
};