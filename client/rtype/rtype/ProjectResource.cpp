#include "ProjectResource.h"

std::map<std::string, sf::Font> ProjectResource::Fonts;

void ProjectResource::load(void)
{
	try {
		addFont("main", "./rsrc/font/pixelmix.ttf");
	}
	catch (std::runtime_error const& e) {
		throw (e);
	}
}

sf::Font const& ProjectResource::getFontByKey(std::string const& key)
{
	if (Fonts.find(key) != Fonts.cend()) {
		return (Fonts.at(key));
	}
	throw std::runtime_error("Fonts '" + key + "' not found");
}

void ProjectResource::addFont(std::string const& key, std::string const& fontName)
{
	sf::Font font;
	if (!font.loadFromFile(fontName)) {
		throw (std::runtime_error(fontName));
	}
	Fonts.insert(std::make_pair(key, font));
}