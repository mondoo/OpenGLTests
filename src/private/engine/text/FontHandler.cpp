#include "engine/text/FontHandler.h"

FontHandler::FontHandler(const std::string& key, const std::string& fileLocation)
{
	LoadFont(key, fileLocation);
}

void FontHandler::LoadFont(const std::string& key, const std::string& fileLocation)
{
	sf::Font font;
	if (font.loadFromFile(fileLocation))
	{
		m_fonts.insert_or_assign(key, font);
	}
}

const std::optional<const sf::Font> FontHandler::GetFont(const std::string& key)
{
	if (m_fonts.find(key) == m_fonts.end())
	{
		return {};
	}
	return m_fonts[key];
}