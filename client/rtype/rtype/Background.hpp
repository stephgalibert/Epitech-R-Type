#pragma once

#include "ADrawable.hpp"
#include "LevelResource.hpp"
#include "StaticTools.hpp"

class Background
{
public:
	Background(std::string const& textureName, float delayRefreshing);
	virtual ~Background(void);

	void init(void);
	void update(float delta);
	void destroy(void);
	void draw(sf::RenderWindow &window);

private:
	std::string _textureName;
	float _delayRefreshing;
	float _delta;

	sf::Vector2i _resolution;
	sf::Texture *_texture;
	sf::RectangleShape _shape;
};

