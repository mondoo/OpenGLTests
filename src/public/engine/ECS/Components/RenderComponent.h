#pragma once

#include <GLM/glm.hpp>

#include "Components.h"

struct RenderComponent
{
	RenderComponent() = default;

	void SetMesh(Mesh* mesh)
	{
		m_mesh = mesh;
	}

	void SetShader(Shader* shader)
	{
		m_shader = shader;
	}

	void SetTexture(Texture* texture)
	{
		m_texture = texture;
	}

	void SetLight(Light* light)
	{
		m_light = light;
	}

	void SetColour(glm::vec4 colour)
	{
		m_colour = colour;
	}

	void SetShouldRender(bool shouldRender)
	{
		m_shouldRender = shouldRender;
	}

	void Render(TransformComponent& transforms, CameraComponent& camera)
	{
		transforms.ApplyTransforms();

		if (!m_shouldRender)
		{
			return;
		}

		if (m_texture)
		{
			m_texture->UseTexture();
		}

		if (m_shader)
		{
			m_shader->SetCamera(!m_shader->GetIsFixed() ? camera.CalculateViewMatrix() : glm::mat3(camera.CalculateViewMatrix()));

			m_shader->UseShader();
			m_shader->SetColour(m_colour);
			m_shader->SetTransforms(transforms);
			if (m_light)
			{
				m_light->UseLight(m_shader->GetAmbientIntensityLocation(), m_shader->GetAmbientColourLocation());
			}

			m_shader->UpdateShader();
		}

		if (m_mesh)
		{
			m_mesh->RenderMesh();
		}

		if (m_texture)
		{
			m_texture->UnbindTexture();
		}
	}

private:
	Shader* m_shader;
	Texture* m_texture;
	Mesh* m_mesh;
	Light* m_light;
	Camera* m_camera;
	glm::vec4 m_colour;

	sf::Vector3f m_translation;
	float m_rotation;
	sf::Vector3f m_scale;

	bool m_shouldRender = true;
};