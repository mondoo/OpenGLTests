#include "engine/graphics/Renderer.h"

Renderer::Renderer(sf::Vector2<int> inSize, const sf::String& inTitle, sf::ContextSettings settings, sf::Uint32 style /* = sf::Style::Default */)
{
	InitRenderer(inSize, inTitle, settings, style);
}

void Renderer::InitRenderer(sf::Vector2<int> inSize, const sf::String& inTitle, sf::ContextSettings settings, sf::Uint32 style /* = sf::Style::Default */)
{
	m_Renderer = new sf::RenderWindow(sf::VideoMode(inSize.x, inSize.y), inTitle, style, settings);
}

Renderer::~Renderer()
{
	m_Renderer = nullptr;
	delete m_Renderer;
}

int Renderer::InitialiseGL()
{
	// Allow extension features
	glewExperimental = GL_TRUE;

	// Init GLEW
	if (glewInit() != GLEW_OK)
	{
		printf("GLEW init failed.");
		m_Renderer->close();
		return 0;
	}

	m_isUsingGL = true;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return 1;
}

void Renderer::Terminate()
{
	m_Renderer->close();
}

void Renderer::Clear()
{
	if (!m_isUsingGL)
	{
		return;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setVerticalSyncEnabled(bool isEnable)
{
	m_Renderer->setVerticalSyncEnabled(true);
}

void Renderer::setMouseCursorVisible(bool isVisible)
{
	m_Renderer->setMouseCursorVisible(false);
}

sf::RenderWindow* Renderer::GetWindow()
{
	return m_Renderer;
}