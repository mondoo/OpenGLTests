#pragma once

#include <SFML/System/Vector3.hpp>
#include "engine/gameframework/entt.hpp"

class Shader;
class Texture;
class Mesh;
class Light;

namespace MeshSystem
{
	void CreateMesh(sf::Vector3f spawnLocation, Shader* shader, Texture* texture, Mesh* mesh, Light* light);

	void UpdateMesh(const entt::entity& playerEntity, float rotation);
};
