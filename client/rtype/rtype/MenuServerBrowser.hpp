#pragma once

#include <SFML/Graphics.hpp>

#include "Protocol.hpp"
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
	static const std::string EMPTY_MESSAGE;

public:
	struct PartyData {
		std::string name;
		uint8_t playersCount;
		bool hasPassword;
		bool running;
	};

public:
	MenuServerBrowser();
	virtual ~MenuServerBrowser();

public:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool input(InputHandler &input);

public:
	void setSize(sf::Vector2f const &size);
	void setPosition(sf::Vector2f const &pos);
	void setFont(sf::Font const *font);
	void clearContent(void);
	void setContent(std::vector<PartyData> const &content);
	void setSelected(const int index);
	void addEntry(PartyData const &entry);
	void addEntry(GetParty const &entry);

public:
	sf::Vector2f const &getSize(void) const;
	sf::Vector2f const &getPosition(void) const;
	std::vector<PartyData> const &getContent(void) const;
	int getSelected(void) const;
	size_t getDisplayedItemsMax(void) const;
	size_t getDisplayedItemsCount(void) const;

public:
	static float getHeightForItems(const size_t items);

private:
	std::vector<PartyData> _content;
	int _selected;

private:
	sf::Font const *_font;
	sf::RectangleShape _frame;
	sf::Text _emptyMessage;
};

