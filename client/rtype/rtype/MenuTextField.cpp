#include "ProjectResource.hpp"
#include "MenuTextField.hpp"

const float MenuTextField::FRAME_OUTILINE_THICKNESS = 2.f;
const sf::Color MenuTextField::DEFAULT_BACKFROUND_COLOR = sf::Color::Black;
const sf::Color MenuTextField::DEFAULT_TEXT_COLOR = sf::Color::White;
const uint32_t MenuTextField::FONT_CHAR_SIZE = 20u;
const float MenuTextField::TEXT_LEFT_PADDING = 3.f;
const float MenuTextField::TEXT_TOP_PADDING = 3.f;
const float MenuTextField::CURSOR_BAR_WIDTH = 1.f;

MenuTextField::MenuTextField() : _cursor(0u), _textDisplayOffset(0u), _cursorVisible(true) {
	try {
		_frame.setFillColor(DEFAULT_BACKFROUND_COLOR);
		_frame.setOutlineThickness(FRAME_OUTILINE_THICKNESS);

		_text.setFillColor(DEFAULT_TEXT_COLOR);
		_text.setCharacterSize(FONT_CHAR_SIZE);

		_cursorBar.setFillColor(DEFAULT_TEXT_COLOR);
	}
	catch (std::exception const &ex) {
		throw std::runtime_error(std::string("MenuTextField: ") + ex.what());
	}
}

MenuTextField::MenuTextField(sf::Vector2f const &position, sf::Vector2f const &size, const uint32_t fontSize) : MenuTextField() {
	setPosition(position);
	setSize(size);
	setFontSize(fontSize);
}

MenuTextField::~MenuTextField() {
}

void MenuTextField::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(_frame, states);
	target.draw(_text, states);
	if (_cursorVisible)
		target.draw(_cursorBar, states);
}

bool MenuTextField::input(InputHandler &input) {
	if (input.isKeyDown(sf::Keyboard::BackSpace)) {
		if (_cursor != 0) {
			try {
				_content.erase(_cursor - 1, 1);
				cursorBack();
			}
			catch (std::out_of_range const &) {
				_cursor = 0u;
				_textDisplayOffset = 0u;
			}
			updateTextDisplay();
		}
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::Left)) {
		cursorBack();
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::Right)) {
		cursorForward();
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::Home)) {
		_cursor = 0u;
		_textDisplayOffset = 0u;
		updateTextDisplay();
	}
	else if (input.isKeyDown(sf::Keyboard::End)) {
		setCursorPos(_content.length());
	}
	else if (input.isTextEntered()) {
		return handleTextInput(input);
	}
	return false;
}

bool MenuTextField::handleTextInput(InputHandler &input) {
	char newChar = input.popTextEntered();

	_content.insert(_cursor, 1, newChar);
	cursorForward();
	updateTextDisplay();
	return true;
}

void MenuTextField::updateTextDisplay(void) {
	_text.setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));

	std::string dispStr = _content.substr(_textDisplayOffset, _textDisplayOffset + getDisplayedLettersMax());

	_text.setString(dispStr);
	if (_cursor < dispStr.length())
		_cursorBar.setPosition(sf::Vector2f(_text.findCharacterPos(_cursor - _textDisplayOffset).x, _text.getPosition().y - (TEXT_TOP_PADDING / 2.f)));
	else
		_cursorBar.setPosition(sf::Vector2f(_text.getPosition().x + _text.getGlobalBounds().width + 2.f, _text.getPosition().y - (TEXT_TOP_PADDING / 2.f)));
}

void MenuTextField::setSize(sf::Vector2f const &size) {
	_frame.setSize(size);
	_cursorBar.setSize(sf::Vector2f(CURSOR_BAR_WIDTH, size.y - (TEXT_TOP_PADDING * 2)));
	_textDisplayOffset = (_cursor <= getDisplayedLettersMax() ? 0u : (_cursor - getDisplayedLettersMax()));
	updateTextDisplay();
}

void MenuTextField::setPosition(sf::Vector2f const &position) {
	_frame.setPosition(position);
	_text.setPosition(sf::Vector2f(position.x + TEXT_LEFT_PADDING, position.y + TEXT_TOP_PADDING));
	updateTextDisplay();
}

void MenuTextField::setFontSize(const uint32_t fontSize) {
	_text.setCharacterSize(fontSize);
	updateTextDisplay();
}

void MenuTextField::setContent(std::string const &content) {
	_content = content;
	setCursorPos(_content.length());
	updateTextDisplay();
}

void MenuTextField::clear(void) {
	_content.clear();
	_cursor = 0u;
	_textDisplayOffset = 0u;
	updateTextDisplay();
}

void MenuTextField::cursorForward(void) {
	if (_cursor != _content.length()) {
		_cursor++;
		if (_cursor > _textDisplayOffset + getDisplayedLettersMax())
			_textDisplayOffset++;
		updateTextDisplay();
	}
}

void MenuTextField::cursorBack(void) {
	if (_cursor != 0u) {
		_cursor--;
		if (_cursor < _textDisplayOffset + 1u && _cursor > 0u)
			_textDisplayOffset--;
		updateTextDisplay();
	}
}

void MenuTextField::setCursorPos(const uint32_t pos) {
	_cursor = (pos > _content.length() ? _content.length() : pos);
	_textDisplayOffset = (_cursor <= getDisplayedLettersMax() ? 0u : (_cursor - getDisplayedLettersMax()));
	updateTextDisplay();
}

void MenuTextField::setCursorVisiblity(const bool visible) {
	_cursorVisible = visible;
}

sf::Vector2f const &MenuTextField::getSize(void) const {
	return _frame.getSize();
}

sf::Vector2f const &MenuTextField::getPosition(void) const {
	return _frame.getPosition();
}

uint32_t MenuTextField::getFontSize(void) const {
	return _text.getCharacterSize();
}

std::string const &MenuTextField::getContent(void) const {
	return _content;
}

uint32_t MenuTextField::getDisplayedLettersMax(void) const {
	return static_cast<uint32_t>((_frame.getSize().x - (TEXT_LEFT_PADDING * 2.f)) / getFontSize());
}

bool MenuTextField::isCursorVisible(void) const {
	return _cursorVisible;
}