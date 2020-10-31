#include "FBXManager.h"
#include "Globals.h"
#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"

#include"Application.h"

#include"ModuleRenderer3D.h"
#include"ModuleGameObject.h"

#include"ComponentMaterial.h"
#include"ComponentMesh.h"
#include"ComponentTransform.h"

#include "MathGeoLib/Math/float3.h"
#include "MathGeoLib/Math/Quat.h"

#include"Devil/include/ilu.h"
#include"Devil/include/ilut.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")
#include<string>

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

void FBXLoader::ImportFBX(char* _buffer, int _size, int _idTexturesTemporal, const char* _name)
{
	const aiScene* scene = aiImportFileFromMemory(_buffer, _size, aiProcessPreset_TargetRealtime_MaxQuality,nullptr);

	if (scene != nullptr && scene->HasMeshes())
	{
		std::string _p = _name;
		_p = _p.substr(0, _p.find_last_of("."));
		scene->mRootNode->mName = _p;

		aiMesh* new_mesh = nullptr;
		std::vector<Mesh*> meshVector;
		std::vector<GLuint> texturesVector;
		aiString texName;

		ExternalApp->renderer3D->cleanUpTextures = texturesVector;

		aiMeshToMesh(scene, meshVector, texturesVector, &texName, texturesVector);

		ExternalApp->renderer3D->cleanUpMeshes = meshVector;	

		NodeToGameObject(scene, scene->mRootNode, ExternalApp->scene_intro->rootGO, meshVector, texName);

		aiReleaseImport(scene);
	}
	else {
		LOG("Error loading scene /Assets/FBXs/&s.fbx", _name);
	}
}

int FBXLoader::LoadTexture(char* buffer, int _size, int* _width, int* _height)
{
	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);


	if (!ilLoadL(IL_TYPE_UNKNOWN,buffer, _size))
	{
		LOG("Error loading texture");
	}

	*_height = ilGetInteger(IL_IMAGE_HEIGHT);
	*_width = ilGetInteger(IL_IMAGE_WIDTH);

	GLuint glID = ilutGLBindTexImage();
	glBindTexture(GL_TEXTURE_2D, glID);
	ilDeleteImages(1, &imageID);

	return glID;
}


void FBXLoader::aiMeshToMesh(const aiScene* scene, std::vector<Mesh*>& meshVector, std::vector<GLuint>& textureVector, aiString* texName, std::vector<GLuint> texturesVector)
{
	aiMesh* new_mesh;
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		Mesh* _mesh = new Mesh();
		new_mesh = scene->mMeshes[i];

		if (new_mesh->mMaterialIndex != -1)
		{
			aiMaterial* material = scene->mMaterials[0];
			material->GetTexture(aiTextureType_DIFFUSE, 0, texName);

			char* buffer = nullptr;
			std::string _localpath = "Assets/Textures/" + (std::string)texName->C_Str();
			int size = ExternalApp->file_system->Load(_localpath.c_str(), &buffer);

			texturesVector.push_back(FBXLoader::LoadTexture(buffer, size, &_mesh->textureWidth, &_mesh->textureHeight));
			_mesh->textureID = texturesVector[texturesVector.size() - 1];

			delete[] buffer;
		}

		
		LOG("%s", scene->mMeshes[i]->mName.C_Str());

		// copy vertices
		_mesh->num_vertices = new_mesh->mNumVertices;
		_mesh->name = (std::string)new_mesh->mName.C_Str();
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

		if (new_mesh->mMaterialIndex < textureVector.size()) {
			_mesh->textureID = textureVector[new_mesh->mMaterialIndex];
		}
		_mesh->GenBuffers(MeshType::FBXNone);
		meshVector.push_back(_mesh);
	}

}

void FBXLoader::NodeToGameObject(const aiScene* scene, aiNode* node, GameObject* parent, std::vector<Mesh*>& meshVector, aiString _name)
{
	GameObject* go = new GameObject();
	go->name = node->mName.C_Str();
	go->parent = parent;
	parent->children.push_back(go);


	for (size_t i = 0; i < node->mNumMeshes; ++i)
	{
		GameObject* childGO = new GameObject();

		childGO->name = "Model";
		childGO->parent = go;

		//Load mesh here
		ComponentTransform* transform = (ComponentTransform*)(childGO->GetComponent(ComponentType::C_Transform));
		ComponentTransform* transform_parent = (ComponentTransform*)childGO->parent->GetComponent(ComponentType::C_Transform);
		aiVector3D translation, scaling;
		aiQuaternion rotation;

		node->mTransformation.Decompose(scaling, rotation, translation);

		float3 pos(translation.x, translation.y, translation.z);
		float3 scale(scaling.x, scaling.y, scaling.z);
		Quat rot(rotation.x, rotation.y, rotation.z, rotation.w);

		transform->SetTransform(pos, rot, scale);
		transform->global_transform = transform_parent->global_transform * transform->local_transform;

		ComponentMesh* meshRenderer = (ComponentMesh*)(childGO->CreateComponent(ComponentType::C_Mesh));
		meshRenderer->mesh = meshVector[node->mMeshes[i]];
		ComponentMaterial* materialRenderer = (ComponentMaterial*)(childGO->CreateComponent(ComponentType::C_Material));
		materialRenderer->textureID = meshRenderer->mesh->textureID;
		std::string p = "Assets/Textures/" + (std::string)_name.C_Str();
		materialRenderer->texturePath = p;

		go->children.push_back(childGO);
	}


	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		NodeToGameObject(scene, node->mChildren[i], go, meshVector, _name);
	}
}
