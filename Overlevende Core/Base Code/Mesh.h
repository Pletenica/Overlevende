#ifndef __Mesh_H__
#define __Mesh_H__

#include "Globals.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

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

	GLuint textureID = 0;

private:

	MeshType _meshType;
};

#endif // __Mesh_H__