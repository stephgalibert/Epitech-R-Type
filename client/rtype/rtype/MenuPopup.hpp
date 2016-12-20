#pragma once

#include "SFML/Graphics.hpp"

#include "InputHandler.hpp"

class MenuPopup : sf::Drawable {
	static const float FRAME_OUTLINE_THICKNESS;
	static const sf::Color BACKGROUND_COLOR;
	static const sf::Color SCREEN_COVER_COLOR;

public:
	MenuPopup(const bool screenCover = true);
	virtual ~MenuPopup();

public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual bool input(InputHandler &input);

public:
	virtual void setPosition(sf::Vector2f const &position);
	virtual void setSize(sf::Vector2f const &size);
	void setScreenCover(const bool screenCover);

public:
	sf::Vector2f const &getPosition(void) const;
	sf::Vector2f const &getSize(void) const;
	bool isScreenCoverOn(void) const;

protected:
	sf::RectangleShape _frame;

private:
	bool _screenCoverOn;
};

