#include "InputHandler.hpp"

InputHandler::InputHandler(void)
{
  _events[(int)sf::Event::EventType::KeyPressed] = std::bind(&InputHandler::keyPressed, this, std::placeholders::_1);
  _events[(int)sf::Event::EventType::KeyReleased] = std::bind(&InputHandler::keyReleased, this, std::placeholders::_1);
  _events[(int)sf::Event::EventType::MouseButtonPressed] = std::bind(&InputHandler::mouseButtonPressed, this, std::placeholders::_1);
  _events[(int)sf::Event::EventType::MouseButtonReleased] = std::bind(&InputHandler::mouseButtonReleased, this, std::placeholders::_1);
  _events[(int)sf::Event::EventType::JoystickButtonPressed] = std::bind(&InputHandler::joystickButtonPressed, this, std::placeholders::_1);
  _events[(int)sf::Event::EventType::JoystickButtonReleased] = std::bind(&InputHandler::joystickButtonReleased, this, std::placeholders::_1);
  _events[(int)sf::Event::EventType::JoystickConnected] = std::bind(&InputHandler::joystickConnected, this, std::placeholders::_1);
  _events[(int)sf::Event::EventType::JoystickDisconnected] = std::bind(&InputHandler::joystickDisconnected, this, std::placeholders::_1);
  _events[(int)sf::Event::EventType::TextEntered] = std::bind(&InputHandler::textEntered, this, std::placeholders::_1);
  _events[(int)sf::Event::EventType::Closed] = std::bind(&InputHandler::exit, this, std::placeholders::_1);

	for (size_t i = 0; i < sf::Mouse::ButtonCount; ++i) {
		_mouse[i] = false;
	}
	for (size_t i = 0; i < sf::Keyboard::KeyCount; ++i) {
		_keys[i] = false;
	}
	for (size_t i = 0; i < sf::Joystick::ButtonCount; ++i) {
		_joystickButtons[i] = false;
	}
	_joystickPresent = false;
	_textEntered = 0;
	_exit = false;
}

InputHandler::~InputHandler(void)
{

}

void InputHandler::init(void)
{
	_joystickPresent = sf::Joystick::isConnected(0);
}

void InputHandler::OnEvent(sf::Event const& e)
{
	popTextEntered();
	if (_events.find((int)e.type) != _events.cend())
	  _events.at((int)e.type)(e);
}

bool InputHandler::isKeyDown(sf::Keyboard::Key key) const
{
	return (_keys[key]);
}

bool InputHandler::isMouseButtonDown(sf::Mouse::Button button) const
{
	return (_mouse[button]);
}

bool InputHandler::isJoystickButtonDown(unsigned int button) const
{
	return (_joystickButtons[button]);
}

bool InputHandler::isJoystickPresent(void) const
{
	return (_joystickPresent);
}

float InputHandler::getJoystickAxis(unsigned int id, sf::Joystick::Axis axis) const
{
	return (sf::Joystick::getAxisPosition(id, axis));
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

bool InputHandler::isJoystickDown(void) const {
	return isJoystickPresent() && getJoystickAxis(0, sf::Joystick::Y) < -JOYSTICK_DEAD_ZONE;
}

bool InputHandler::isJoystickUp(void) const {
	return isJoystickPresent() && getJoystickAxis(0, sf::Joystick::Y) > JOYSTICK_DEAD_ZONE;
}

bool InputHandler::isJoystickLeft(void) const {
	return isJoystickPresent() && getJoystickAxis(0, sf::Joystick::X) < -JOYSTICK_DEAD_ZONE;
}

bool InputHandler::isJoystickRight(void) const {
	return isJoystickPresent() && getJoystickAxis(0, sf::Joystick::X) > JOYSTICK_DEAD_ZONE;
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

void InputHandler::joystickButtonPressed(sf::Event const& e)
{
	_joystickButtons[e.joystickButton.button] = true;
}

void InputHandler::joystickButtonReleased(sf::Event const& e)
{
	_joystickButtons[e.joystickButton.button] = false;
}

void InputHandler::joystickConnected(sf::Event const& e)
{
  (void)e;
	_joystickPresent = true;
}

void InputHandler::joystickDisconnected(sf::Event const& e)
{
  (void)e;
	_joystickPresent = false;
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
