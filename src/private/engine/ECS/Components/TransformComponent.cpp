#include "engine/ECS/Components/TransformComponent.h"

TransformComponent::TransformComponent()
	: m_transforms(glm::mat4(1.0f))
	, m_translation(glm::vec3(1.0f))
	, m_rotation(0.f)
	, m_scale(1.0f)
{}

TransformComponent::TransformComponent(sf::Vector3f translation, float rotation, sf::Vector3f scale)
{
	SetTransforms(translation, rotation, scale);
	ApplyTransforms();
}

void TransformComponent::SetTranslation(glm::vec3 translation)
{
	m_translation = translation;
}

void TransformComponent::SetTranslation(float x, float y, float z)
{
	m_translation = glm::vec3(x, y, z);
}

void TransformComponent::SetRotatation(float radians)
{
	m_rotation = radians;
}

void TransformComponent::SetScale(glm::vec3 scale)
{
	m_scale = scale;
}

void TransformComponent::SetScale(float x, float y, float z)
{
	m_scale = glm::vec3(x, y, z);
}

void TransformComponent::SetScale(float scale)
{
	SetScale(scale, scale, 1.0f);
}

void TransformComponent::ApplyTranslation()
{
	m_transforms = glm::translate(m_transforms, m_translation);
}

void TransformComponent::ApplyRotation()
{
	m_transforms = glm::rotate(m_transforms, m_rotation, glm::vec3(0.0f, 1.0f, 0.0f));
}

void TransformComponent::ApplyScale()
{
	m_transforms = glm::scale(m_transforms, m_scale);
}

void TransformComponent::SetTransforms(sf::Vector3f translation, float rotation, sf::Vector3f scale)
{
	SetTranslation(translation.x, translation.y, translation.z);
	SetRotatation(rotation);
	SetScale(scale.x, scale.y, scale.z);
}

void TransformComponent::ApplyTransforms()
{
	ResetTransforms();

	ApplyTranslation();
	ApplyRotation();
	ApplyScale();
}

void TransformComponent::ResetTransforms()
{
	m_transforms = glm::mat4(1.0f);
}

glm::mat4 TransformComponent::GetTransforms()
{
	return m_transforms;
}