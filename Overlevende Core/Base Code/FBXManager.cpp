#include "FBXManager.h"
#include "Globals.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include"Application.h"

#include"ModuleRenderer3D.h"
#include"ModuleGameObject.h"

#include"ComponentMesh.h"

#include"Devil/include/ilu.h"
#include"Devil/include/ilut.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

void myFunction(const char* message, char* user)
{
	LOG(message);
}

void FBXLoader::EnableDebug()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	stream.callback = myFunction;
	aiAttachLogStream(&stream);
}

void FBXLoader::DisableDebug()
{
	aiDetachAllLogStreams();
}

void FBXLoader::ImportFBX(const char* full_path, int _idTexturesTemporal)
{
	const aiScene* scene = aiImportFile(full_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiMesh* new_mesh = nullptr;

		std::vector<Mesh*> meshVector;
		aiMeshToMesh(scene, meshVector);

		ExternalApp->renderer3D->cleanUpMeshes = meshVector;

		NodeToGameObject(scene, scene->mRootNode, ExternalApp->scene_intro->rootGO, meshVector);
		
		if (scene->HasMaterials())
		{
			aiMaterial* material = scene->mMaterials[0];

			aiString texName;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &texName);

			std::string texturePath(full_path);
			texturePath = texturePath.substr(0, texturePath.find_last_of("/\\") + 1);
			texturePath += texName.C_Str();

			LoadTexture(texturePath.c_str());

			texturePath.clear();
		}

		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene % s", full_path);
}

int FBXLoader::LoadTexture(const char* path)
{

	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	
	if (!ilLoadImage(path)) 
	{
		LOG("Error loading texture");
	}
	GLuint glID = ilutGLBindTexImage();
	
	//ExternalApp->renderer3D->evangelion.textureID = glID;

	glBindTexture(GL_TEXTURE_2D, glID);
	ilDeleteImages(1, &imageID);

	return 0;
}

void FBXLoader::aiMeshToMesh(const aiScene* scene, std::vector<Mesh*>& meshVector)
{
	aiMesh* new_mesh;
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		Mesh* _mesh = new Mesh();
		new_mesh = scene->mMeshes[i];
		LOG("%s", scene->mMeshes[i]->mName.C_Str());

		// copy vertices
		_mesh->num_vertices = new_mesh->mNumVertices;
		_mesh->vertices = new float[_mesh->num_vertices * 3];
		memcpy(_mesh->vertices, new_mesh->mVertices, sizeof(float) * _mesh->num_vertices * 3);
		LOG("New mesh with %d vertices", _mesh->num_vertices);

		if (new_mesh->HasNormals())
		{
			_mesh->num_normals = new_mesh->mNumVertices;
			_mesh->normals = new float[_mesh->num_normals * 3];
			memcpy(_mesh->normals, new_mesh->mNormals, sizeof(float) * _mesh->num_normals * 3);
			LOG("New mesh with %d normals", _mesh->num_normals);
		}

		if (new_mesh->HasTextureCoords(0))
		{
			_mesh->num_textures = new_mesh->mNumVertices;
			_mesh->textures = new float[new_mesh->mNumVertices * 2];

			for (unsigned int i = 0; i < _mesh->num_textures; i++)
			{
				_mesh->textures[i * 2] = new_mesh->mTextureCoords[0][i].x;
				_mesh->textures[i * 2 + 1] = new_mesh->mTextureCoords[0][i].y;
			}

			LOG("New mesh with %d texture coords", _mesh->num_textures);
		}

		// copy faces
		if (new_mesh->HasFaces())
		{
			_mesh->num_indices = new_mesh->mNumFaces * 3;
			_mesh->indices = new uint[_mesh->num_indices]; // assume each face is a triangle
			for (uint j = 0; j < new_mesh->mNumFaces; ++j)
			{
				if (new_mesh->mFaces[j].mNumIndices != 3)
				{
					LOG("WARNING, geometry face with != 3 indices!");
				}
				else
				{
					memcpy(&_mesh->indices[j * 3], new_mesh->mFaces[j].mIndices, 3 * sizeof(uint));
				}
			}
		}

		_mesh->GenBuffers(MeshType::FBXNone);
		meshVector.push_back(_mesh);
	}

}

void FBXLoader::NodeToGameObject(const aiScene* scene, aiNode* node, GameObject* parent, std::vector<Mesh*>& meshVector)
{
	GameObject* go = new GameObject();
	go->name = node->mName.C_Str();
	go->parent = parent;
	parent->children.push_back(go);

	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		GameObject* childGO = new GameObject();
		childGO->name = scene->mMeshes[node->mMeshes[i]]->mName.C_Str();
		childGO->parent = go;

		//Load mesh here
		ComponentMesh* meshRenderer = dynamic_cast<ComponentMesh*>(childGO->GetComponent(ComponentType::C_Mesh));
		meshRenderer->mesh = meshVector[node->mMeshes[i]];

		go->children.push_back(childGO);
	}

	for (size_t i = 0; i < node->mNumChildren; ++i)
	{
		NodeToGameObject(scene, node->mChildren[i], go, meshVector);
	}
}
