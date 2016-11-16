#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <unordered_map>

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

public:
	ProjectResource(void);
	virtual ~ProjectResource(void);

	virtual void load(void);
	sf::Font const& getFontByKey(std::string const& key) const;
	sf::Music &getMusicByKey(std::string const& key);

private:
	void addFont(std::string const& key, std::string const& fontName);
	void addMusic(std::string const& key, std::string const& path);

	CacheManager<std::string, sf::Font> _fonts;
	MusicBox _musics;
};

