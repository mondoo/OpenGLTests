#include "engine/ECS/Components/RenderComponent.h"

#include "engine/graphics/Mesh.h"
#include "engine/graphics/Shader.h"
#include "engine/graphics/Texture.h"
#include "engine/graphics/light/Light.h"
#include "engine/gameframework/Camera.h"

void RenderComponent::SetMesh(Mesh* mesh)
{
	m_mesh = mesh;
}

void RenderComponent::SetShader(Shader* shader)
{
	m_shader = shader;
}

void RenderComponent::SetTexture(Texture* texture)
{
	m_texture = texture;
}

void RenderComponent::SetLight(Light* light)
{
	m_light = light;
}

void RenderComponent::SetColour(glm::vec4 colour)
{
	m_colour = colour;
}

void RenderComponent::SetShouldRender(bool shouldRender)
{
	m_shouldRender = shouldRender;
}

void RenderComponent::Render(TransformComponent& transforms, CameraComponent& camera)
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