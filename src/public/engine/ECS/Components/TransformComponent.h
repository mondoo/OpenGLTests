#pragma once

#include <GLM/glm.hpp>
#include <SFML/System/Vector3.hpp>
#include <GLM/gtc/matrix_transform.hpp>

struct TransformComponent
{
	TransformComponent()
		: m_transforms(glm::mat4(1.0f))
		, m_translation(glm::vec3(1.0f))
		, m_rotation(0.f)
		, m_scale(1.0f)
	{}

	TransformComponent(sf::Vector3f translation, float rotation, sf::Vector3f scale)
	{
		SetTransforms(translation, rotation, scale);
		ApplyTransforms();
	}

	void SetTranslation(glm::vec3 translation)
	{
		m_translation = translation;
	}
		
	void SetTranslation(float x = 0.0f, float y = 0.0f, float z = 0.0f)
	{
		m_translation = glm::vec3(x, y, z);
	}

	void SetRotatation(float radians = 0.0f)
	{
		m_rotation = radians;
	}

	void SetScale(glm::vec3 scale)
	{
		m_scale = scale;
	}

	void SetScale(float x, float y, float z)
	{
		m_scale = glm::vec3(x, y, z);
	}

	void SetScale(float scale = 1.0f)
	{
		SetScale(scale, scale, 1.0f);
	}

	void ApplyTranslation()
	{
		m_transforms = glm::translate(m_transforms, m_translation);
	}

	void ApplyRotation()
	{
		m_transforms = glm::rotate(m_transforms, m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void ApplyScale()
	{
		m_transforms = glm::scale(m_transforms, m_scale);
	}
	
	void SetTransforms(sf::Vector3f translation, float rotation, sf::Vector3f scale)
	{
		SetTranslation(translation.x, translation.y, translation.z);
		SetRotatation(rotation);
		SetScale(scale.x, scale.y, scale.z);
	}

	void ApplyTransforms()
	{
		ResetTransforms();

		ApplyTranslation();
		ApplyRotation();
		ApplyScale();
	}

	void ResetTransforms()
	{
		m_transforms = glm::mat4(1.0f);
	}

	glm::mat4 GetTransforms()
	{
		return m_transforms;
	}

private:
	glm::mat4 m_transforms;

	glm::vec3 m_translation;
	float m_rotation;
	glm::vec3 m_scale;
};