#include "Background.hpp"

Background::Background(std::string const& textureName, float delayRefreshing)
	: _textureName(textureName),
	  _delayRefreshing(delayRefreshing),
	  _delta(0)
{
	//_resolution = sf::Vector2i(800, 480); // !
	std::pair<short, short> tmp = StaticTools::GetResolution();
	_resolution.x = tmp.first;
	_resolution.y = tmp.second;
}

Background::~Background(void)
{
}

void Background::init(void)
{
	try {
		_shape.setPosition(sf::Vector2f(0, 0));
		_shape.setSize(sf::Vector2f((float)_resolution.x, (float)_resolution.y));

		_texture = LevelResource::TheLevelResource.getTextureByKey(_textureName);
		_texture->setRepeated(true);

		_shape.setTexture(_texture);
		_shape.setTextureRect(sf::IntRect(0, 0, _resolution.x, _resolution.y));
	}
	catch (std::runtime_error const& e) {
		throw (e);
	}
}

void Background::update(float delta)
{
	_delta += delta;

	if (_delta > _delayRefreshing) {
		_shape.setTextureRect(sf::IntRect(_shape.getTextureRect().left
			+ (int)std::ceil(delta * 5.f), 0, _resolution.x, _resolution.y));
		_delta = 0;
	}
}

void Background::destroy(void)
{
}

void Background::draw(sf::RenderWindow &window)
{
	window.draw(_shape);
}