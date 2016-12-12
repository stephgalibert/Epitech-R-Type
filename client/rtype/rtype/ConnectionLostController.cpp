#include "ConnectionLostController.hpp"

ConnectionLostController::ConnectionLostController(void)
{
	_delta = 0;
	_resolution = StaticTools::GetResolution();
}

ConnectionLostController::~ConnectionLostController(void)
{
}


void ConnectionLostController::init(void)
{
	try {
		_text.setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));

		setTextSize(22);
		setTextColor(sf::Color::Red);
		setText(_string);
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

bool ConnectionLostController::input(InputHandler &input)
{
	(void)input;
	return (false);
}

void ConnectionLostController::update(float delta)
{
	(void)delta;
	//_delta += delta;

	//if (_delta > 1.f) {
	//	_delta = 0;
	//}
}

void ConnectionLostController::draw(sf::RenderWindow &window)
{
	window.draw(_text);
}

void ConnectionLostController::recycle(void)
{
}

void ConnectionLostController::setTextColor(sf::Color const& color)
{
	_text.setFillColor(color);
}

void ConnectionLostController::setTextSize(size_t size)
{
	_text.setCharacterSize(size);
	updateTextSize();
}

void ConnectionLostController::setText(std::string const& text)
{
	_text.setString(text);
	updateTextSize();
}

void ConnectionLostController::setBaseText(std::string const& text)
{
	_string = text;
	_text.setString(_string);
	updateTextSize();
}

void ConnectionLostController::updateTextSize(void)
{
	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_text.setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f));
}
