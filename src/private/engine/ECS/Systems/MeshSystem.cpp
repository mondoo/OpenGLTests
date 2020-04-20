#include "engine/ECS/Systems/MeshSystem.h"

#include "engine/Global.h"
#include "engine/ECS/Components/Components.h"
#include "engine/graphics/Shapes.h"
#include "engine/graphics/Shader.h"
#include "engine/graphics/Texture.h"
#include "engine/graphics/Mesh.h"
#include "engine/graphics/light/Light.h"

namespace MeshSystem
{
	void CreateMesh(sf::Vector3f spawnLocation, Shader* shader, Texture* texture, Mesh* mesh, Light* light)
	{
		auto entity = Global::GetECS().create();
		auto& transform = Global::GetECS().emplace<TransformComponent>(entity);
		transform.SetTranslation(spawnLocation.x, spawnLocation.y, spawnLocation.z);
		auto& renderComponent = Global::GetECS().emplace<RenderComponent>(entity);
		renderComponent.SetShader(shader);
		renderComponent.SetTexture(texture);
		renderComponent.SetMesh(mesh);
		renderComponent.SetLight(light);
		renderComponent.SetColour(glm::vec4(1.0f));
	}

	void UpdateMesh(const entt::entity& playerEntity, float rotation)
	{
		auto renderView = Global::GetECS().view<RenderComponent, TransformComponent>();
		for (auto entity : renderView)
		{
			auto [transformComponent, renderComponent] = renderView.get<TransformComponent, RenderComponent>(entity);

			transformComponent.SetRotatation(rotation);

			renderComponent.Render(transformComponent, Global::GetECS().get<CameraComponent>(playerEntity));
		}
	}
}