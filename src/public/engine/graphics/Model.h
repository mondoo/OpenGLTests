#pragma once

#include <GLM/glm.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "engine/gameframework/Camera.h"
#include "light/Light.h"

class Model
{
public:
	Model() = default;
	Model(Shader* shader, Texture* texture, Mesh* mesh, Light* light, Camera* camera)
		: m_shader(shader)
		, m_texture(texture)
		, m_mesh(mesh)
		, m_light(light)
		, m_colour(glm::vec4(1.0f))
		, m_camera(camera)
	{}

	~Model()
	{
		m_shader = nullptr;
		delete m_shader;
		m_texture = nullptr;
		delete m_texture;
		m_mesh = nullptr;
		delete m_mesh;
		m_camera = nullptr;
		delete m_camera;
	}

	void SetTransforms(sf::Vector3f translation, float rotation, sf::Vector3f scale)
	{
		m_translation = translation;
		m_rotation = rotation;
		m_scale = scale;
	}

	void SetColour(glm::vec4 colour)
	{
		m_colour = colour;
	}

	void Render()
	{
		if (m_texture)
		{
			m_texture->UseTexture();
		}

		if (m_shader)
		{
			m_shader->SetCamera(!m_shader->GetIsFixed() ? m_camera->CalculateViewMatrix() : glm::mat3(m_camera->CalculateViewMatrix()));

			m_shader->UseShader();
			m_shader->SetColour(m_colour);
			m_shader->SetTransforms(m_translation, m_rotation, m_scale);
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
};