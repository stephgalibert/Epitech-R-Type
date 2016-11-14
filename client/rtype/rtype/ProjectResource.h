#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <unordered_map>

class ProjectResource
{
public:
	static void load(void);
	static sf::Font const& getFontByKey(std::string const& key);

private:
	static void addFont(std::string const& key, std::string const& fontName);

	static std::map<std::string, sf::Font> Fonts;
};

