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

static const std::string assetDirectory = "assets/";
constexpr float toRadians = 3.14159265f / 180.0f;

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

void AddModel(std::vector<Model*>& models, Shader* shader, Texture* texture, Mesh* mesh, Light* light, Camera* camera)
{
	Model* model = new Model(shader, texture, mesh, light, camera);
	models.push_back(model);
}

void main()
{
	Engine engine = Engine();
	engine.Init();
	engine.GetRoot()->GetCameraManager()->AddCamera("Main", new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 50.0f));

	std::vector<Shader*> shaders;
	Light* ambientLight;
	FontHandler* font = new FontHandler("FreePixel", assetDirectory + "fonts/FreePixel.ttf");

	std::unordered_map<std::string, Texture*> textures;
	LoadTextures(textures);

	CreateShaders(shaders);

	const glm::mat4 projection = glm::perspective(45.0f, (GLfloat)engine.GetRenderer()->getSize().x / (GLfloat)engine.GetRenderer()->getSize().y, 0.1f, 500.0f);
	for (Shader* shader : shaders)
	{
		shader->SetProjection(projection);
	}

	ambientLight = new Light();
	ambientLight->SetColour(1.0f, 1.0f, 1.0f);

	std::vector<Model*> models;
	AddModel(models, shaders[0], textures["BrickTexture"], Shapes::CreatePyramid(), ambientLight, engine.GetCameraManager()["Main"]);
	AddModel(models, shaders[0], textures["DirtTexture"], Shapes::CreatePyramid(), ambientLight, engine.GetCameraManager()["Main"]);
	AddModel(models, shaders[2], nullptr, Shapes::CreateCube(), nullptr, engine.GetCameraManager()["Main"]);
	AddModel(models, shaders[1], textures["SkyboxTexture"], Shapes::CreateCubeMap(), ambientLight, engine.GetCameraManager()["Main"]);

	float currentRotation = 0.0f;
	float currentSize = 0.4f;
	bool sizeDirection = true;

	TextRenderer* text = new TextRenderer();
	if (font->GetFont("FreePixel").has_value())
	{
		text->SetFont(font->GetFont("FreePixel").value());
		text->SetColour(sf::Color::Red);
		text->SetScale({1.0f, 1.0f});
	}
	
	bool lightForward = true;



	while (engine.GetRenderer()->isOpen())
	{
		sf::Event Event;
		while (engine.GetRenderer()->pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				engine.GetRenderer().Terminate();
			}
			if (Event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					engine.GetRenderer().Terminate();
				}
			}
		}

		engine.Loop();

		GLfloat intensity = ambientLight->GetAmbientIntensity();
		intensity += (lightForward ? 0.3f : -0.3f) * engine.GetDeltaTime();
		if (intensity >= 1.0f)
		{
			lightForward = false;
			intensity = 1.0f;
		}
		else if (intensity <= 0.0f)
		{
			lightForward = true;
			intensity = 0.0f;
		}
		ambientLight->SetAmbientIntensity(intensity);


		currentRotation += 60.0f * engine.GetDeltaTime();
		if (currentRotation >= 360.f)
		{
			currentRotation = 0.0f;
		}
		models[0]->SetTransforms(
			{ 0.0f, 0.0f, -2.5f },
			currentRotation * toRadians,
			{ currentSize, currentSize, currentSize }
		);
		models[1]->SetTransforms(
			{ -1.0f, -1.0f, -4.5f },
			currentRotation * toRadians,
			{ currentSize, currentSize, currentSize }
		);
		models[2]->SetTransforms(
			{ 1.0f, -1.0f, -4.5f },
			currentRotation * toRadians,
			{ currentSize, currentSize, currentSize }
		);

		
		// Draw
		engine.GetRenderer().Clear();

		for (Model* model : models)
		{
			model->Render();
		}

		glUseProgram(0);

		// SFML 2D
		engine.GetRenderer()->pushGLStates();
		text->SetString(std::to_string((int)(1.f / engine.GetDeltaTime())) + "FPS");
		text->DrawText(engine.GetRenderer());
		engine.GetRenderer()->popGLStates();
		
		engine.GetRenderer()->display();
	}
}