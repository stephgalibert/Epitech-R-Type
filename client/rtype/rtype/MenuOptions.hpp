#pragma once

#include "SFML/Graphics.hpp"

#include "MenuTextForm.hpp"
#include "MenuSlider.hpp"

class MenuOptions : public sf::Drawable {
	static const std::string FORM_HOST_FIELD;
	static const std::string FORM_PORT_FIELD;
	static const float SLIDER_HEIGHT;
	static const float ELEMENTS_PADDING;
	static const sf::Color SLIDER_FOCUSED_COLOR;
	static const sf::Color SLIDER_INACTIVE_COLOR;

public:
	MenuOptions();
	virtual ~MenuOptions();

public:
	void init(sf::Font *font);
	bool input(InputHandler &input);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
	std::string const &getHost(void) const;
	std::string const &getPort(void) const;
	MenuTextForm const &getForm(void) const;
	float getSoundValue(void) const;
	float getMusicValue(void) const;
	uint8_t getFocusedItem(void) const;

public:
	void setPosition(sf::Vector2f const &position);
	void setWidth(const float width);
	void setHost(std::string const &host);
	void setPort(std::string const &port);
	void setSoundValue(const float value);
	void setMusicValue(const float value);
	void resetFocus(void);

public:
	enum FocusedItem : uint8_t {
		FORM = 0,
		SOUND_SLIDER = 1,
		MUSIC_SLIDER = 2
	};

private:
	sf::Font *_font;
	FocusedItem _focusedItem;
	MenuTextForm _form;
	MenuSlider _soundSlider;
	MenuSlider _musicSlider;
};

