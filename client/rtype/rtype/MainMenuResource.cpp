#include "MainMenuResource.hpp"

const std::string MainMenuResource::MENU_RESOURCE_PATH = "./rsrc/menu/";

const std::string MainMenuResource::LOGO_R = "R.png";
const std::string MainMenuResource::LOGO_DOT = "dot.png";
const std::string MainMenuResource::LOGO_T = "T.png";
const std::string MainMenuResource::LOGO_Y = "Y.png";
const std::string MainMenuResource::LOGO_P = "P.png";
const std::string MainMenuResource::LOGO_E = "E.png";
const std::string MainMenuResource::NAV_SOUND_0 = "menu_sound0.wav";
const std::string MainMenuResource::NAV_SOUND_1 = "menu_sound1.wav";
const std::string MainMenuResource::NAV_SOUND_2 = "menu_sound2.wav";
const std::string MainMenuResource::NAV_SOUND_3 = "menu_sound3.wav";

MainMenuResource MainMenuResource::menuResourceManager;

MainMenuResource::MainMenuResource() {

}

MainMenuResource::~MainMenuResource() {
	for (auto it : _textures) {
		delete it.second;
	}
}

void MainMenuResource::load(void) {
	try {
		addTexture(LOGO_R, MENU_RESOURCE_PATH + LOGO_R);
		addTexture(LOGO_DOT, MENU_RESOURCE_PATH + LOGO_DOT);
		addTexture(LOGO_T, MENU_RESOURCE_PATH + LOGO_T);
		addTexture(LOGO_Y, MENU_RESOURCE_PATH + LOGO_Y);
		addTexture(LOGO_P, MENU_RESOURCE_PATH + LOGO_P);
		addTexture(LOGO_E, MENU_RESOURCE_PATH + LOGO_E);
		addSound(NAV_SOUND_0, MENU_RESOURCE_PATH + NAV_SOUND_0);
		addSound(NAV_SOUND_1, MENU_RESOURCE_PATH + NAV_SOUND_1);
		addSound(NAV_SOUND_2, MENU_RESOURCE_PATH + NAV_SOUND_2);
		addSound(NAV_SOUND_3, MENU_RESOURCE_PATH + NAV_SOUND_3);
	}
	catch (std::runtime_error const &) {
		throw;
	}
}

sf::Texture *MainMenuResource::getTextureByKey(std::string const &key) {
	if (_textures.find(key) != _textures.cend()) {
		return (_textures[key]);
	}
	throw std::runtime_error("Texture " + key + " not found");
}

sf::Sound *MainMenuResource::getSoundByKey(std::string const &key) {
	try {
		return _sounds.getSound(key);
	}
	catch (std::exception const &e) {
		throw std::runtime_error(e.what());
	}
}

void MainMenuResource::playSound(std::string const &key) {
	try {
		getSoundByKey(key)->play();
	}
	catch (std::runtime_error const &e) {
		std::cout << e.what() << std::endl;
	}
}

void MainMenuResource::addTexture(std::string const &key, std::string const &file) {
	sf::Texture *texture = new sf::Texture();
	if (!texture->loadFromFile(file)) {
		throw (std::runtime_error("Texture " + file + " not found"));
	}
	_textures.insert(std::make_pair(key, texture));
}

void MainMenuResource::addSound(std::string const &key, std::string const &file) {
	try {
		_sounds.addSample(key, file);
	}
	catch (std::runtime_error const &) {
		throw;
	}
}
