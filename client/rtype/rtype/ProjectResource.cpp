#include "ProjectResource.hpp"

const std::string ProjectResource::MAIN_FONT = "main_font";
const std::string ProjectResource::MAIN_THEME = "main_theme";

ProjectResource ProjectResource::TheProjectResource;

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
		addTexture("hud1", "./rsrc/sprites/hud1.png");

		addTexture("shots1", "./rsrc/sprites/shots1.png");
		addTexture("shots2", "./rsrc/sprites/shots2.png");
		addTexture("shots3", "./rsrc/sprites/shots3.png");
		addTexture("shots4", "./rsrc/sprites/shots4.png");
		addTexture("players", "./rsrc/sprites/players.bmp");
		addTexture("background", "./rsrc/sprites/background.png");
		addTexture("background2", "./rsrc/sprites/background2.png");
		addTexture("explosions", "./rsrc/sprites/explosions.png");
		addTexture("powerups1", "./rsrc/sprites/powerups1.png");

		addMusic("stage_01", "./rsrc/music/stage_01.ogg");
		addMusic("game_over", "./rsrc/music/game_over.ogg");
		addSound("explosions", "./rsrc/music/explosion.ogg");
		addSound("shot", "./rsrc/music/shot.wav");
		//addTexture("hud2", "./rsrc/sprites/hud2.png");
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
	throw std::runtime_error("Texture " + key + " not found");
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

sf::Sound *ProjectResource::getSoundByKey(std::string const& key)
{
	try {
		return (_sounds.getSound(key));
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

void ProjectResource::addSound(std::string const& key, std::string const& path)
{
	_sounds.addSample(key, path);
}