#include "MenuConfirmPopup.hpp"

const std::string MenuConfirmPopup::CONFIRM_BUTTON_LABEL_DEFAULT = "Confirm";
const std::string MenuConfirmPopup::CANCEL_BUTTON_LABEL_DEFAULT = "Cancel";
const float MenuConfirmPopup::MESSAGE_LATERAL_PADDING = 10.f;
const float MenuConfirmPopup::MESSAGE_VERTICAL_PADDING = 10.f;
const uint32_t MenuConfirmPopup::BUTTON_FONT_SIZE = 22u;

MenuConfirmPopup::MenuConfirmPopup(const bool screenCover) : MenuPopup(screenCover) {
	_confirmButton.setColorForAllStates(sf::Color::White);
	_confirmButton.setColorForState(sf::Color::Red, MenuButton::State::HOVERED);
	_confirmButton.setCharacterSize(BUTTON_FONT_SIZE);
	_confirmButton.setLabel(CONFIRM_BUTTON_LABEL_DEFAULT);
	_cancelButton.setColorForAllStates(sf::Color::White);
	_cancelButton.setColorForState(sf::Color::Red, MenuButton::State::HOVERED);
	_cancelButton.setCharacterSize(BUTTON_FONT_SIZE);
	_cancelButton.setLabel(CANCEL_BUTTON_LABEL_DEFAULT);
	updateDisplay();
}

MenuConfirmPopup::~MenuConfirmPopup() {

}

void MenuConfirmPopup::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	MenuPopup::draw(target, states);
	target.draw(_message, states);
	target.draw(_confirmButton, states);
	target.draw(_cancelButton, states);
}

bool MenuConfirmPopup::input(InputHandler &input) {
	if (input.isKeyDown(sf::Keyboard::Right) || input.isJoystickRight()) {
		_confirmButton.setState(MenuButton::State::INACTIVE);
		_cancelButton.setState(MenuButton::State::HOVERED);
	}
	else if (input.isKeyDown(sf::Keyboard::Left) || input.isJoystickLeft()) {
		_confirmButton.setState(MenuButton::State::HOVERED);
		_cancelButton.setState(MenuButton::State::INACTIVE);
	}
	else if (input.isKeyDown(sf::Keyboard::Tab)) {
		if (_confirmButton.getState() == MenuButton::State::INACTIVE) {
			_confirmButton.setState(MenuButton::State::HOVERED);
			_cancelButton.setState(MenuButton::State::INACTIVE);
		}
		else {
			_confirmButton.setState(MenuButton::State::INACTIVE);
			_cancelButton.setState(MenuButton::State::HOVERED);
		}
	}
	return false;
}

void MenuConfirmPopup::updateDisplay(void) {
	try {
		setSize(getSize());
		setPosition(getPosition());
	}
	catch (std::exception const &) {

	}
}

void MenuConfirmPopup::setPosition(sf::Vector2f const &position) {
	MenuPopup::setPosition(position);
	_message.setPosition(sf::Vector2f(getPosition().x + MESSAGE_LATERAL_PADDING, getPosition().y + MESSAGE_VERTICAL_PADDING));
	_confirmButton.setPosition(sf::Vector2f(_message.getPosition().x, getPosition().y + getSize().y - _confirmButton.getGlobalBounds().height - MESSAGE_VERTICAL_PADDING * 2));
	_cancelButton.setPosition(sf::Vector2f(getPosition().x + getSize().x - MESSAGE_LATERAL_PADDING - _cancelButton.getGlobalBounds().width, _confirmButton.getPosition().y));
}

void MenuConfirmPopup::setSize(sf::Vector2f const &size) {
	MenuPopup::setSize(size);
	_confirmButton.setPosition(sf::Vector2f(_message.getPosition().x, getPosition().y + getSize().y - _confirmButton.getGlobalBounds().height - MESSAGE_VERTICAL_PADDING * 2));
	_cancelButton.setPosition(sf::Vector2f(getPosition().x + getSize().x - MESSAGE_LATERAL_PADDING - _cancelButton.getGlobalBounds().width, _confirmButton.getPosition().y));
}

void MenuConfirmPopup::setFont(sf::Font const *font) {
	_message.setFont(*font);
	_confirmButton.setFontForAllStates(font);
	_cancelButton.setFontForAllStates(font);
	updateDisplay();
}

void MenuConfirmPopup::setMessage(std::string const &message) {
	_message.setString(message);
	updateDisplay();
}

void MenuConfirmPopup::setConfirmButtonLabel(std::string const &label) {
	_confirmButton.setLabel(label);
	updateDisplay();
}

void MenuConfirmPopup::setCancelButtonLabel(std::string const &label) {
	_cancelButton.setLabel(label);
	updateDisplay();
}

void MenuConfirmPopup::setConfirmed(const bool confirmed) {
	if (confirmed) {
		_confirmButton.setState(MenuButton::State::HOVERED);
		_cancelButton.setState(MenuButton::State::INACTIVE);
	}
	else {
		_cancelButton.setState(MenuButton::State::HOVERED);
		_confirmButton.setState(MenuButton::State::INACTIVE);
	}
}

bool MenuConfirmPopup::isConfirmed(void) const {
	return _confirmButton.getState() == MenuButton::State::HOVERED;
}
