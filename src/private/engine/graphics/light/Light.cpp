#include "engine/graphics/light/Light.h"

Light::Light()
	: m_colour(glm::vec3(1.0f, 1.0f, 1.0f))
	, m_ambientIntensity(1.0f)
{}

Light::Light(GLfloat r, GLfloat g, GLfloat b, GLfloat ambientIntensity)
	: m_colour(glm::vec3(r, g, b))
	, m_ambientIntensity(ambientIntensity)
{}

glm::vec3 Light::GetColour() { 
	return m_colour; 
}

void Light::SetColour(GLfloat r, GLfloat g, GLfloat b)
{
	m_colour = glm::vec3(r, g, b);
}

GLfloat Light::GetAmbientIntensity() {
	return m_ambientIntensity; 
}

void Light::SetAmbientIntensity(GLfloat intensity)
{
	m_ambientIntensity = intensity;
}

void Light::UseLight(GLint ambientIntensityLocation, GLint ambientColourLocation)
{
	glUniform3f(ambientColourLocation, m_colour.x, m_colour.y, m_colour.z);
	glUniform1f(ambientIntensityLocation, m_ambientIntensity);
}
