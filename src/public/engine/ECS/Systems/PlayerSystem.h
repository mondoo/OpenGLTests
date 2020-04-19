#pragma once

#include "engine/Global.h"
#include "engine/gameframework/entt.hpp"
#include "engine/ECS/Components/Components.h"

namespace PlayerSystem
{
	entt::entity CreatePlayer()
	{
		auto entity = Global::GetECS().create();
		Global::GetECS().emplace<PlayerComponent>(entity);
		Global::GetECS().emplace<TransformComponent>(entity);
		Global::GetECS().emplace<InputComponent>(entity, true);
		auto& cameraComponent = Global::GetECS().emplace<CameraComponent>(entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 50.0f);
	
		return entity;
	}

	void UpdatePlayer()
	{
		auto playerView = Global::GetECS().view<PlayerComponent, TransformComponent, InputComponent, CameraComponent>();
		for (auto entity : playerView)
		{
			auto [inputComponent, cameraComponent] = playerView.get<InputComponent, CameraComponent>(entity);
			inputComponent.Update(Global::GetWindow());
			cameraComponent.UpdateInput(inputComponent, Global::GetDeltaTime());
		}
	}
}