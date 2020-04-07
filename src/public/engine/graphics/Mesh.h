#pragma once

#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVerticies, unsigned int numOfIndicies, bool hasUVs = true);

	virtual void RenderMesh();

	void ClearMesh();

	GLuint GetVAO();

protected:
	GLuint m_VAO, m_VBO, m_IBO;
	GLsizei m_indexCount;
};