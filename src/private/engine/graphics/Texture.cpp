#include "engine/graphics/Texture.h"

#include <stdio.h>

#include "image/stb_image.h"

Texture::Texture()
	: m_textureID(0)
	, m_width(0)
	, m_height(0)
	, m_bitDepth(0)
	, m_fileLocation("")
{}

Texture::Texture(const std::string& fileLocation)
	: m_textureID(0)
	, m_width(0)
	, m_height(0)
	, m_bitDepth(0)
	, m_fileLocation(fileLocation)
{}

Texture::~Texture()
{
	ClearTexture();
}

void Texture::LoadTexture()
{
	unsigned char* textureData = stbi_load(m_fileLocation.c_str(), &m_width, &m_height, &m_bitDepth, 0);
	if (!textureData)
	{
		printf("Failed to find: %s\n", m_fileLocation.c_str());
		return;
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(m_textureType, m_textureID);

	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(m_textureType, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(m_textureType);

	glBindTexture(m_textureType, 0);
	stbi_image_free(textureData);
}

void Texture::LoadCubeMap(std::vector<std::string> faces)
{
	glGenTextures(1, &m_textureID);
	glBindTexture(m_textureType, m_textureID);

	for (size_t i = 0; i < faces.size(); i++)
	{
		unsigned char* textureData = stbi_load(faces[i].c_str(), &m_width, &m_height, &m_bitDepth, 0);
		if (!textureData)
		{
			printf("Failed to find: %s\n", faces[i].c_str());
			return;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + (GLenum)i, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		stbi_image_free(textureData);

	}

	glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(m_textureType, m_textureID);
}


void Texture::UnbindTexture()
{
	glBindTexture(m_textureType, 0);
}

void Texture::ClearTexture()
{
	glDeleteTextures(1, &m_textureID);
	m_textureID = 0;
	m_width = 0;
	m_height = 0;
	m_bitDepth = 0;
	m_fileLocation = "";
}

void Texture::SetTextureType(GLenum type)
{
	m_textureType = type;
}