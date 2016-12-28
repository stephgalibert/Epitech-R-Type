#include "MenuOptions.hpp"

#include "MainMenuResource.hpp"

const std::string MenuOptions::FORM_HOST_FIELD = "Host IP";
const std::string MenuOptions::FORM_PORT_FIELD = "Port";

MenuOptions::MenuOptions() {
	
}

MenuOptions::~MenuOptions() {
	
}

void MenuOptions::init(void) {
	_form.addField(FORM_HOST_FIELD);
	_form.addField(FORM_PORT_FIELD);
	_form.setSize(sf::Vector2f(_form.getSize().x, _form.getIdealHeight()));
}

bool MenuOptions::input(InputHandler &input) {
	return _form.input(input);
}

void MenuOptions::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(_form);
}

std::string const &MenuOptions::getHost(void) const {
	return _form.getFieldContent(FORM_HOST_FIELD);
}

std::string const &MenuOptions::getPort(void) const {
	return _form.getFieldContent(FORM_PORT_FIELD);
}

MenuTextForm const &MenuOptions::getForm(void) const {
	return _form;
}

void MenuOptions::setPosition(sf::Vector2f const &position) {
	_form.setPosition(position);
}

void MenuOptions::setWidth(const float width) {
	_form.setSize(sf::Vector2f(width, _form.getSize().y));
}

void MenuOptions::setHost(std::string const &host) {
	_form.setFieldContent(FORM_HOST_FIELD, host);
}

void MenuOptions::setPort(std::string const &port) {
	_form.setFieldContent(FORM_PORT_FIELD, port);
}
