#pragma once

#include "SFML\Graphics.hpp"

#include "InputHandler.hpp"

class MenuTextField : public sf::Drawable {
	static const float FRAME_OUTILINE_THICKNESS;
	static const sf::Color DEFAULT_BACKFROUND_COLOR;
	static const sf::Color DEFAULT_TEXT_COLOR;
	static const uint32_t FONT_CHAR_SIZE;
	static const float TEXT_TOP_PADDING;
	static const float TEXT_LEFT_PADDING;
	static const float CURSOR_BAR_WIDTH;

public:
	MenuTextField();
	MenuTextField(sf::Vector2f const &position, sf::Vector2f const &size, const uint32_t fontSize = FONT_CHAR_SIZE);
	virtual ~MenuTextField();

public:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool input(InputHandler &input);

public:
	void setSize(sf::Vector2f const &size);
	void setPosition(sf::Vector2f const &position);
	void setFontSize(const uint32_t fontSize);
	void setContent(std::string const &content);
	void clear(void);
	void cursorForward(void);
	void cursorBack(void);
	void setCursorPos(const uint32_t pos);
	void setCursorVisiblity(const bool visible);

public:
	sf::Vector2f const &getSize(void) const;
	sf::Vector2f const &getPosition(void) const;
	uint32_t getFontSize(void) const;
	std::string const &getContent(void) const;
	uint32_t getDisplayedLettersMax(void) const;
	bool isCursorVisible(void) const;

private:
	bool handleTextInput(InputHandler &input);
	void updateTextDisplay(void);

private:
	std::string _content;
	uint32_t _cursor;
	uint32_t _textDisplayOffset;
	bool _cursorVisible;

private:
	sf::RectangleShape _frame;
	sf::RectangleShape _cursorBar;
	sf::Text _text;
};

