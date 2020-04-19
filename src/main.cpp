#define STB_IMAGE_IMPLEMENTATION

#include <vector>
#include <iostream>
#include <unordered_map>

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
// OpenGL
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

// Engine
#include "engine/system/Singleton.h"
#include "engine/system/Root.h"
#include "engine/Engine.h"

#include "engine/graphics/Shader.h"
#include "engine/graphics/Renderer.h"

#include "engine/gameframework/DeltaTime.h"
#include "engine/gameframework/CameraManager.h"
#include "engine/gameframework/Camera.h"
#include "engine/gameframework/Mouse.h"

#include "engine/graphics/Mesh.h"
#include "engine/graphics/Shapes.h"
#include "engine/graphics/CubeMap.h"
#include "engine/graphics/Model.h"
#include "engine/graphics/Texture.h"
#include "engine/graphics/light/Light.h"

#include "engine/text/FontHandler.h"
#include "engine/text/TextRenderer.h"


#include "engine/gameframework/entt.hpp"
#include "engine/ECS/Components/Components.h"


#include "engine/Global.h"
#include "engine/ECS/Systems/Systems.h"

static const std::string assetDirectory = "assets/";
constexpr float toRadians = 3.14159265f / 180.0f;

Engine engine = Engine();

static Engine& GetEngine()
{
	return engine;
}

void CreateShaders(std::vector<Shader*>& shaders)
{
	Shader* shader = new Shader();
	shader->CreateFromFiles("shaders/shader.vert", "shaders/shader.frag");
	shaders.push_back(shader);

	Shader* cubeMap = new Shader();
	cubeMap->CreateFromFiles("shaders/cubemap.vert", "shaders/cubemap.frag");
	cubeMap->SetIsFixed(true);
	shaders.push_back(cubeMap);

	Shader* blank = new Shader();
	blank->CreateFromFiles("shaders/blank.vert", "shaders/blank.frag");
	shaders.push_back(blank);
}

void LoadTextures(std::unordered_map<std::string, Texture*>& textures)
{
	Texture* brickTexture = new Texture(assetDirectory + "textures/brick.png");
	brickTexture->LoadTexture();
	
	Texture* dirtTexture = new Texture(assetDirectory + "textures/dirt.png");
	dirtTexture->LoadTexture();

	Texture* skyboxTexture = new Texture();
	skyboxTexture->SetTextureType(GL_TEXTURE_CUBE_MAP);
	skyboxTexture->LoadCubeMap({
		assetDirectory + "textures/skybox/right.jpg",
		assetDirectory + "textures/skybox/left.jpg",
		assetDirectory + "textures/skybox/top.jpg",
		assetDirectory + "textures/skybox/bottom.jpg",
		assetDirectory + "textures/skybox/front.jpg",
		assetDirectory + "textures/skybox/back.jpg"
	});

	textures.insert({ "BrickTexture", brickTexture });
	textures.insert({ "DirtTexture", dirtTexture });
	textures.insert({ "SkyboxTexture", skyboxTexture });
}

void main()
{
	Global::GetEngine().Init();

	std::vector<Shader*> shaders;
	Light* ambientLight;
	ambientLight = new Light();
	ambientLight->SetColour(1.0f, 1.0f, 1.0f);

	std::unordered_map<std::string, Texture*> textures;
	LoadTextures(textures);
	CreateShaders(shaders);

	const glm::mat4 projection = glm::perspective(45.0f, (GLfloat)Global::GetEngine().GetRenderer()->getSize().x / (GLfloat)Global::GetEngine().GetRenderer()->getSize().y, 0.1f, 500.0f);
	for (Shader* shader : shaders)
	{
		shader->SetProjection(projection);
	}

	FontHandler* font = new FontHandler("FreePixel", assetDirectory + "fonts/FreePixel.ttf");
	TextRenderer* text = new TextRenderer();
	if (font->GetFont("FreePixel").has_value())
	{
		text->SetFont(font->GetFont("FreePixel").value());
		text->SetColour(sf::Color::Red);
		text->SetScale({ 1.0f, 1.0f });
	}

	auto playerEntity = PlayerSystem::CreatePlayer();

	MeshSystem::CreateMesh({ 0.0f, 0.0f, -2.5f }, shaders[0], textures["BrickTexture"], Shapes::CreatePyramid(), ambientLight);
	MeshSystem::CreateMesh({ -1.0f, -1.0f, -4.5f }, shaders[0], textures["DirtTexture"], Shapes::CreatePyramid(), ambientLight);
	MeshSystem::CreateMesh({ -2.0f, -2.0f, -4.5f }, shaders[2], nullptr, Shapes::CreateCube(), nullptr);
	MeshSystem::CreateMesh({ 0.0f, 0.0f, 0.0f }, shaders[1], textures["SkyboxTexture"], Shapes::CreateCubeMap(), ambientLight);

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