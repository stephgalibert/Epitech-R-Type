#include "SplashScreen.h"

SplashScreen::SplashScreen(void)
	: _fsm(State::ST_Increase),
	  _delta(0),
	  _finished(false)
{
	_states[State::ST_None] = std::bind(&SplashScreen::st_none, this, std::placeholders::_1);
	_states[State::ST_Increase] = std::bind(&SplashScreen::st_increase, this, std::placeholders::_1);
	_states[State::ST_Fix] = std::bind(&SplashScreen::st_fix, this, std::placeholders::_1);
	_states[State::ST_Decrease] = std::bind(&SplashScreen::st_decrease, this, std::placeholders::_1);
	_states[State::ST_Finished] = std::bind(&SplashScreen::st_finished, this, std::placeholders::_1);
}

SplashScreen::~SplashScreen(void)
{
}

void SplashScreen::init(void)
{
	if (!_texture.loadFromFile("./rsrc/splashscreen/rtype_logo.jpg")) {
		throw (std::runtime_error("./rsrc/splashscreen/rtype_logo.jpg not found"));
	}
	_texture.setSmooth(true);

	_sprite.setTexture(_texture);

	sf::FloatRect rect = _sprite.getGlobalBounds();
	_rect.setSize(sf::Vector2f(rect.width - rect.left, rect.height - rect.top));
	_rect.setFillColor(sf::Color(0, 0, 0, 255));
}

void SplashScreen::update(float delta)
{
	_delta += delta;
	_states.at(_fsm)(delta);
}

void SplashScreen::draw(sf::RenderWindow &window)
{
	window.draw(_sprite);
	window.draw(_rect);
}

bool SplashScreen::isFinished(void) const
{
	return (_finished);
}

void SplashScreen::st_none(float delta)
{
	(void)delta;
}

void SplashScreen::st_increase(float delta)
{
	if (_delta < 2.f) {
		_rect.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)(255 - (_delta / 2.f * 255.f))));
	}
	else {
		_delta = 0.f;
		_fsm = State::ST_Fix;
	}
}

void SplashScreen::st_fix(float delta)
{
	if (_delta > 3.f) {
		_delta = 0.f;
		_fsm = State::ST_Decrease;
	}
}

void SplashScreen::st_decrease(float delta)
{
	if (_delta < 3.f) {
		_rect.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)(_delta / 3.f * 255.f)));
	}
	else {
		_delta = 0.f;
		_fsm = State::ST_Finished;
	}
}

void SplashScreen::st_finished(float delta)
{
	(void)delta;
	_rect.setFillColor(sf::Color(0, 0, 0, 255));
	_finished = true;
}