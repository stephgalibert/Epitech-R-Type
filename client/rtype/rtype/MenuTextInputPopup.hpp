#pragma once

#include "MenuPopup.hpp"
#include "MenuTextForm.hpp"

class MenuTextInputPopup : public MenuPopup {
	static const float LABEL_LATERAL_PADDING;
	static const float LABEL_VERTICAL_PADDING;
	static const float TEXT_FIELD_HEIGHT;
	static const uint32_t TEXT_FONT_SIZE;
	static const sf::Color LABEL_COLOR;

public:
	MenuTextInputPopup(const bool screenCover = true);
	MenuTextInputPopup(std::string const &label, std::string const &content = "", const bool screenCover = true);
	virtual ~MenuTextInputPopup();

public:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual bool input(InputHandler &input);
	virtual void updateDisplay(void);

public:
	virtual void setPosition(sf::Vector2f const &position);
	virtual void setSize(sf::Vector2f const &size);
	void resizeAndCenter(void);
	void setTextFieldContent(std::string const &field, std::string const &content);
	void clearContents(void);
	void removeFields(void);
	void addField(std::string const &name, std::string const &content = "");

public:
	std::string const &getTextFieldContent(std::string const &field) const;
	MenuTextForm const &getForm(void) const;

private:
	MenuTextForm _form;
};

