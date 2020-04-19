#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>
#include <SFML/System/Vector3.hpp>
#include <string>

#include "engine/ECS/Components/TransformComponent.h"

class Shader
{
public:
	Shader();

	~Shader();

	void CreateFromString(const std::string& vertextCode, const std::string& fragementCode);
	void CreateFromFiles(const std::string& vertextFile, const std::string& fragmentFile);

	const std::string ReadFile(const std::string& fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();

	void UseShader();

	void ClearShader();

	void SetProjection(glm::mat4 projection);
	void SetCamera(glm::mat4 camera);

	void SetTranslation(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	void SetRotate(float radians = 0.0f);
	void SetScale(float x, float y, float z);
	void SetScale(float scale = 1.0f);
	void SetTransforms(sf::Vector3f translation, float rotation, sf::Vector3f scale);
	void SetTransforms(TransformComponent& transforms);
	void ResetTransforms();

	void SetColour(glm::vec4 colour);

	bool GetIsFixed();
	void SetIsFixed(bool isFixed);

	void UpdateShader();

private:
	void CompileShader(const std::string& vertextCode, const std::string& fragementCode);
		
	void AddShader(GLuint program, const char* shaderCode, GLenum shaderType);

private:
	GLuint m_shaderId;
	GLuint m_uniformProjection;
	GLuint m_uniformModel;
	GLuint m_uniformView;
	GLuint m_uniformAmbientIntensity;
	GLuint m_uniformAmbientColour;
	GLuint m_uniformColour;

	glm::vec4 m_colour;

	glm::mat4 m_transforms;
	glm::mat4 m_projection;
	glm::mat4 m_camera;

	bool m_isFixed = false;
};
