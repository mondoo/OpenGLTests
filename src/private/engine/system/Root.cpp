#include "engine/system/Root.h"

Root::Root()
	: m_renderer(&Singleton<Renderer>::GetInstance())
	, m_deltaTime(&Singleton<DeltaTime>::GetInstance())
	, m_resourceManager(&Singleton<ResourceManager>::GetInstance())
{
}

Root::~Root()
{
	m_renderer = nullptr;
	delete m_renderer;
	m_deltaTime = nullptr;
	delete m_deltaTime;
}

Renderer* Root::GetRenderer()
{ 
	return m_renderer;
}

DeltaTime* Root::GetDeltaTime() {
	return m_deltaTime;
}

ResourceManager* Root::GetResourceManager()
{
	return m_resourceManager;
}