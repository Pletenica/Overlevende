#include "Globals.h"
#include "Application.h"
#include "ModuleFileSystem.h"
#include "FBXManager.h"
#include "ModuleRenderer3D.h"
#include "ModuleBaseMotor.h"
#include "InspectorWindow.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "Mesh.h"
//#include "PathNode.h"

#include "Resource.h"
#include "PhysFS/include/physfs.h"
#include <fstream>
#include <filesystem>

#include "Assimp/include/cfileio.h"
#include "Assimp/include/types.h"

#pragma comment( lib, "PhysFS/libx86/physfs.lib" )

ModuleFileSystem::ModuleFileSystem(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	// needs to be created before Init so other modules can use it
	char* base_path = SDL_GetBasePath();
	PHYSFS_init(nullptr);
	SDL_free(base_path);

	//Setting the working directory as the writing directory
	if (PHYSFS_setWriteDir(".") == 0)
		LOG("File System error while creating write dir: %s\n", PHYSFS_getLastError());

	AddPath("."); //Adding ProjectFolder (working directory)
	AddPath("Assets");
	CreateLibraryDirectories();
}

// Destructor
ModuleFileSystem::~ModuleFileSystem()
{
	PHYSFS_deinit();
}

// Called before render is available
bool ModuleFileSystem::Init()
{
	LOG("Loading File System");
	bool ret = true;

	// Ask SDL for a write dir
	char* write_path = SDL_GetPrefPath("Pletenica Studios", "Overlevende");

	// Trun this on while in game mode
	//if(PHYSFS_setWriteDir(write_path) == 0)
	//	LOG("File System error while creating write dir: %s\n", PHYSFS_getLastError());

	SDL_free(write_path);

	return ret;
}

// Called before quitting
bool ModuleFileSystem::CleanUp()
{
	//LOG("Freeing File System subsystem");

	return true;
}

void ModuleFileSystem::CreateLibraryDirectories()
{
	CreateDir(LIBRARY_PATH);
	//CreateDir(FOLDERS_PATH);
	CreateDir(MESHES_PATH);
	//CreateDir(TEXTURES_PATH);
	CreateDir(MATERIALS_PATH);
	//CreateDir(MODELS_PATH);
	//CreateDir(ANIMATIONS_PATH);
	//CreateDir(PARTICLES_PATH);
	//CreateDir(SHADERS_PATH);
	//CreateDir(SCENES_PATH);
}

// Add a new zip file or folder
bool ModuleFileSystem::AddPath(const char* path_or_zip)
{
	bool ret = false;

	if (PHYSFS_mount(path_or_zip, nullptr, 1) == 0)
	{
		LOG("File System error while adding a path or zip: %s\n", PHYSFS_getLastError());
	}
	else
		ret = true;

	return ret;
}

// Check if a file exists
bool ModuleFileSystem::Exists(const char* file) const
{
	return PHYSFS_exists(file) != 0;
}

bool ModuleFileSystem::CreateDir(const char* dir)
{
	if (IsDirectory(dir) == false)
	{
		PHYSFS_mkdir(dir);
		return true;
	}
	return false;
}

// Check if a file is a directory
bool ModuleFileSystem::IsDirectory(const char* file) const
{
	return PHYSFS_isDirectory(file) != 0;
}

const char * ModuleFileSystem::GetWriteDir() const
{
	//TODO: erase first annoying dot (".")
	return PHYSFS_getWriteDir();
}

void ModuleFileSystem::DiscoverFiles(const char* directory, std::vector<Resource> &file_list) const
{
	char **rc = PHYSFS_enumerateFiles(directory);
	char **i;

	for (i = rc; *i != nullptr; i++)
	{
		std::string str = std::string(directory) + std::string("/") + std::string(*i);
		if (IsDirectory(str.c_str()))
			file_list.push_back(Resource((*i), true));
		else
			file_list.push_back(Resource((*i),false));
	}

	PHYSFS_freeList(rc);
}

void ModuleFileSystem::GetFilesRecursive(Resource* _resourceroot)
{
	DiscoverFiles(_resourceroot->name.c_str(), _resourceroot->children);

	if (_resourceroot->children.size() != 0) {
		for (int i = 0; i < _resourceroot->children.size(); i++) {
			if (_resourceroot->children[i].isDirectory == true) {
				GetFilesRecursive(&_resourceroot->children[i]);
			}
		}
	}
}

void ModuleFileSystem::GetRealDir(const char* path, std::string& output) const
{
	output = PHYSFS_getBaseDir();

	std::string baseDir = PHYSFS_getBaseDir();
	std::string searchPath = *PHYSFS_getSearchPath();
	std::string realDir = PHYSFS_getRealDir(path);

	output.append(*PHYSFS_getSearchPath()).append("/");
	output.append(PHYSFS_getRealDir(path)).append("/").append(path);
}

std::string ModuleFileSystem::GetPathRelativeToAssets(const char* originalPath) const
{
	std::string ret;
	GetRealDir(originalPath, ret);

	return ret;
}

bool ModuleFileSystem::HasExtension(const char* path) const
{
	std::string ext = "";
	SplitFilePath(path, nullptr, nullptr, &ext);
	return ext != "";
}

bool ModuleFileSystem::HasExtension(const char* path, std::string extension) const
{
	std::string ext = "";
	SplitFilePath(path, nullptr, nullptr, &ext);
	return ext == extension;
}

bool ModuleFileSystem::HasExtension(const char* path, std::vector<std::string> extensions) const
{
	std::string ext = "";
	SplitFilePath(path, nullptr, nullptr, &ext);
	if (ext == "")
		return true;
	for (uint i = 0; i < extensions.size(); i++)
	{
		if (extensions[i] == ext)
			return true;
	}
	return false;
}



std::string ModuleFileSystem::NormalizePath(const char * full_path) const
{
	std::string newPath(full_path);
	for (int i = 0; i < newPath.size(); ++i)
	{
		if (newPath[i] == '\\')
			newPath[i] = '/';
	}
	return newPath;
}

void ModuleFileSystem::SplitFilePath(const char * full_path, std::string * path, std::string * file, std::string * extension) const
{
	if (full_path != nullptr)
	{
		std::string full(full_path);
		size_t pos_separator = full.find_last_of("\\/");
		size_t pos_dot = full.find_last_of(".");

		if (path != nullptr)
		{
			if (pos_separator < full.length())
				*path = full.substr(0, pos_separator + 1);
			else
				path->clear();
		}

		if (file != nullptr)
		{
			if (pos_separator < full.length())
				*file = full.substr(pos_separator + 1, pos_dot - pos_separator - 1);
			else
				*file = full.substr(0, pos_dot);
		}

		if (extension != nullptr)
		{
			if (pos_dot < full.length())
				*extension = full.substr(pos_dot + 1);
			else
				extension->clear();
		}
	}
}

int close_sdl_rwops(SDL_RWops *rw)
{
	//Comented here
	//RELEASE_ARRAY(rw->hidden.mem.base);
	SDL_FreeRW(rw);
	return 0;
}

unsigned int ModuleFileSystem::Save(const char* file, const void* buffer, unsigned int size, bool append) const
{
	unsigned int ret = 0;

	bool overwrite = PHYSFS_exists(file) != 0;
	PHYSFS_file* fs_file = (append) ? PHYSFS_openAppend(file) : PHYSFS_openWrite(file);

	if (fs_file != nullptr)
	{
		uint written = (uint)PHYSFS_write(fs_file, (const void*)buffer, 1, size);
		if (written != size)
		{
			LOG("[error] File System error while writing to file %s: %s", file, PHYSFS_getLastError());
		}
		else
		{
			if (append == true) {
				LOG("Added %u data to [%s%s]", size, GetWriteDir(), file);
			}
			else if (overwrite == true) {

				LOG("File [%s%s] overwritten with %u bytes", GetWriteDir(), file, size);
			}
			else {
				LOG("New file created [%s%s] of %u bytes", GetWriteDir(), file, size);
			}

			ret = written;
		}

		if (PHYSFS_close(fs_file) == 0)
			LOG("[error] File System error while closing file %s: %s", file, PHYSFS_getLastError());
	}
	else
		LOG("[error] File System error while opening file %s: %s", file, PHYSFS_getLastError());

	return ret;
}

unsigned int ModuleFileSystem::Load(const char* path, const char* file, char** buffer) const
{
	std::string full_path(path);
	full_path += file;
	return Load(full_path.c_str(), buffer);
}

// Read a whole file and put it in a new buffer
uint ModuleFileSystem::Load(const char* file, char** buffer) const
{
	uint ret = 0;

	PHYSFS_file* fs_file = PHYSFS_openRead(file);

	if (fs_file != nullptr)
	{
		PHYSFS_sint32 size = (PHYSFS_sint32)PHYSFS_fileLength(fs_file);

		if (size > 0)
		{
			*buffer = new char[size + 1];
			uint readed = (uint)PHYSFS_read(fs_file, *buffer, 1, size);
			if (readed != size)
			{
				LOG("File System error while reading from file %s: %s\n", file, PHYSFS_getLastError());
				delete(buffer);
			}
			else
			{
				ret = readed;
				//Adding end of file at the end of the buffer. Loading a shader file does not add this for some reason
				(*buffer)[size] = '\0';
			}
		}

		if (PHYSFS_close(fs_file) == 0)
			LOG("File System error while closing file %s: %s\n", file, PHYSFS_getLastError());
	}
	else
		LOG("File System error while opening file %s: %s\n", file, PHYSFS_getLastError());

	return ret;
}

void ModuleFileSystem::LoadFileFromPath(const char* _path)
{
	std::string path = _path;
	path = NormalizePath(path.c_str());

	ResourceType _type = ResourceType::R_NONE;
	_type = GetResourceTypeFromPath(path);

	char* buffer = nullptr;
	std::string _p = path.substr(path.find_last_of("/")+1);

	if (_type == ResourceType::R_MESH) {
		std::string _localpath = "Assets/FBXs/" + _p;
		int size = Load(_localpath.c_str(), &buffer);

		if (buffer != nullptr) {
			FBXLoader::ImportFBX(buffer, size, App->renderer3D->imgID, _p.c_str());
		}
	}

	if (_type == ResourceType::R_TEXTURE) {
		std::string _lpath = "Assets/Textures/" + _p;
		std::string _texname = _p.substr(0, _p.find_first_of("."));
		int size = Load(_lpath.c_str(), &buffer);

		ComponentMesh* c_mesh = (ComponentMesh*)App->base_motor->inspector_window->_selectedGO->GetComponent(ComponentType::C_Mesh);
		ComponentMaterial* c_mat = (ComponentMaterial*)App->base_motor->inspector_window->_selectedGO->GetComponent(ComponentType::C_Material);

		if (c_mesh != nullptr && c_mat != nullptr) {
			c_mesh->mesh->textureID = FBXLoader::LoadTexture(buffer, size, &c_mesh->mesh->textureWidth, &c_mesh->mesh->textureHeight, _texname);
			c_mat->textureID = c_mesh->mesh->textureID;
			c_mat->textureAssetsPath = _lpath;
		}
	}

	delete[] buffer;
}

ResourceType ModuleFileSystem::GetResourceTypeFromPath(std::string _path)
{
	ResourceType _type = ResourceType::R_NONE;
	std::string extension = _path.substr(_path.find_last_of(".") + 1);

	if (extension == "fbx" ||
		extension == "FBX" ||
		extension == "DAE" ||
		extension == "dae" ||
		extension == "obj" ||
		extension == "OBJ") {
		
		_type = ResourceType::R_MESH;
	}
	if (extension == "png" ||
		extension == "PNG" ||
		extension == "DDS" ||
		extension == "dds" ||
		extension == "jpeg" ||
		extension == "JPEG" ||
		extension == "tga" ||
		extension == "TGA") {

		_type = ResourceType::R_TEXTURE;
	}

	return _type;
}