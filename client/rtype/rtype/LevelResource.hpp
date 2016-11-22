#pragma once

#include <string>
#include <unordered_map>

#include <SFML\Graphics.hpp>

#include "MusicBox.hpp"
#include "IResourceManager.hpp"

class LevelResource : public IResourceManager
{
public:
	static LevelResource TheLevelResource; // à mettre dans ALevel
public:
	LevelResource(void);
	virtual ~LevelResource(void);

	virtual void load(void);
	sf::Texture *getTextureByKey(std::string const& key);
	sf::Music &getMusicByKey(std::string const& key);

private:
	void addTexture(std::string const& key, std::string const& path);
	void addMusic(std::string const& key, std::string const& path);

	std::unordered_map<std::string, sf::Texture *> _textures;
	MusicBox _musics;
};

