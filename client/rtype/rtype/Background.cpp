#include "Background.hpp"

Background::Background(void)
	: _delta(0),
	  _fsm(State::ST_FadeIn)
{
	_states[State::ST_None] = std::bind(&Background::st_none, this, std::placeholders::_1);
	_states[State::ST_FadeIn] = std::bind(&Background::st_fadeIn, this, std::placeholders::_1);
	_states[State::ST_Parallax] = std::bind(&Background::st_parallax, this, std::placeholders::_1);
}

Background::~Background(void)
{
}

void Background::init(void)
{
	//_fader = new Fader(Fader::FadeIn);

	_resolution = StaticTools::GetResolution();

	_shape1.setPosition(sf::Vector2f(0, 0));
	_shape1.setSize(sf::Vector2f((float)_resolution.x, (float)_resolution.y));

	_shape2.setPosition(sf::Vector2f(0, 0));
	_shape2.setSize(sf::Vector2f((float)_resolution.x, (float)_resolution.y));

	_texture1 = LevelResource::TheLevelResource.getTextureByKey("background");
	_texture2 = LevelResource::TheLevelResource.getTextureByKey("background2");

	_texture1->setRepeated(true);
	_texture2->setRepeated(true);

	_shape1.setTexture(_texture1);
	_shape2.setTexture(_texture2);
	_shape1.setTextureRect(sf::IntRect(0, 0, _resolution.x, _resolution.y));
	_shape2.setTextureRect(sf::IntRect(0, 0, _resolution.x, _resolution.y));

	_fsm = State::ST_Parallax;
}

void Background::update(float delta)
{
	_delta += delta;
	switch (_fsm)
	{
	case State::ST_FadeIn:
		st_fadeIn(delta);
		break;
	case State::ST_Parallax:
		st_parallax(delta);
		break;
	}
}

void Background::destroy(void)
{
}

void Background::draw(sf::RenderWindow &window)
{
	window.draw(_shape1);
	window.draw(_shape2);
}

void Background::st_none(float delta)
{
	(void)delta;
}

void Background::st_fadeIn(float delta)
{
	//_rect.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)(255 - (delta / 1.f * 255.f))));
}

void Background::st_parallax(float delta)
{
	if (_delta > 0.03) {
		_shape1.setTextureRect(sf::IntRect(_shape1.getTextureRect().left
			+ (int)std::ceil(delta * 5.f), 0, _resolution.x, _resolution.y));
		_delta = 0;
	}
	if (delta > 0.01) {
		_shape2.setTextureRect(sf::IntRect(_shape2.getTextureRect().left
			+ (int)std::ceil(delta * 5.f), 0, _resolution.x, _resolution.y));
	}
}