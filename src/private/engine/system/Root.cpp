#include "engine/system/Root.h"

Root::Root()
	: m_renderer(&Singleton<Renderer>::GetInstance())
	, m_camera(&Singleton<CameraManager>::GetInstance())
	, m_mouse(&Singleton<Mouse>::GetInstance())
	, m_deltaTime(&Singleton<DeltaTime>::GetInstance())
{
}

Root::~Root()
{
	m_renderer = nullptr;
	delete m_renderer;
	m_camera = nullptr;
	delete m_camera;
	m_mouse = nullptr;
	delete m_mouse;
	m_deltaTime = nullptr;
	delete m_deltaTime;
}

Renderer* Root::GetRenderer()
{ 
	return m_renderer;
}

CameraManager* Root::GetCameraManager() {
	return m_camera;
}

Mouse* Root::GetMouse() {
	return m_mouse;
}

DeltaTime* Root::GetDeltaTime() {
	return m_deltaTime;
}