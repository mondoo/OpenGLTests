#define STB_IMAGE_IMPLEMENTATION

#include <objbase.h>

#include <vector>

#include "engine/graphics/Graphics.h"

#include "engine/text/FontHandler.h"
#include "engine/text/TextRenderer.h"

#include "engine/Global.h"
#include "engine/Boot.h"
#include "engine/types/SystemTypes.h"
#include "engine/gameframework/entt.hpp"
#include "engine/ECS/Components/Components.h"
#include "engine/ECS/Systems/Systems.h"

constexpr float toRadians = 3.14159265f / 180.0f;

Engine engine = Engine();

void main()
{
	CoInitialize(nullptr);

	Global::GetEngine().Init();

	Light* ambientLight;
	ambientLight = new Light();
	ambientLight->SetColour(1.0f, 1.0f, 1.0f);

	Boot::LoadAssets();

	const glm::mat4 projection = glm::perspective(45.0f, (GLfloat)Global::GetEngine().GetRenderer()->getSize().x / (GLfloat)Global::GetEngine().GetRenderer()->getSize().y, 0.1f, 500.0f);
	
	std::vector<Shader*> shaders;
	Global::FilterAssetsByType<Shader>(shaders, ResourceType::Shader);
	for (Shader* shader : shaders)
	{
		shader->SetProjection(projection);
	}

	FontHandler* font = new FontHandler("FreePixel", "assets/fonts/FreePixel.ttf");
	TextRenderer* text = new TextRenderer();
	if (font->GetFont("FreePixel").has_value())
	{
		text->SetFont(font->GetFont("FreePixel").value());
		text->SetColour(sf::Color::Red);
		text->SetScale({ 1.0f, 1.0f });
	}

	auto playerEntity = PlayerSystem::CreatePlayer();

	MeshSystem::CreateMesh({ 0.0f, 0.0f, -2.5f }, Global::FindAsset<Shader>("DefaultShader"), Global::FindAsset<Texture>("BrickTexture"), Shapes::CreatePyramid(), ambientLight);
	MeshSystem::CreateMesh({ -1.0f, -1.0f, -4.5f }, Global::FindAsset<Shader>("DefaultShader"), Global::FindAsset<Texture>("DirtTexture"), Shapes::CreatePyramid(), ambientLight);
	MeshSystem::CreateMesh({ -2.0f, -2.0f, -4.5f }, Global::FindAsset<Shader>("NullShader"), nullptr, Shapes::CreateCube(), nullptr);
	MeshSystem::CreateMesh({ 0.0f, 0.0f, 0.0f }, Global::FindAsset<Shader>("CubemapShader"), Global::FindAsset<Texture>("SkyboxTexture"), Shapes::CreateCubeMap(), ambientLight);

	float currentRotation = 0.0f;
	float currentSize = 0.4f;

	while (Global::IsOpen())
	{
		sf::Event Event;
		while (Global::GetRenderer()->pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				Global::GetRenderer().Terminate();
			}
			if (Event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					Global::GetRenderer().Terminate();
				}
			}
		}

		Global::GetEngine().Loop();

		PlayerSystem::UpdatePlayer();

		Global::GetRenderer().Clear();

		currentRotation += 60.0f * Global::GetDeltaTime();
		if (currentRotation >= 360.f)
		{
			currentRotation = 0.0f;
		}

		MeshSystem::UpdateMesh(playerEntity, currentRotation* toRadians);
		
		glUseProgram(0);

		// SFML 2D
		Global::GetRenderer()->pushGLStates();
		text->SetString(std::to_string((int)(1.f / Global::GetDeltaTime())) + "FPS");
		text->DrawText(Global::GetEngine().GetRenderer());
		Global::GetRenderer()->popGLStates();

		Global::GetRenderer()->display();
	}
}