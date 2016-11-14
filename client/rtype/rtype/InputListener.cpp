#include "InputListener.hpp"

InputListener::InputListener(void)
{
	_events[sf::Event::EventType::KeyPressed] = std::bind(&InputListener::keyPressed, this, std::placeholders::_1);
	_events[sf::Event::EventType::KeyReleased] = std::bind(&InputListener::keyReleased, this, std::placeholders::_1);
	_events[sf::Event::EventType::MouseButtonPressed] = std::bind(&InputListener::mouseButtonPressed, this, std::placeholders::_1);
	_events[sf::Event::EventType::MouseButtonReleased] = std::bind(&InputListener::mouseButtonReleased, this, std::placeholders::_1);
	_events[sf::Event::EventType::TextEntered] = std::bind(&InputListener::textEntered, this, std::placeholders::_1);
	_events[sf::Event::EventType::Closed] = std::bind(&InputListener::exit, this, std::placeholders::_1);

	for (size_t i = 0; i < sf::Mouse::ButtonCount; ++i)
		_mouse[i] = false;
	for (size_t i = 0; i < sf::Keyboard::KeyCount; ++i)
		_keys[i] = false;
	_textEntered = 0;
	_exit = false;
}

InputListener::~InputListener(void)
{

}

void InputListener::OnEvent(sf::Event const& e)
{
	popTextEntered();
	if (_events.find(e.type) != _events.cend())
		_events.at(e.type)(e);
}

bool InputListener::isKeyDown(sf::Keyboard::Key key) const
{
	return (_keys[key]);
}

bool InputListener::isMouseButtonDown(sf::Mouse::Button button) const
{
	return (_mouse[button]);
}

bool InputListener::isTextEntered(void) const
{
	return (_textEntered != 0);
}

char InputListener::popTextEntered(void)
{
	char tmp = _textEntered;
	_textEntered = 0;
	return (tmp);
}

bool InputListener::isExiting(void) const
{
	return (_exit);
}

void InputListener::keyPressed(sf::Event const& e)
{
	_keys[e.key.code] = true; 
}

void InputListener::keyReleased(sf::Event const& e)
{
	_keys[e.key.code] = false;
}

void InputListener::mouseButtonPressed(sf::Event const& e)
{
	_mouse[e.mouseButton.button] = true;
}

void InputListener::mouseButtonReleased(sf::Event const& e)
{
	_mouse[e.mouseButton.button] = false;
}

void InputListener::textEntered(sf::Event const& e)
{
	_textEntered = static_cast<char>(e.text.unicode);
}

void InputListener::exit(sf::Event const& e)
{
	(void)e;
	_exit = true;
}