#include "MenuButton.hpp"

MenuButton::MenuButton() : _state(State::INACTIVE) {
  setFontForAllStates(NULL);
  _label.setStyle(sf::Text::Bold);
}

MenuButton::MenuButton(std::string const &label, const short id, const sf::Font *font,
	sf::Color const &color, sf::Color const &hoverColor) :
	_state(MenuButton::State::INACTIVE), _label(label, *font), _id(id) {
	_label.setStyle(sf::Text::Bold);
	setFontForAllStates(font);
	setColorForAllStates(color);
	setColorForState(hoverColor, State::HOVERED);
}

MenuButton::~MenuButton() {

}

void MenuButton::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(_label, states);
}

void MenuButton::update(void) {
  if (_stateFonts[static_cast<short>(_state)])
    _label.setFont(*_stateFonts[static_cast<short>(_state)]);
  _label.setFillColor(_stateColors[static_cast<short>(_state)]);
}

void MenuButton::setLabel(std::string const &label) {
	_label.setString(label);
}

void MenuButton::setState(const State state) {
	_state = state;
	update();
}

void MenuButton::setPosition(const float x, const float y) {
	_label.setPosition(x, y);
}

void MenuButton::setPosition(sf::Vector2f const &position) {
	_label.setPosition(position);
}

void MenuButton::setCharacterSize(const size_t size) {
	_label.setCharacterSize(size);
}

void MenuButton::setFontForState(const sf::Font *font, const State state) {
	_stateFonts[static_cast<short>(state)] = font;
	if (state == _state)
		update();
}

void MenuButton::setFontForAllStates(const sf::Font *font) {
	for (short i = 0; i < 3; i++) {
		_stateFonts[i] = font;
	}
	update();
}

void MenuButton::setColorForState(sf::Color const &color, const State state) {
	_stateColors[static_cast<short>(state)] = color;
	if (state == _state)
		update();
}

void MenuButton::setColorForAllStates(sf::Color const &color) {
	for (short i = 0; i < 3; i++) {
		_stateColors[i] = color;
	}
	update();
}

short MenuButton::getId(void) const {
	return _id;
}

MenuButton::State MenuButton::getState(void) const {
	return _state;
}

sf::Vector2f const &MenuButton::getPosition(void) const {
	return _label.getPosition();
}

sf::FloatRect MenuButton::getGlobalBounds(void) const {
	return _label.getGlobalBounds();
}
