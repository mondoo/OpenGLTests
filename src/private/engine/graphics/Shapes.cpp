#include "engine/graphics/Shapes.h"
#include "engine/graphics/CubeMap.h"

#include <SFML/OpenGL.hpp>

Mesh* Shapes::CreatePyramid()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x		y		z			u		v
			-1.0f,	-1.0f,	0.0f,		0.0f,	0.0f,
			0.0f,	-1.0f,	1.0f,		0.5f,	0.0f,
			1.0f,	-1.0f,	0.0f,		1.0f,	0.0f,
			0.0f,	1.0f,	0.0f,		0.5f,	1.0f
	};

	Mesh* mesh = new Mesh();
	mesh->CreateMesh(vertices, indices, 20, 12);
	return mesh;
}

Mesh* Shapes::CreateCubeMap()
{
	CubeMap* cubeMap = new CubeMap();
	cubeMap->InitialiseCubeMap();
	return cubeMap;
}

Mesh* Shapes::CreateCube()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f, -1.0f,		
		-1.0f, -1.0f, 1.0f,			
		-1.0f, 1.0f, 1.0f,			
		1.0f, 1.0f, -1.0f,			
		-1.0f, -1.0f, -1.0f,		
		-1.0f, 1.0f, -1.0f,			

		1.0f, -1.0f, 1.0f,			
		-1.0f, -1.0f, -1.0f,		
		1.0f, -1.0f, -1.0f,			
		1.0f, 1.0f, -1.0f,			
		1.0f, -1.0f, -1.0f,			
		-1.0f, -1.0f, -1.0f,		

		-1.0f, -1.0f, -1.0f,		
		-1.0f, 1.0f, 1.0f,			
		-1.0f, 1.0f, -1.0f,			
		1.0f, -1.0f, 1.0f,			
		-1.0f, -1.0f, 1.0f,			
		-1.0f, -1.0f, -1.0f,		

		-1.0f, 1.0f, 1.0f,			
		-1.0f, -1.0f, 1.0f,			
		1.0f, -1.0f, 1.0f,			
		1.0f, 1.0f, 1.0f,			
		1.0f, -1.0f, -1.0f,			
		1.0f, 1.0f, -1.0f,			

		1.0f, -1.0f, -1.0f,			
		1.0f, 1.0f, 1.0f,			
		1.0f, -1.0f, 1.0f,			
		1.0f, 1.0f, 1.0f,			
		1.0f, 1.0f, -1.0f,			
		-1.0f, 1.0f, -1.0f,			

		1.0f, 1.0f, 1.0f, 			
		-1.0f, 1.0f, -1.0f,			
		-1.0f, 1.0f, 1.0f,			
		1.0f, 1.0f, 1.0f,			
		-1.0f, 1.0f, 1.0f,			
		1.0f, -1.0f, 1.0f,			
	};

	Mesh* mesh = new Mesh();
	mesh->CreateMesh(vertices, 0, 3 * 36, 12 * 3, false);
	return mesh;
}

Mesh* Shapes::CreatePlane()
{
	GLfloat vertices[] = {
		//	x		y		z	
		-0.8f,  0.8f, 0.0f,
		0.8f,  0.8f, 0.0f,
		-0.8f, -0.8f, 0.0f,

		-0.8f, -0.8f, 0.0f,
		0.8f,  0.8f, 0.0f,
		0.8f, -0.8f, 0.0f,
	};

	Mesh* mesh = new Mesh();
	mesh->CreateMesh(vertices, 0, 12, 12, false);
	return mesh;
}