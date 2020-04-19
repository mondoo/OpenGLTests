#pragma once

#include <GLM/glm.hpp>
#include <SFML/System/Vector3.hpp>

class Shader;
class Texture;
class Mesh;
class Light;
class Camera;

class Model
{
public:
	Model() = default;
	Model(Shader* shader, Texture* texture, Mesh* mesh, Light* light, Camera* camera);

	~Model();

	void SetTransforms(sf::Vector3f translation, float rotation, sf::Vector3f scale);

	void SetColour(glm::vec4 colour);

	void SetShouldRender(bool shouldRender);

	void Render();

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