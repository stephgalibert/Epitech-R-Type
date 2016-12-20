#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "IResourceManager.hpp"

#include "MusicBox.hpp"

class MainMenuResource : public IResourceManager {
public:
	static const std::string MENU_RESOURCE_PATH;
	static const std::string LOGO_R;
	static const std::string LOGO_DOT;
	static const std::string LOGO_T;
	static const std::string LOGO_Y;
	static const std::string LOGO_P;
	static const std::string LOGO_E;
	static MainMenuResource menuResourceManager;

public:
	MainMenuResource(void);
	virtual ~MainMenuResource(void);

public:
	virtual void load(void);
	sf::Texture *getTextureByKey(std::string const &key);

private:
	void addTexture(std::string const &key, std::string const &file);

private:
	std::map<std::string, sf::Texture *> _textures;
};

