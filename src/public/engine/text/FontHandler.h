#pragma once

#include <unordered_map>
#include <optional>
#include <SFML/Graphics/Font.hpp>

class FontHandler
{
public:
	FontHandler() = default;
	FontHandler(const std::string& key, const std::string& fileLocation);

	void LoadFont(const std::string& key, const std::string& fileLocation);

	const std::optional<const sf::Font> GetFont(const std::string& key);

private:
	sf::Font m_font;
	bool m_fontIsLoaded = false;

	std::unordered_map<std::string, sf::Font> m_fonts;

};