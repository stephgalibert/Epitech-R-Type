#include <iostream>

#include "ProjectResource.hpp"

#include "MenuTextInputPopup.hpp"

const float MenuTextInputPopup::LABEL_LATERAL_PADDING = 10.f;
const float MenuTextInputPopup::LABEL_VERTICAL_PADDING = 12.f;
const float MenuTextInputPopup::TEXT_FIELD_HEIGHT = 45.f;
const uint32_t MenuTextInputPopup::TEXT_FONT_SIZE = 16u;
const sf::Color MenuTextInputPopup::LABEL_COLOR = sf::Color::White;

MenuTextInputPopup::MenuTextInputPopup(const bool screenCover) : MenuPopup(screenCover) {
	_label.setCharacterSize(TEXT_FONT_SIZE);
	_label.setFillColor(LABEL_COLOR);
}

MenuTextInputPopup::MenuTextInputPopup(std::string const &label, std::string const &content, const bool screenCover) : MenuTextInputPopup(screenCover) {
	_label.setString(label);
	_textField.setContent(content);
}

MenuTextInputPopup::~MenuTextInputPopup() {

}

void MenuTextInputPopup::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	MenuPopup::draw(target, states);
	target.draw(_label, states);
	target.draw(_textField, states);
}

bool MenuTextInputPopup::input(InputHandler &input) {
	return _textField.input(input);
}

void MenuTextInputPopup::updateDisplay(void) {
	try {
		setSize(getSize());
		setPosition(getPosition());
	}
	catch (std::exception const &) {

	}
}

void MenuTextInputPopup::setPosition(sf::Vector2f const &position) {
	MenuPopup::setPosition(position);
	_label.setPosition(sf::Vector2f(getPosition().x + LABEL_LATERAL_PADDING, getPosition().y + LABEL_VERTICAL_PADDING));
	_textField.setPosition(sf::Vector2f(_label.getPosition().x, _label.getPosition().y + _label.getGlobalBounds().height + LABEL_VERTICAL_PADDING * 2));
}

void MenuTextInputPopup::setSize(sf::Vector2f const &size) {
	MenuPopup::setSize(size);
	_textField.setSize(sf::Vector2f(size.x - (2 * LABEL_LATERAL_PADDING), TEXT_FIELD_HEIGHT));
}

void MenuTextInputPopup::setLabel(std::string const &label) {
	_label.setString(label);
	updateDisplay();
}

void MenuTextInputPopup::setTextFieldContent(std::string const &content) {
	_textField.setContent(content);
}

void MenuTextInputPopup::clearTextFieldContent(void) {
	_textField.clear();
}

void MenuTextInputPopup::setFont(sf::Font const *font) {
	_label.setFont(*font);
	updateDisplay();
}

std::string const &MenuTextInputPopup::getTextFieldContent(void) const {
	return _textField.getContent();
}
