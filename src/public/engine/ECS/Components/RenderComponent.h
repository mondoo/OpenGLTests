#pragma once

#include <GLM/glm.hpp>

#include "Components.h"

class Mesh;
class Shader;
class Texture;
class Light;
class Camera;

struct RenderComponent
{
	RenderComponent() = default;

	void SetMesh(Mesh* mesh);

	void SetShader(Shader* shader);

	void SetTexture(Texture* texture);

	void SetLight(Light* light);

	void SetColour(glm::vec4 colour);

	void SetShouldRender(bool shouldRender);

	void Render(TransformComponent& transforms, CameraComponent& camera);

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