#ifndef __Mesh_H__
#define __Mesh_H__

#include "Globals.h"

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

private:

	MeshType _meshType;
};

#endif // __Mesh_H__