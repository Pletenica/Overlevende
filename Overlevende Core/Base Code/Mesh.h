#ifndef __Mesh_H__
#define __Mesh_H__

#include "Globals.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>

#include "MathGeoLib/src/Geometry/AABB.h"

enum MeshType {
	FBXNone,
	Sphere,
	Cube,
	Pyramid,
	Cylinder
};

class Mesh {
public:
	Mesh();
	~Mesh();

	void GenBuffers(MeshType _type);
	void Render();

	std::string name;

	uint id_indices = 0; // index in VRAM
	uint num_indices = 0;
	uint* indices = nullptr;


	uint id_vertices = 0; // unique vertex in VRAM
	uint num_vertices = 0;
	float* vertices = nullptr;

	uint id_normals = 0; // unique vertex in VRAM
	uint num_normals = 0;
	float* normals = nullptr;

	uint id_textures = 0;
	uint num_textures = 0;
	float* textures = nullptr;
	int textureWidth = 0;
	int textureHeight = 0;

	GLuint textureID = 0;
	std::string meshPath = "";
	AABB LocalAABB;

private:

	MeshType _meshType;
};

#endif // __Mesh_H__