#include "MainMenuResource.hpp"

const std::string MainMenuResource::MENU_RESOURCE_PATH = "./rsrc/menu/";

const std::string MainMenuResource::LOGO_R = "R.png";
const std::string MainMenuResource::LOGO_DOT = "dot.png";
const std::string MainMenuResource::LOGO_T = "T.png";
const std::string MainMenuResource::LOGO_Y = "Y.png";
const std::string MainMenuResource::LOGO_P = "P.png";
const std::string MainMenuResource::LOGO_E = "E.png";

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
	}
	catch (std::runtime_error const&) {
		throw;
	}
}

sf::Texture *MainMenuResource::getTextureByKey(std::string const &key) {
	if (_textures.find(key) != _textures.cend()) {
		return (_textures[key]);
	}
	throw std::runtime_error("Texture " + key + " not found");
}

void MainMenuResource::addTexture(std::string const &key, std::string const &file) {
	sf::Texture *texture = new sf::Texture();
	if (!texture->loadFromFile(file)) {
		throw (std::runtime_error("Texture " + file + " not found"));
	}
	_textures.insert(std::make_pair(key, texture));
}