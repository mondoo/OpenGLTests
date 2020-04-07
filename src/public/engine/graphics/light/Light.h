#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat r, GLfloat g, GLfloat b, GLfloat ambientIntensity);

	glm::vec3 GetColour();
	void SetColour(GLfloat r, GLfloat g, GLfloat b);

	GLfloat GetAmbientIntensity();
	void SetAmbientIntensity(GLfloat intensity);

	void UseLight(GLint ambientIntensityLocation, GLint ambientColourLocation);

private:
	glm::vec3 m_colour;
	GLfloat m_ambientIntensity;
};