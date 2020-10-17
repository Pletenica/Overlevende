
static float PyramidVertices[] = {
	0,0,0,1,0,0,0,0,1,1,0,1,0.5f,1,0.5f,
};

static int PyramidIndices[] = {
	0,1,3,0,3,2,3,1,4,1,0,4,0,2,4,2,3,4,
};

static int CubeVertices[] = {
	//Bottom Vertices
	0.0f ,0.0f, 0.0f,
	1.0f ,0.0f, 0.0f,
	1.0f ,0.0f, 1.0f,
	0.0f ,0.0f, 1.0f,

	//Top Vertices
	0.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f
};

static int CubeIndices[] = {
	//Bottom face
	0,1,2, 2,3,0,
	//Front Face
	3,2,6, 6,7,3,
	//Right face
	6,2,1, 1,5,6,
	//Left face
	4,0,7, 7,0,3,
	//Back face
	1,0,5, 0,4,5,
	//Top face
	4,7,6, 6,5,4
};