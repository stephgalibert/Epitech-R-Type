#include "FPSCounter.hpp"

FPSCounter::FPSCounter(void)
{
}

FPSCounter::~FPSCounter(void)
{
}

void FPSCounter::init()
{
	try {
		_text.setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}

	_text.setCharacterSize(14);
	_text.setFillColor(sf::Color::Yellow);
	_text.setString("0 FPS");
	_text.setPosition(sf::Vector2f(7, 7));
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
