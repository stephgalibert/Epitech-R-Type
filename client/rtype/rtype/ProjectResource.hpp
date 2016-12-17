#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <unordered_map>
#include <memory>

#include "IResourceManager.hpp"

#include "MusicBox.hpp"
#include "SoundBox.hpp"
#include "CacheManager.hpp"
#include "StaticTools.hpp"

class ProjectResource : public IResourceManager
{
public:
	static const std::string MAIN_FONT;
	static const std::string MAIN_THEME;
	static ProjectResource TheProjectResource;

public:
	ProjectResource(void);
	virtual ~ProjectResource(void);

	virtual void load(void);
	sf::Font &getFontByKey(std::string const& key);
	sf::Texture *getTextureByKey(std::string const& key);
	sf::Music &getMusicByKey(std::string const& key);
	sf::Sound *getSoundByKey(std::string const& key);

private:
	void addFont(std::string const& key, std::string const& fontName);
	void addTexture(std::string const& key, std::string const& path);
	void addMusic(std::string const& key, std::string const& path);
	void addSound(std::string const& key, std::string const& path);

	CacheManager<std::string, sf::Font> _fonts;
	std::unordered_map<std::string, sf::Texture *> _textures;
	SoundBox _sounds;
	MusicBox _musics;
};

