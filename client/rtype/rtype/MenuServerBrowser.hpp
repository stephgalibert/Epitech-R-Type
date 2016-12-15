#pragma once

#include <SFML/Graphics.hpp>

#include "InputHandler.hpp"

class MenuServerBrowser : public sf::Drawable {
	static const float FRAME_OUTLINE_THICKNESS;
	static const sf::Color ITEM_BASE_COLOR;
	static const sf::Color ITEM_SECOND_COLOR;
	static const float ITEMS_SPACING;
	static const float ITEMS_HEIGHT;
	static const uint32_t FONT_CHAR_SIZE;
	static const float TEXT_TOP_PADDING;
	static const float TEXT_LEFT_PADDING;

public:
	MenuServerBrowser();
	virtual ~MenuServerBrowser();

public:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool input(InputHandler &input);

public:
	void setSize(sf::Vector2f const &size);
	void setPosition(sf::Vector2f const &pos);
	void clearContent(void);
	void setContent(std::vector<std::string> const &content);
	void setSelected(const int index);

public:
	sf::Vector2f const &getSize(void) const;
	sf::Vector2f const &getPosition(void) const;
	std::vector<std::string> const &getContent(void) const;
	int getSelected(void) const;
	size_t getDisplayedItemsMax(void) const;
	size_t getDisplayedItemsCount(void) const;

public:
	static float getHeightForItems(const size_t items);

private:
	std::vector<std::string> _content;
	int _selected;

private:
	sf::RectangleShape _frame;
};

