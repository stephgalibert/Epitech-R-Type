#pragma once

#include <SFML/Graphics.hpp>

class MenuButton : public sf::Drawable {
public:
	enum class State : short {
		INACTIVE = 0,
		HOVERED = 1,
		CLICKED = 2
	};

public:
	MenuButton();
	MenuButton(std::string const &label, const short id, const sf::Font *font,
		sf::Color const &color = sf::Color::White, sf::Color const &hoverColor = sf::Color::Red);
	virtual ~MenuButton();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void update(void);

public:
	void setLabel(std::string const &text);
	void setState(const State state);
	void setPosition(const float x, const float y);
	void setPosition(sf::Vector2f const &position);
	void setCharacterSize(const size_t size);
	void setFontForState(const sf::Font *font, const State state);
	void setFontForAllStates(const sf::Font *font);
	void setColorForState(sf::Color const &color, const State state);
	void setColorForAllStates(sf::Color const &color);

public:
	short getId(void) const;
	State getState(void) const;
	sf::Vector2f const &getPosition(void) const;

private:
	State _state;
	sf::Text _label;
	short _id;

	const sf::Font *_stateFonts[3];
	sf::Color _stateColors[3];
};
