#include "FPSCounter.hpp"

FPSCounter::FPSCounter(void)
{
	_resolution = StaticTools::GetResolution();
	_delta = 0;
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

	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_text.setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f));

	_text.setOrigin(textRect.width, 0);
	_text.setPosition(sf::Vector2f(_resolution.first - 17.f, 7.f));
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
