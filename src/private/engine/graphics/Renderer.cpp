#include "engine/graphics/Renderer.h"

template<class TY>
Renderer::~Renderer()
{
	m_Renderer = nullptr;
	delete m_Renderer;
}

T* operator->() const
{
	return &*m_Renderer;
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

T* GetWindow()
{
	return m_Renderer;
}