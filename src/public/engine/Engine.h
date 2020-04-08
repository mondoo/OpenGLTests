#pragma once

#include "engine/system/Singleton.h"
#include "engine/system/Root.h"

class Engine : public Singleton<Engine>
{
public:
	Engine()
	{
		m_root = new Root();
	}

	~Engine()
	{
		m_root = nullptr;
		delete m_root;
	}

	void Init()
	{
		Renderer* renderer = m_root->GetRenderer();
		sf::ContextSettings context(24, 8, 2, 3, 3);
		renderer->InitRenderer({ 800, 600 }, "Hello World!", context);
		renderer->setVerticalSyncEnabled(true);
		renderer->setMouseCursorVisible(false);
		if (!renderer->InitialiseGL())
		{
			renderer->Terminate();
			return;
		}

		m_root->GetMouse()->SetCenter(GetRenderer());
	}

	void Loop()
	{
		m_root->GetDeltaTime()->Update();
		UpdateCamera("Main");
		m_root->GetMouse()->SetCenter(GetRenderer());
	}

	void UpdateCamera(const std::string& key)
	{
		if (GetRenderer()->hasFocus())
		{
			GetCameraManager()["Main"]->UpdateKeyboard(GetDeltaTime());
			GetCameraManager()["Main"]->MouseControl(GetDeltaTime(), GetRoot()->GetMouse()->Update(GetRenderer()));
		}
	}

	const float& GetDeltaTime()
	{
		return m_root->GetDeltaTime()->GetDeltaTime();
	}

	Root* GetRoot()
	{
		return m_root;
	}

	Renderer& GetRenderer()
	{
		return *m_root->GetRenderer();
	}

	CameraManager& GetCameraManager()
	{
		return *m_root->GetCameraManager();
	}

private:
	Root* m_root;
};