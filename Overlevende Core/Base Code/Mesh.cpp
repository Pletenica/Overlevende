#include "Globals.h"
#include "Mesh.h"
#include "Glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include"FBXManager.h"
#include"MeshesArray.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Glew/libx86/glew32.lib") /* link Microsoft OpenGL lib   */

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &id_indices);
	glDeleteBuffers(1, &id_vertices);

	delete[] vertices;
	delete[] indices;
}
void Mesh::GenBuffers(MeshType _type)
{
	_meshType = _type;

	switch (_type) {
	case(MeshType::Pyramid):
		glBufferData(GL_ARRAY_BUFFER, sizeof(PyramidVertices), PyramidVertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(PyramidIndices), PyramidIndices, GL_STATIC_DRAW);
		break;
	case(MeshType::Cube):
		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices)*24*3, PyramidVertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CubeIndices)*36, CubeIndices, GL_STATIC_DRAW);
		break;
	case(MeshType::FBXNone):
		glGenBuffers(1, (GLuint*)&(id_vertices));
		glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertices * 3, vertices, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*)&(id_indices));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * num_indices, indices, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*)&(id_normals));
		glBindBuffer(GL_ARRAY_BUFFER, id_normals);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_normals * 3, normals, GL_STATIC_DRAW);
		break;
	default:
		glBufferData(GL_ARRAY_BUFFER, sizeof(PyramidVertices), PyramidVertices, GL_STATIC_DRAW);
		break;
	}
}

void Mesh::Render()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, id_normals);
	glNormalPointer(GL_FLOAT, 0, NULL);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);

	switch (_meshType) {
	case(MeshType::FBXNone):
		glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);
	case(MeshType::Pyramid):
		glDrawElements(GL_TRIANGLES, sizeof(PyramidIndices) / sizeof(int), GL_UNSIGNED_INT, NULL);
		break;
	case(MeshType::Cube):
		glDrawElements(GL_TRIANGLES, sizeof(CubeIndices) / sizeof(int), GL_UNSIGNED_INT, NULL);
		break;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}