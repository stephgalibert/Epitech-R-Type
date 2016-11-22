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

	sf::Vector2i resolution = StaticTools::GetResolution();
	sf::RectangleShape *shape = new sf::RectangleShape;

	shape->setPosition(sf::Vector2f(0, 0));
	shape->setSize(sf::Vector2f((float)resolution.x, (float)resolution.y));

	setShape(shape);
	setTexture(ProjectResource::TheProjectResource.getTextureByKey("background"));

	getTexture()->setRepeated(true);
	getShape()->setTextureRect(sf::IntRect(0, 400, 1920, 1080));

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
		getShape()->setTextureRect(sf::IntRect(getShape()->getTextureRect().left + (int)std::ceil(delta * 5.f), 400, 1920, 1080));
	
		_delta = 0;
	}
}