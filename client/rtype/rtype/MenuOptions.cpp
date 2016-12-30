#include "MenuOptions.hpp"

#include "MainMenuResource.hpp"

const std::string MenuOptions::FORM_HOST_FIELD = "Host IP";
const std::string MenuOptions::FORM_PORT_FIELD = "Port";
const float MenuOptions::SLIDER_HEIGHT = 30.f;
const float MenuOptions::ELEMENTS_PADDING = 15.f;
const sf::Color MenuOptions::SLIDER_FOCUSED_COLOR = sf::Color::White;
const sf::Color MenuOptions::SLIDER_INACTIVE_COLOR = sf::Color(120, 120, 120);

MenuOptions::MenuOptions() {
	
}

MenuOptions::~MenuOptions() {
	
}

void MenuOptions::init(sf::Font *font) {
	_font = font;
	_focusedItem = FORM;
	_form.setActive(true);
	_form.addField(FORM_HOST_FIELD);
	_form.addField(FORM_PORT_FIELD);
	_form.setSize(sf::Vector2f(_form.getSize().x, _form.getIdealHeight()));
	_soundSlider.setSize(sf::Vector2f(_form.getSize().x - 100.f, SLIDER_HEIGHT));
	_musicSlider.setSize(_soundSlider.getSize());
	_soundSlider.setColor(SLIDER_INACTIVE_COLOR);
	_musicSlider.setColor(SLIDER_INACTIVE_COLOR);
}

bool MenuOptions::input(InputHandler &input) {
	if (input.isKeyDown(sf::Keyboard::Return) || input.isKeyDown(sf::Keyboard::Down)) {
		if (_focusedItem == FORM && _form.getFocusedField() + 1 == _form.getFieldCount()) {
			_focusedItem = SOUND_SLIDER;
			_soundSlider.setColor(SLIDER_FOCUSED_COLOR);
			_form.setActive(false);
			return true;
		}
		else if (_focusedItem == SOUND_SLIDER) {
			_focusedItem = MUSIC_SLIDER;
			_soundSlider.setColor(SLIDER_INACTIVE_COLOR);
			_musicSlider.setColor(SLIDER_FOCUSED_COLOR);
			return true;
		}
	}
	else if (input.isKeyDown(sf::Keyboard::Up)) {
		if (_focusedItem == SOUND_SLIDER) {
			_focusedItem = FORM;
			_soundSlider.setColor(SLIDER_INACTIVE_COLOR);
			_form.setActive(true);
			return true;
		}
		else if (_focusedItem == MUSIC_SLIDER) {
			_focusedItem = SOUND_SLIDER;
			_musicSlider.setColor(SLIDER_INACTIVE_COLOR);
			_soundSlider.setColor(SLIDER_FOCUSED_COLOR);
			return true;
		}
	}
	else if (input.isKeyDown(sf::Keyboard::PageUp)) {
		_focusedItem = FORM;
		_form.setFocusedField(0u);
		_form.setActive(true);
		_musicSlider.setColor(SLIDER_INACTIVE_COLOR);
		_soundSlider.setColor(SLIDER_INACTIVE_COLOR);
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::PageDown)) {
		_focusedItem = MUSIC_SLIDER;
		_musicSlider.setColor(SLIDER_FOCUSED_COLOR);
		_form.setFocusedField(1u);
		_form.setActive(false);
		_soundSlider.setColor(SLIDER_INACTIVE_COLOR);
		return true;
	}

	switch (_focusedItem) {
	case FORM:
		return _form.input(input);
	case SOUND_SLIDER:
		return _soundSlider.input(input);
	case MUSIC_SLIDER:
		return _musicSlider.input(input);
	default:
		break;
	}
	return false;
}

void MenuOptions::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	sf::Text sliderLabel;
	sliderLabel.setCharacterSize(18u);
	sliderLabel.setFont(*_font);

	target.draw(_form);

	sliderLabel.setString("Sound:");
	sliderLabel.setPosition(sf::Vector2f(_form.getPosition().x, _soundSlider.getPosition().y));
	sliderLabel.setFillColor(_soundSlider.getColor());
	target.draw(sliderLabel);
	target.draw(_soundSlider);

	sliderLabel.setString("Music:");
	sliderLabel.setPosition(sf::Vector2f(_form.getPosition().x, _musicSlider.getPosition().y));
	sliderLabel.setFillColor(_soundSlider.getColor());
	target.draw(sliderLabel);
	target.draw(_musicSlider);
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

float MenuOptions::getSoundValue(void) const {
	return _soundSlider.getValue();
}

float MenuOptions::getMusicValue(void) const {
	return _musicSlider.getValue();
}

uint8_t MenuOptions::getFocusedItem(void) const {
	return static_cast<uint8_t>(_focusedItem);
}

void MenuOptions::setPosition(sf::Vector2f const &position) {
	_form.setPosition(position);
	_soundSlider.setPosition(sf::Vector2f(_form.getPosition().x + _form.getSize().x - _soundSlider.getSize().x, _form.getPosition().y + _form.getSize().y + ELEMENTS_PADDING));
	_musicSlider.setPosition(sf::Vector2f(_form.getPosition().x + _form.getSize().x - _musicSlider.getSize().x, _soundSlider.getPosition().y + _soundSlider.getSize().y + ELEMENTS_PADDING));
}

void MenuOptions::setWidth(const float width) {
	_form.setSize(sf::Vector2f(width, _form.getSize().y));
	_soundSlider.setSize(sf::Vector2f(_form.getSize().x - 100.f, SLIDER_HEIGHT));
	_musicSlider.setSize(_soundSlider.getSize());
}

void MenuOptions::setHost(std::string const &host) {
	_form.setFieldContent(FORM_HOST_FIELD, host);
}

void MenuOptions::setPort(std::string const &port) {
	_form.setFieldContent(FORM_PORT_FIELD, port);
}

void MenuOptions::setSoundValue(const float value) {
	_soundSlider.setValue(value);
}

void MenuOptions::setMusicValue(const float value) {
	_musicSlider.setValue(value);
}

void MenuOptions::resetFocus(void) {
	_focusedItem = FORM;
	_form.setActive(true);
	_soundSlider.setColor(SLIDER_INACTIVE_COLOR);
	_musicSlider.setColor(SLIDER_INACTIVE_COLOR);
	_form.setFocusedField(0u);
}
