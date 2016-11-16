#pragma once

#include <functional>
#include <unordered_map>

#include <SFML/Graphics.hpp>

class InputHandler
{
public:
	InputHandler(void);
	virtual ~InputHandler(void);

	virtual void OnEvent(sf::Event const& e);

	bool isKeyDown(sf::Keyboard::Key key) const;
	bool isMouseButtonDown(sf::Mouse::Button button) const;
	bool isTextEntered(void) const;

	char popTextEntered(void);
	bool isExiting(void) const;

private:
	void keyPressed(sf::Event const& e);
	void keyReleased(sf::Event const& e);
	void mouseButtonPressed(sf::Event const& e);
	void mouseButtonReleased(sf::Event const& e);
	void textEntered(sf::Event const& e);
	void exit(sf::Event const& e);
	std::unordered_map<sf::Event::EventType, std::function<void(sf::Event const&)> > _events;

	bool _mouse[sf::Mouse::ButtonCount];
	bool _keys[sf::Keyboard::KeyCount];

	char _textEntered;
	bool _exit;
};

