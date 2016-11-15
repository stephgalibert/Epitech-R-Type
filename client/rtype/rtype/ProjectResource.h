#pragma once

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <unordered_map>

#include "MusicBox.hpp"
#include "SoundBox.hpp"
#include "MemoryFile.hpp"
#include "CacheManager.hpp"
#include "StaticTools.h"

class ProjectResource
{
public:
	static void Load(void);
	static sf::Font const& GetFontByKey(std::string const& key);
	static MemoryFile const& GetMemoryFileByKey(std::string const& key);

public:
	static MusicBox Musics;
	static SoundBox Sounds;

private:
	static void AddFont(std::string const& key, std::string const& fontName);
	static void AddMemoryFile(std::string const& key, std::string const& path);
	static void AddMusic(std::string const& name, MemoryFile const& mf);

	static std::unordered_map<std::string, sf::Font> Fonts;
	static std::unordered_map<std::string, MemoryFile> MemoryFiles;
};

