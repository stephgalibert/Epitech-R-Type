#pragma once

#include <functional>
#include <unordered_map>

#include <SFML/Graphics.hpp>

class InputHandler
{
public:
	static const int JOYSTICK_DEAD_ZONE = 20;

public:
	InputHandler(void);
	virtual ~InputHandler(void);

	virtual void init(void);
	virtual void OnEvent(sf::Event const& e);

	bool isKeyDown(sf::Keyboard::Key key) const;
	bool isMouseButtonDown(sf::Mouse::Button button) const;
	bool isJoystickButtonDown(unsigned int button) const;
	bool isJoystickPresent(void) const;
	bool isTextEntered(void) const;

	float getJoystickAxis(unsigned int id, sf::Joystick::Axis axis);
	char popTextEntered(void);
	bool isExiting(void) const;

private:
	void keyPressed(sf::Event const& e);
	void keyReleased(sf::Event const& e);
	void mouseButtonPressed(sf::Event const& e);
	void mouseButtonReleased(sf::Event const& e);
	void joystickButtonPressed(sf::Event const& e);
	void joystickButtonReleased(sf::Event const& e);
	void joystickConnected(sf::Event const& e);
	void joystickDisconnected(sf::Event const& e);
	void textEntered(sf::Event const& e);
	void exit(sf::Event const& e);
	std::unordered_map<int, std::function<void(sf::Event const&)> > _events;

	bool _mouse[sf::Mouse::ButtonCount];
	bool _keys[sf::Keyboard::KeyCount];
	bool _joystickButtons[sf::Joystick::ButtonCount];
	bool _joystickPresent;

	char _textEntered;
	bool _exit;
};

