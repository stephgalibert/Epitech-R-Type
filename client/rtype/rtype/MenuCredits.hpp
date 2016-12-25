#pragma once

#include <vector>

#include "SFML/Graphics.hpp"

class MenuCredits : public sf::Drawable {
	static const uint32_t FONT_CHAR_SIZE;
	static const float LINES_SPACING;

public:
	MenuCredits();
	virtual ~MenuCredits();

public:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void init(sf::Font const *font);

public:
	void setPosition(sf::Vector2f const &position);
	void addLine(std::string const &line = " ", const uint32_t fontSize = FONT_CHAR_SIZE);

public:
	sf::Vector2f const &getPosition(void) const;

private:
	sf::Vector2f _position;
	sf::Font const *_font;
	std::vector<sf::Text> _text;
};

