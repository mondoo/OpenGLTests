#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class TextRenderer
{
public:
	TextRenderer() = default;
	~TextRenderer() = default;

	template<typename T = sf::RenderWindow>
	void DrawText(const T& window);

	void SetString(const std::string& string);
	void SetFont(const sf::Font& font);
	void SetColour(const sf::Color& colour);
	void SetScale(const sf::Vector2f& scale = { 1.f, 1.f });

private:
	sf::Font m_font;
	sf::Text m_text;
	bool m_fontIsSet = false;
};

template<typename T>
inline void TextRenderer::DrawText(const T& window)
{
	if (m_fontIsSet)
	{
		m_text.setFont(m_font);
		window->draw(m_text);
	}
}