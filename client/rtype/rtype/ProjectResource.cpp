#include "ProjectResource.hpp"

const std::string ProjectResource::MAIN_FONT = "main_font";
const std::string ProjectResource::MAIN_THEME = "main_theme";

ProjectResource::ProjectResource(void)
{
}

ProjectResource::~ProjectResource(void)
{
}

void ProjectResource::load(void)
{
	try {
		addFont(MAIN_FONT, "./rsrc/font/pixelmix.ttf");
		addMusic(MAIN_THEME, "rsrc/music/main_theme.wav");
	}
	catch (std::runtime_error const& e) {
		throw (e);
	}
}

sf::Font const& ProjectResource::getFontByKey(std::string const& key) const
{
	if (_fonts.find(key)) {
		return (_fonts.at(key));
	}
	throw std::runtime_error("Fonts '" + key + "' not found");
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


/*CacheManager<std::string, sf::Font> ProjectResource::Fonts;
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
}*/