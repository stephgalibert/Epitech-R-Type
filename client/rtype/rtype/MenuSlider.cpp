#include "MenuSlider.hpp"

const uint32_t MenuSlider::MAX_VALUE = 100u;
const uint32_t MenuSlider::MIN_VALUE = 0u;
const float MenuSlider::VALUE_BAR_WIDTH = 5u;
const sf::Color MenuSlider::DEFAULT_COLOR = sf::Color::White;

MenuSlider::MenuSlider(float value) {
	setValue(value);
	setColor(DEFAULT_COLOR);
	updateDisplay();
}

MenuSlider::~MenuSlider() {
}

void MenuSlider::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  (void)states;
	target.draw(_sliderHorizontalBar);
	target.draw(_sliderValueBar);
}

bool MenuSlider::input(InputHandler &input) {
	if (input.isKeyDown(sf::Keyboard::Right)) {
		if (_value < MAX_VALUE)
			_value++;
		updateDisplay();
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::Left)) {
		if (_value > MIN_VALUE)
			_value--;
		updateDisplay();
		return true;
	}
	return false;
}

void MenuSlider::updateDisplay(void) {
	_sliderHorizontalBar.setSize(sf::Vector2f(_size.x - VALUE_BAR_WIDTH, VALUE_BAR_WIDTH));
	_sliderValueBar.setSize(sf::Vector2f(VALUE_BAR_WIDTH, _size.y));

	_sliderHorizontalBar.setPosition(sf::Vector2f(_position.x + VALUE_BAR_WIDTH / 2, _position.y + _size.y / 2 - _sliderHorizontalBar.getSize().y / 2));
	_sliderValueBar.setPosition(sf::Vector2f(_sliderHorizontalBar.getPosition().x - VALUE_BAR_WIDTH / 2 + (_sliderHorizontalBar.getSize().x / MAX_VALUE) * _value, _position.y));
}

sf::Vector2f const &MenuSlider::getPosition(void) const {
	return _position;
}

sf::Vector2f const & MenuSlider::getSize(void) const {
	return _size;
}

float MenuSlider::getValue(void) const {
	return _value;
}

sf::Color const & MenuSlider::getColor(void) const {
	return _sliderHorizontalBar.getFillColor();
}

void MenuSlider::setPosition(sf::Vector2f const &position) {
	_position = position;
	updateDisplay();
}

void MenuSlider::setSize(sf::Vector2f const &size) {
	_size = size;
	updateDisplay();
}

void MenuSlider::setValue(const float value) {
	if (value > MAX_VALUE)
		_value = MAX_VALUE;
	else if (value < MIN_VALUE)
		_value = MIN_VALUE;
	else
		_value = value;
	updateDisplay();
}

void MenuSlider::setColor(sf::Color const &color) {
	_sliderHorizontalBar.setFillColor(color);
	_sliderValueBar.setFillColor(color);
}
