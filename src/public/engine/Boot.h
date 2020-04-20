#pragma once

#include "engine/Core.h"
#include "engine/graphics/Graphics.h"

namespace Boot
{
	void LoadAssets()
	{
		const std::string assetDirectory = "assets/";

		Texture* brickTexture = new Texture(assetDirectory + "textures/brick.png");
		brickTexture->LoadTexture();
		Global::GetEngine().GetResourceManager()->Create("BrickTexture", brickTexture, ResourceType::Image);

		Texture* dirtTexture = new Texture(assetDirectory + "textures/dirt.png");
		dirtTexture->LoadTexture();
		Global::GetEngine().GetResourceManager()->Create("DirtTexture", dirtTexture, ResourceType::Image);

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
		Global::GetEngine().GetResourceManager()->Create("SkyboxTexture", skyboxTexture, ResourceType::Image);

		Shader* shader = new Shader();
		shader->CreateFromFiles("shaders/shader.vert", "shaders/shader.frag");
		Global::GetEngine().GetResourceManager()->Create("DefaultShader", shader, ResourceType::Shader);

		Shader* cubeMap = new Shader();
		cubeMap->CreateFromFiles("shaders/cubemap.vert", "shaders/cubemap.frag");
		cubeMap->SetIsFixed(true);
		Global::GetEngine().GetResourceManager()->Create("CubemapShader", cubeMap, ResourceType::Shader);

		Shader* blank = new Shader();
		blank->CreateFromFiles("shaders/blank.vert", "shaders/blank.frag");
		Global::GetEngine().GetResourceManager()->Create("NullShader", blank, ResourceType::Shader);

		FontHandler* font = new FontHandler("FreePixel", "assets/fonts/FreePixel.ttf");
		Global::GetEngine().GetResourceManager()->Create("DefaultFont", font, ResourceType::Font);

		TextRenderer* text = new TextRenderer();
		if (font->GetFont("FreePixel").has_value())
		{
			text->SetFont(font->GetFont("FreePixel").value());
			text->SetColour(sf::Color::Red);
			text->SetScale({ 1.0f, 1.0f });
		}
		Global::GetEngine().GetResourceManager()->Create("LogText", text, ResourceType::Text);

		Light* ambientLight;
		ambientLight = new Light();
		ambientLight->SetColour(1.0f, 1.0f, 1.0f);
		Global::GetEngine().GetResourceManager()->Create("GlobalLight", ambientLight, ResourceType::Light);
	}
}