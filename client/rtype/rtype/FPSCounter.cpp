#include "FPSCounter.h"

FPSCounter::FPSCounter(void)
{
}

FPSCounter::~FPSCounter(void)
{
}

void FPSCounter::init(void)
{
	if (!_font.loadFromFile("./rsrc/font/pixelmix.ttf")) {
		throw (std::runtime_error("./rsrc/font/pixelmix.ttf not found"));
	}
	_text.setFont(_font);
	_text.setCharacterSize(16);
	_text.setFillColor(sf::Color::Yellow);
	_text.setString("0 FPS");
	_text.setPosition(sf::Vector2f(10, 10));
}

void FPSCounter::update(float delta)
{
	_delta += delta;
	if (_delta > 1.f) {
		_text.setString(std::to_string((int)(1 / delta)) + " FPS");
		_delta = 0;
	}
}

void FPSCounter::draw(sf::RenderWindow &window)
{
	window.draw(_text);
}