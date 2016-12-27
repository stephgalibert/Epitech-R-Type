#include <iostream>

#include "ProjectResource.hpp"

#include "MenuTextInputPopup.hpp"

const float MenuTextInputPopup::LABEL_LATERAL_PADDING = 10.f;
const float MenuTextInputPopup::LABEL_VERTICAL_PADDING = 12.f;
const float MenuTextInputPopup::TEXT_FIELD_HEIGHT = 45.f;
const uint32_t MenuTextInputPopup::TEXT_FONT_SIZE = 16u;
const sf::Color MenuTextInputPopup::LABEL_COLOR = sf::Color::White;

MenuTextInputPopup::MenuTextInputPopup(const bool screenCover) : MenuPopup(screenCover) {
	_form.setSize(getSize());
}

MenuTextInputPopup::MenuTextInputPopup(std::string const &label, std::string const &content, const bool screenCover) : MenuTextInputPopup(screenCover) {
	addField(label, content);
}

MenuTextInputPopup::~MenuTextInputPopup() {

}

void MenuTextInputPopup::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	MenuPopup::draw(target, states);
	target.draw(_form, states);
}

bool MenuTextInputPopup::input(InputHandler &input) {
	return _form.input(input);
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
	_form.setPosition(position);
}

void MenuTextInputPopup::setSize(sf::Vector2f const &size) {
	MenuPopup::setSize(size);
	_form.setSize(size);
}

void MenuTextInputPopup::resizeAndCenter(void) {
	_form.setSize(sf::Vector2f(getSize().x, _form.getIdealHeight()));
	setSize(sf::Vector2f(getSize().x, _form.getSize().y));
	centerOnScreen();
}

void MenuTextInputPopup::setTextFieldContent(std::string const &field, std::string const &content) {
	_form.setFieldContent(field, content);
}

void MenuTextInputPopup::clearContents(void) {
	_form.clearFieldsContent();
}

void MenuTextInputPopup::removeFields(void) {
	_form.removeFields();
}

void MenuTextInputPopup::addField(std::string const &name, std::string const &content) {
	_form.addField(name, content);
}

std::string const &MenuTextInputPopup::getTextFieldContent(std::string const &field) const {
	return _form.getFieldContent(field);
}

MenuTextForm const &MenuTextInputPopup::getForm(void) const {
	return _form;
}
