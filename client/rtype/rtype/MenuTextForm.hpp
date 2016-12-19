#pragma once

#include "SFML/Graphics.hpp"

#include "InputHandler.hpp"
#include "MenuTextField.hpp"

class MenuTextForm : public sf::Drawable {
	static const float FRAME_OUTILINE_THICKNESS;
	static const sf::Color DEFAULT_BACKGROUND_COLOR;
	static const sf::Color DEFAULT_TEXT_COLOR;
	static const sf::Color INACTIVE_COVER_COLOR;
	static const uint32_t LABEL_FONT_CHAR_SIZE;
	static const float FORM_LATERAL_PADDING;
	static const float FORM_VERTICAL_PADDING;
	static const float TEXT_FIELD_HEIGHT;

public:
	MenuTextForm();
	virtual ~MenuTextForm();

public:
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	bool input(InputHandler &input);

public:
	void setSize(sf::Vector2f const &size);
	void setPosition(sf::Vector2f const &position);
	void addField(std::string const &name, std::string const &content = "");
	void setFieldContent(std::string const &fieldName, std::string const &content);
	void clearFieldsContent(void);
	void removeFields(void);

public:
	sf::Vector2f const &getSize(void) const;
	sf::Vector2f const &getPosition(void) const;
	float getIdealHeight(void) const;
	uint32_t getFieldCount(void) const;
	std::string const &getFieldContent(std::string const &fieldName) const;
	MenuTextField const &getField(std::string const &fieldName) const;
	uint32_t getDrawnFieldsMax(void) const;

private:
	MenuTextField &getField(std::string const &fieldName);
	void updateLayout(void);

private:
	uint32_t _focusedField;

private:
	sf::RectangleShape _frame;
	std::vector<std::pair<std::string, MenuTextField>> _fields;
};

