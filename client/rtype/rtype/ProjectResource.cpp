#include "ProjectResource.h"
#include <Windows.h>

CacheManager<std::string, sf::Font> ProjectResource::Fonts;
CacheManager<std::string, MemoryFile> ProjectResource::MemoryFiles;
MusicBox ProjectResource::Musics;
SoundBox ProjectResource::Sounds;

void ProjectResource::Load(void)
{
	try {
		AddFont("main", "./rsrc/font/pixelmix.ttf");
		AddMemoryFile("main_theme", "rsrc/music/main_theme.wav");

		Musics.addSample("main_theme", MemoryFiles["main_theme"]);
	}
	catch (std::runtime_error const& e) {
		throw (e);
	}
}

sf::Font const& ProjectResource::GetFontByKey(std::string const& key)
{
	if (Fonts.find(key)) {
		return (Fonts.at(key));
	}
	throw std::runtime_error("Fonts '" + key + "' not found");
}

MemoryFile const& ProjectResource::GetMemoryFileByKey(std::string const& key)
{
	if (MemoryFiles.find(key)) {
		return (MemoryFiles.at(key));
	}

	throw std::runtime_error("Memory file '" + key + "' not found");
}

void ProjectResource::AddFont(std::string const& key, std::string const& fontName)
{
	sf::Font font;
	if (!font.loadFromFile(fontName)) {
		throw (std::runtime_error(fontName));
	}
	Fonts.insert(key, font);
}

void ProjectResource::AddMemoryFile(std::string const& key, std::string const& path)
{
	MemoryFiles[key].filename = path;
	try {
		MemoryFiles[key].load();
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

void ProjectResource::AddMusic(std::string const& name, MemoryFile const& mf)
{
	try {
		Musics.addSample(name, mf);
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}