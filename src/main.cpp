#define STB_IMAGE_IMPLEMENTATION

#include <objbase.h>

#include <vector>

#include "engine/Core.h"
#include "engine/graphics/Graphics.h"

#include "engine/Util/Utilities.h"

Engine engine = Engine();

void main()
{
	CoInitialize(nullptr);

	Global::GetEngine().Init();

	auto playerEntity = PlayerSystem::CreatePlayer();

	MeshSystem::CreateMesh({ 0.0f, 0.0f, -2.5f }, Global::FindAsset<Shader>("DefaultShader"), Global::FindAsset<Texture>("BrickTexture"), Shapes::CreatePyramid(), Global::FindAsset<Light>("GlobalLight"));
	MeshSystem::CreateMesh({ -1.0f, -1.0f, -4.5f }, Global::FindAsset<Shader>("DefaultShader"), Global::FindAsset<Texture>("DirtTexture"), Shapes::CreatePyramid(), Global::FindAsset<Light>("GlobalLight"));
	MeshSystem::CreateMesh({ -2.0f, -2.0f, -4.5f }, Global::FindAsset<Shader>("NullShader"), nullptr, Shapes::CreateCube(), nullptr);
	MeshSystem::CreateMesh({ 0.0f, 0.0f, 0.0f }, Global::FindAsset<Shader>("CubemapShader"), Global::FindAsset<Texture>("SkyboxTexture"), Shapes::CreateCubeMap(), Global::FindAsset<Light>("GlobalLight"));

	float currentRotation = 0.0f;

	while (Global::IsOpen())
	{
		Global::GetEngine().Tick();

		PlayerSystem::UpdatePlayer();

		Global::GetRenderer().Clear();

		Utilities::Rotate(currentRotation, Global::GetDeltaTime());
		MeshSystem::UpdateMesh(playerEntity, Utilities::ToRadians(currentRotation));
		
		glUseProgram(0);

		// SFML 2D
		Global::GetRenderer()->pushGLStates();

		if (TextRenderer* text = Global::FindAsset<TextRenderer>("LogText"))
		{
			text->SetString(Utilities::FPS());
			text->DrawText(Global::GetEngine().GetRenderer());
		}

		Global::GetRenderer()->popGLStates();

		Global::GetRenderer()->display();
	}
}