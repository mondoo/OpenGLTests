#include "engine/graphics/Shader.h"

#include <SFML/OpenGL.hpp>

#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include <stdio.h>
#include <iostream>
#include <fstream>

Shader::Shader()
	: m_shaderId(0)
	, m_uniformProjection(0)
	, m_uniformModel(0)
	, m_transforms(glm::mat4(1.0f))
	, m_colour(glm::vec4(1.0f))
	, m_uniformView(0)
	, m_uniformAmbientIntensity(0)
	, m_uniformAmbientColour(0)
	, m_uniformColour(0)
	, m_camera(glm::mat4(1.0f))
	, m_projection(glm::mat4(1.0f))
{}

Shader::~Shader()
{
	ClearShader();
}

void Shader::CreateFromString(const std::string& vertextCode, const std::string& fragementCode)
{
	CompileShader(vertextCode, fragementCode);
}

void Shader::CreateFromFiles(const std::string& vertextFile, const std::string& fragmentFile)
{
	std::string vertexString = ReadFile(vertextFile);
	std::string fragmentString = ReadFile(fragmentFile);
	CompileShader(vertexString, fragmentString);
}

const std::string Shader::ReadFile(const std::string& fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("Failed to read %s, file doesn't exist", fileLocation.c_str());
		return std::string();
	}

	std::string line = "";

	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content += line + "\n";
	}

	fileStream.close();
	return content;
}

GLuint Shader::GetProjectionLocation()
{
	return m_uniformProjection;
}

GLuint Shader::GetModelLocation()
{
	return m_uniformModel;
}

GLuint Shader::GetViewLocation()
{
	return m_uniformView;
}

GLuint Shader::GetAmbientIntensityLocation()
{
	return m_uniformAmbientIntensity;
}

GLuint Shader::GetAmbientColourLocation()
{
	return m_uniformAmbientColour;
}

void Shader::UseShader()
{
	glUseProgram(m_shaderId);
}

void Shader::ClearShader()
{
	if (m_shaderId != 0)
	{
		glDeleteProgram(m_shaderId);
		m_shaderId = 0;
	}

	m_uniformProjection = 0;
	m_uniformModel = 0;
}

void Shader::SetProjection(glm::mat4 projection)
{
	m_projection = projection;
}

void Shader::SetCamera(glm::mat4 camera)
{
	m_camera = camera;
}

void Shader::SetTranslation(float x /* = 0.0f */, float y /* = 0.0f */, float z /* = 0.0f */)
{
	m_transforms = glm::translate(m_transforms, glm::vec3(x, y, z));
}

void Shader::SetRotate(float radians /* = 0.0f */)
{
	m_transforms = glm::rotate(m_transforms, radians, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Shader::SetScale(float x, float y, float z)
{
	m_transforms = glm::scale(m_transforms, glm::vec3(x, y, z));
}

void Shader::SetScale(float scale /* = 1.0f */)
{
	SetScale(scale, scale, 1.0f);
}

void Shader::SetTransforms(sf::Vector3f translation, float rotation, sf::Vector3f scale)
{
	ResetTransforms();

	SetTranslation(translation.x, translation.y, translation.z);
	SetRotate(rotation);
	SetScale(scale.x, scale.y, scale.z);
}

void Shader::ResetTransforms()
{
	m_transforms = glm::mat4(1.0f);
}

void Shader::SetColour(glm::vec4 colour)
{
	m_colour = colour;
}

bool Shader::GetIsFixed()
{
	return m_isFixed;
}

void Shader::SetIsFixed(bool isFixed)
{
	m_isFixed = isFixed;
}

void Shader::UpdateShader()
{
	glUniformMatrix4fv(m_uniformModel, 1, GL_FALSE, glm::value_ptr(m_transforms));
	glUniformMatrix4fv(m_uniformProjection, 1, GL_FALSE, glm::value_ptr(m_projection));
	glUniformMatrix4fv(m_uniformView, 1, GL_FALSE, glm::value_ptr(m_camera));
	glUniform4fv(m_uniformColour, 1, glm::value_ptr(m_colour));
}

void Shader::CompileShader(const std::string& vertextCode, const std::string& fragementCode)
{
	m_shaderId = glCreateProgram();

	if (!m_shaderId)
	{
		printf("Error creating shader program");
		return;
	}

	AddShader(m_shaderId, vertextCode.c_str(), GL_VERTEX_SHADER);
	AddShader(m_shaderId, fragementCode.c_str(), GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(m_shaderId);
	glGetProgramiv(m_shaderId, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderId, sizeof(eLog), NULL, eLog);
		printf("Error linking program:\n'%s'", eLog);
		return;
	}

	glValidateProgram(m_shaderId);
	glGetProgramiv(m_shaderId, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(m_shaderId, sizeof(eLog), NULL, eLog);
		printf("Error validating program:\n'%s'", eLog);
		return;
	}

	m_uniformProjection = glGetUniformLocation(m_shaderId, "projection");
	m_uniformModel = glGetUniformLocation(m_shaderId, "model");
	m_uniformView = glGetUniformLocation(m_shaderId, "view");
	m_uniformColour = glGetUniformLocation(m_shaderId, "colour");

	m_uniformAmbientIntensity = glGetUniformLocation(m_shaderId, "ambLight.ambientIntensity");
	m_uniformAmbientColour = glGetUniformLocation(m_shaderId, "ambLight.colour");
}

void Shader::AddShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = (GLint)strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader:\n'%s'", shaderType, eLog);
		return;
	}

	glAttachShader(program, theShader);
}