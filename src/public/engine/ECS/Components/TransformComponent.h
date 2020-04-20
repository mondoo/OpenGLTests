#pragma once

#include <GLM/glm.hpp>
#include <SFML/System/Vector3.hpp>
#include <GLM/gtc/matrix_transform.hpp>

struct TransformComponent
{
	TransformComponent();

	TransformComponent(sf::Vector3f translation, float rotation, sf::Vector3f scale);

	void SetTranslation(glm::vec3 translation);
		
	void SetTranslation(float x = 0.0f, float y = 0.0f, float z = 0.0f);

	void SetRotatation(float radians = 0.0f);

	void SetScale(glm::vec3 scale);

	void SetScale(float x, float y, float z);

	void SetScale(float scale = 1.0f);

	void ApplyTranslation();

	void ApplyRotation();

	void ApplyScale();
	
	void SetTransforms(sf::Vector3f translation, float rotation, sf::Vector3f scale);

	void ApplyTransforms();

	void ResetTransforms();

	glm::mat4 GetTransforms();

private:
	glm::mat4 m_transforms;

	glm::vec3 m_translation;
	float m_rotation;
	glm::vec3 m_scale;
};