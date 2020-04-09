#pragma once

#include "engine/system/Singleton.h"
#include "engine/system/Root.h"

class Engine : public Singleton<Engine>
{
public:
	Engine();

	~Engine();

	void Init();

	void Loop();

	void UpdateCamera(const std::string& key);

	const float& GetDeltaTime();

	Root* GetRoot();

	Renderer& GetRenderer();

	sf::RenderWindow* GetWindow();

	CameraManager& GetCameraManager();

private:
	Root* m_root;
};