#include "InputHandler.hpp"

InputHandler::InputHandler(void)
{
	_events[sf::Event::EventType::KeyPressed] = std::bind(&InputHandler::keyPressed, this, std::placeholders::_1);
	_events[sf::Event::EventType::KeyReleased] = std::bind(&InputHandler::keyReleased, this, std::placeholders::_1);
	_events[sf::Event::EventType::MouseButtonPressed] = std::bind(&InputHandler::mouseButtonPressed, this, std::placeholders::_1);
	_events[sf::Event::EventType::MouseButtonReleased] = std::bind(&InputHandler::mouseButtonReleased, this, std::placeholders::_1);
	_events[sf::Event::EventType::TextEntered] = std::bind(&InputHandler::textEntered, this, std::placeholders::_1);
	_events[sf::Event::EventType::Closed] = std::bind(&InputHandler::exit, this, std::placeholders::_1);

	for (size_t i = 0; i < sf::Mouse::ButtonCount; ++i)
		_mouse[i] = false;
	for (size_t i = 0; i < sf::Keyboard::KeyCount; ++i)
		_keys[i] = false;
	_textEntered = 0;
	_exit = false;
}

InputHandler::~InputHandler(void)
{

}

void InputHandler::OnEvent(sf::Event const& e)
{
	popTextEntered();
	if (_events.find(e.type) != _events.cend())
		_events.at(e.type)(e);
}

bool InputHandler::isKeyDown(sf::Keyboard::Key key) const
{
	return (_keys[key]);
}

bool InputHandler::isMouseButtonDown(sf::Mouse::Button button) const
{
	return (_mouse[button]);
}

bool InputHandler::isTextEntered(void) const
{
	return (_textEntered != 0);
}

char InputHandler::popTextEntered(void)
{
	char tmp = _textEntered;
	_textEntered = 0;
	return (tmp);
}

bool InputHandler::isExiting(void) const
{
	return (_exit);
}

void InputHandler::keyPressed(sf::Event const& e)
{
	_keys[e.key.code] = true; 
}

void InputHandler::keyReleased(sf::Event const& e)
{
	_keys[e.key.code] = false;
}

void InputHandler::mouseButtonPressed(sf::Event const& e)
{
	_mouse[e.mouseButton.button] = true;
}

void InputHandler::mouseButtonReleased(sf::Event const& e)
{
	_mouse[e.mouseButton.button] = false;
}

void InputHandler::textEntered(sf::Event const& e)
{
	_textEntered = static_cast<char>(e.text.unicode);
}

void InputHandler::exit(sf::Event const& e)
{
	(void)e;
	_exit = true;
}