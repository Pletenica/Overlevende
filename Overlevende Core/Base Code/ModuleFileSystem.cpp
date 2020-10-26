#include "Globals.h"
#include "Application.h"
#include "ModuleFileSystem.h"
//#include "PathNode.h"

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
	//CreateDir(LIBRARY_PATH);
	//CreateDir(FOLDERS_PATH);
	//CreateDir(MESHES_PATH);
	//CreateDir(TEXTURES_PATH);
	//CreateDir(MATERIALS_PATH);
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

void ModuleFileSystem::DiscoverFiles(const char* directory, std::vector<std::string> & file_list, std::vector<std::string> & dir_list) const
{
	char **rc = PHYSFS_enumerateFiles(directory);
	char **i;

	for (i = rc; *i != nullptr; i++)
	{
		std::string str = std::string(directory) + std::string("/") + std::string(*i);
		if (IsDirectory(str.c_str()))
			dir_list.push_back(*i);
		else
			file_list.push_back(*i);
	}

	PHYSFS_freeList(rc);
}

void ModuleFileSystem::GetAllFilesWithExtension(const char* directory, const char* extension, std::vector<std::string>& file_list) const
{
	std::vector<std::string> files;
	std::vector<std::string> dirs;
	DiscoverFiles(directory, files, dirs);

	for (uint i = 0; i < files.size(); i++)
	{
		std::string ext;
		SplitFilePath(files[i].c_str(), nullptr, nullptr, &ext);

		if (ext == extension)
			file_list.push_back(files[i]);
	}
}

//PathNode M_FileSystem::GetAllFiles(const char* directory, std::vector<std::string>* filter_ext, std::vector<std::string>* ignore_ext) const
//{
//	PathNode root;
//	if (Exists(directory))
//	{
//		root.path = directory;
//		Engine->fileSystem->SplitFilePath(directory, nullptr, &root.localPath);
//		if (root.localPath == "")
//			root.localPath = directory;
//
//		std::vector<std::string> file_list, dir_list;
//		DiscoverFiles(directory, file_list, dir_list);	
//		
//		//Adding all child directories
//		for (uint i = 0; i < dir_list.size(); i++)
//		{
//			std::string str = directory;
//			str.append("/").append(dir_list[i]);
//			root.children.push_back(GetAllFiles(str.c_str(), filter_ext, ignore_ext));
//		}
//		//Adding all child files
//		for (uint i = 0; i < file_list.size(); i++)
//		{
//			//Filtering extensions
//			bool filter = true, discard = false;
//			if (filter_ext != nullptr)
//			{
//				filter = HasExtension(file_list[i].c_str(), *filter_ext);
//			}
//			if (ignore_ext != nullptr)
//			{
//				discard = HasExtension(file_list[i].c_str(), *ignore_ext);
//			}
//			if (filter == true && discard == false)
//			{
//				std::string str = directory;
//				str.append("/").append(file_list[i]);
//				root.children.push_back(GetAllFiles(str.c_str(), filter_ext, ignore_ext));
//			}
//		}
//		root.isFile = HasExtension(root.path.c_str());
//		root.isLeaf = root.children.empty() == true;
//	}
//	return root;
//}

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

std::string ModuleFileSystem::GetUniqueName(const char* path, const char* name) const
{
	//TODO: modify to distinguix files and dirs?
	std::vector<std::string> files, dirs;
	DiscoverFiles(path, files, dirs);

	std::string finalName(name);
	bool unique = false;

	for (uint i = 0; i < 50 && unique == false; ++i)
	{
		unique = true;

		//Build the compare name (name_i)
		if (i > 0)
		{
			finalName = std::string(name).append("_");
			if (i < 10)
				finalName.append("0");
			finalName.append(std::to_string(i));
		}

		//Iterate through all the files to find a matching name
		for (uint f = 0; f < files.size(); ++f)
		{
			if (finalName == files[f])
			{
				unique = false;
				break;
			}
		}
	}
	return finalName;
}