#include "StaticTools.hpp"

#include "MenuPopup.hpp"

const float MenuPopup::FRAME_OUTLINE_THICKNESS = 2.f;
const sf::Color MenuPopup::BACKGROUND_COLOR = sf::Color::Black;
const sf::Color MenuPopup::SCREEN_COVER_COLOR = sf::Color(0, 0, 0, 120);

MenuPopup::MenuPopup(const bool screenCover) : _screenCoverOn(screenCover) {
	_frame.setFillColor(BACKGROUND_COLOR);
	_frame.setOutlineThickness(FRAME_OUTLINE_THICKNESS);
}

MenuPopup::~MenuPopup() {
}

void MenuPopup::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (_screenCoverOn) {
		sf::RectangleShape screenCover;

		screenCover.setFillColor(SCREEN_COVER_COLOR);
		screenCover.setPosition(sf::Vector2f(0.f, 0.f));
		screenCover.setSize(sf::Vector2f(static_cast<float>(target.getSize().x), static_cast<float>(target.getSize().y)));
		target.draw(screenCover, states);
	}
	target.draw(_frame, states);
}

bool MenuPopup::input(InputHandler &input) {
	return false;
}

void MenuPopup::setPosition(sf::Vector2f const &position) {
	_frame.setPosition(position);
}

void MenuPopup::setSize(sf::Vector2f const &size) {
	_frame.setSize(size);
}

void MenuPopup::setScreenCover(const bool screenCover) {
	_screenCoverOn = screenCover;
}

sf::Vector2f const &MenuPopup::getPosition(void) const {
	return _frame.getPosition();
}

sf::Vector2f const &MenuPopup::getSize(void) const {
	return _frame.getSize();
}

bool MenuPopup::isScreenCoverOn(void) const {
	return _screenCoverOn;
}
