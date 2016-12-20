#include "ProjectResource.hpp"

#include "MenuTextForm.hpp"

const float MenuTextForm::FRAME_OUTILINE_THICKNESS = 2.f;
const sf::Color MenuTextForm::DEFAULT_BACKGROUND_COLOR = sf::Color::Black;
const sf::Color MenuTextForm::DEFAULT_TEXT_COLOR = sf::Color::White;
const sf::Color MenuTextForm::INACTIVE_COVER_COLOR = sf::Color(0, 0, 0, 120);
const uint32_t MenuTextForm::LABEL_FONT_CHAR_SIZE = 16u;
const float MenuTextForm::FORM_LATERAL_PADDING = 10.f;
const float MenuTextForm::FORM_VERTICAL_PADDING = 10.f;
const float MenuTextForm::TEXT_FIELD_HEIGHT = 40.f;

MenuTextForm::MenuTextForm() : _focusedField(0) {
	_frame.setFillColor(DEFAULT_BACKGROUND_COLOR);
	_frame.setOutlineThickness(FRAME_OUTILINE_THICKNESS);
}

MenuTextForm::~MenuTextForm() {

}

void MenuTextForm::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(_frame, states);
	if (!_fields.empty()) {
		sf::Text label;
		sf::RectangleShape inactiveCover;

		inactiveCover.setFillColor(INACTIVE_COVER_COLOR);
		label.setCharacterSize(LABEL_FONT_CHAR_SIZE);
		label.setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));
		for (uint32_t i = 0; i < getDrawnFieldsMax() && i < _fields.size(); i++) {
			label.setString(_fields.at(i).first + ":");
			label.setPosition(sf::Vector2f(_fields.at(i).second.getPosition().x, _fields.at(i).second.getPosition().y - FORM_VERTICAL_PADDING - LABEL_FONT_CHAR_SIZE));
			target.draw(label);
			target.draw(_fields.at(i).second);
			if (i != _focusedField) {
				inactiveCover.setPosition(_fields.at(i).second.getPosition());
				inactiveCover.setSize(_fields.at(i).second.getSize());
				target.draw(inactiveCover, states);
			}
		}
	}
}

bool MenuTextForm::input(InputHandler &input) {
	if (!_fields.empty()) {
		if (input.isKeyDown(sf::Keyboard::Down) || input.isKeyDown(sf::Keyboard::Tab) || input.isKeyDown(sf::Keyboard::Return)) {
			if (_focusedField < _fields.size() - 1)
				_focusedField++;
			updateLayout();
			return true;
		}
		else if (input.isKeyDown(sf::Keyboard::Up)) {
			if (_focusedField != 0)
				_focusedField--;
			updateLayout();
			return true;
		}
		else {
			try {
				return _fields.at(_focusedField).second.input(input);
			}
			catch (std::exception const &) {
				_focusedField = 0;
			}
		}
	}
	return false;
}

void MenuTextForm::setSize(sf::Vector2f const &size) {
	_frame.setSize(size);
	updateLayout();
}

void MenuTextForm::setPosition(sf::Vector2f const &position) {
	_frame.setPosition(position);
}

void MenuTextForm::addField(std::string const &name, std::string const &content) {
	_fields.push_back(std::make_pair(name, MenuTextField()));
	_fields.rbegin()->second.setContent(content);
	updateLayout();
}

void MenuTextForm::setFieldContent(std::string const &fieldName, std::string const &content) {
	try {
		getField(fieldName).setContent(content);
	}
	catch (std::out_of_range const &) {

	}
}

void MenuTextForm::clearFieldsContent(void) {
	for (auto &field : _fields) {
		field.second.clear();
	}
}

void MenuTextForm::removeFields(void) {
	_fields.clear();
	updateLayout();
}

void MenuTextForm::setFocusedField(const uint32_t field) {
	_focusedField = field;
	if (_focusedField >= _fields.size())
		_focusedField = _fields.size() ? _fields.size() - 1 : 0;
	updateLayout();
}

sf::Vector2f const &MenuTextForm::getSize(void) const {
	return _frame.getSize();
}

sf::Vector2f const &MenuTextForm::getPosition(void) const {
	return _frame.getPosition();
}

float MenuTextForm::getIdealHeight(void) const {
	return _fields.size() * (TEXT_FIELD_HEIGHT + LABEL_FONT_CHAR_SIZE + FORM_VERTICAL_PADDING * 2) + (FORM_VERTICAL_PADDING);
}

uint32_t MenuTextForm::getFieldCount(void) const {
	return _fields.size();
}

std::string const &MenuTextForm::getFieldContent(std::string const &fieldName) const {
	try {
		return getField(fieldName).getContent();
	}
	catch (std::out_of_range const &ex) {
		throw std::runtime_error(ex.what());
	}
}

MenuTextField const & MenuTextForm::getField(std::string const & fieldName) const {
	for (auto &field : _fields) {
		if (field.first == fieldName)
			return field.second;
	}
	throw std::out_of_range("getField(\"" + fieldName + "\")");
}

uint32_t MenuTextForm::getDrawnFieldsMax(void) const {
	return static_cast<uint32_t>((_frame.getSize().y - FORM_VERTICAL_PADDING) / (TEXT_FIELD_HEIGHT + FORM_VERTICAL_PADDING * 2 + LABEL_FONT_CHAR_SIZE));
}

uint32_t MenuTextForm::getFocusedField(void) const {
	return _focusedField;
}

MenuTextField &MenuTextForm::getField(std::string const &fieldName) {
	for (auto &field : _fields) {
		if (field.first == fieldName)
			return field.second;
	}
	throw std::out_of_range("getField(\"" + fieldName + "\")");
}

void MenuTextForm::updateLayout(void) {
	sf::Vector2f pos(_frame.getPosition());

	pos.x += FORM_LATERAL_PADDING;
	for (uint32_t i = 0; i < _fields.size(); i++) {
		_fields.at(i).second.setCursorVisiblity(i == _focusedField);
		pos.y += FORM_VERTICAL_PADDING * 2 + LABEL_FONT_CHAR_SIZE;
		_fields.at(i).second.setPosition(pos);
		_fields.at(i).second.setSize(sf::Vector2f(_frame.getSize().x - (FORM_LATERAL_PADDING * 2), TEXT_FIELD_HEIGHT));
		pos.y += TEXT_FIELD_HEIGHT;
	}
}