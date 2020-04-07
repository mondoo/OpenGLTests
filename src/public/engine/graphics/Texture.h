#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>

class Texture
{
public:
	Texture();
	Texture(const std::string& fileLocation);
	~Texture();

	void LoadTexture();
	void LoadCubeMap(std::vector<std::string> faces);

	void UseTexture();
	void UnbindTexture();

	void ClearTexture();

	void SetTextureType(GLenum type);

private:
	GLuint m_textureID;
	int m_width, m_height, m_bitDepth;

	std::string m_fileLocation;

	GLenum m_textureType = GL_TEXTURE_2D;
};