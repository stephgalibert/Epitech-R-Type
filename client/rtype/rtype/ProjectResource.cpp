#include "ProjectResource.hpp"

const std::string ProjectResource::MAIN_FONT = "main_font";
const std::string ProjectResource::MAIN_THEME = "main_theme";

ProjectResource::ProjectResource(void)
{
}

ProjectResource::~ProjectResource(void)
{
	for (auto it : _textures) {
		delete it.second;
	}
}

void ProjectResource::load(void)
{
	try {
		addFont(MAIN_FONT, "./rsrc/font/pixelmix.ttf");
		addMusic(MAIN_THEME, "./rsrc/music/main_theme.wav");
		addTexture("background", "./rsrc/sprites/background.jpg");
	}
	catch (std::runtime_error const& e) {
		throw (e);
	}
}

sf::Font &ProjectResource::getFontByKey(std::string const& key)
{
	if (_fonts.find(key)) {
		return (_fonts[key]);
	}
	throw std::runtime_error("Fonts '" + key + "' not found");
}

sf::Texture *ProjectResource::getTextureByKey(std::string const& key)
{
	if (_textures.find(key) != _textures.cend()) {
		return (_textures[key]);
	}
	throw std::runtime_error("Texture " + key + "not found");
}

sf::Music &ProjectResource::getMusicByKey(std::string const& key)
{
	try {
		return (_musics.getMusic(key));
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

void ProjectResource::addFont(std::string const& key, std::string const& fontName)
{
	sf::Font font;
	if (!font.loadFromFile(fontName)) {
		throw (std::runtime_error(fontName));
	}
	_fonts.insert(key, font);
}

void ProjectResource::addMusic(std::string const& key, std::string const& path)
{
	_musics.addSample(key, path);
}

void ProjectResource::addTexture(std::string const& key, std::string const& path)
{
	sf::Texture *texture = new sf::Texture;
	if (!texture->loadFromFile(path)) {
		throw (std::runtime_error("texture: " + path + " not found"));
	}
	_textures.insert(std::make_pair(key, texture));
}