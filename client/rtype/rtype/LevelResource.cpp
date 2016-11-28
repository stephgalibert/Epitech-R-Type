#include "LevelResource.hpp"

LevelResource LevelResource::TheLevelResource;

LevelResource::LevelResource(void)
{
}

LevelResource::~LevelResource(void)
{
}

void LevelResource::load(void)
{
	try {
		addTexture("players", "./rsrc/sprites/players.png");
		addTexture("background", "./rsrc/sprites/background.png");
		addTexture("background2", "./rsrc/sprites/background2.png");
		addTexture("explosions", "./rsrc/sprites/explosions.png");
		addMusic("stage_01", "./rsrc/music/stage_01.ogg");
		addSound("explosions", "./rsrc/music/explosion.ogg");
	}
	catch (std::runtime_error const& e) {
		throw (e);
	}
}

sf::Texture *LevelResource::getTextureByKey(std::string const& key)
{
	if (_textures.find(key) != _textures.cend()) {
		return (_textures[key]);
	}
	throw std::runtime_error("Texture " + key + " not found");
}

sf::Music &LevelResource::getMusicByKey(std::string const& key)
{
	try {
		return (_musics.getMusic(key));
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

sf::Sound *LevelResource::getSoundByKey(std::string const& key)
{
	try {
		return (_sounds.getSound(key));
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

void LevelResource::addTexture(std::string const& key, std::string const& path)
{
	sf::Texture *texture = new sf::Texture;
	if (!texture->loadFromFile(path)) {
		throw (std::runtime_error("texture: " + path + " not found"));
	}
	_textures.insert(std::make_pair(key, texture));
}

void LevelResource::addMusic(std::string const& key, std::string const& path)
{
	_musics.addSample(key, path);
}

void LevelResource::addSound(std::string const& key, std::string const& path)
{
	_sounds.addSample(key, path);
}
