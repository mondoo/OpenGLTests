#include "engine/text/TextRenderer.h"

void TextRenderer::SetString(const std::string& string)
{
	m_text.setString(string);
}

void TextRenderer::SetFont(const sf::Font& font)
{
	m_font = font;
	m_fontIsSet = true;
}

void TextRenderer::SetColour(const sf::Color& colour)
{
	m_text.setFillColor(colour);
}

void TextRenderer::SetScale(const sf::Vector2f& scale /* = { 1.f, 1.f } */)
{
	m_text.setScale(scale);
}