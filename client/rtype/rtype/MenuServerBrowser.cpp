#include "ProjectResource.hpp"

#include "MenuServerBrowser.hpp"

const float MenuServerBrowser::FRAME_OUTLINE_THICKNESS = 2.f;
const sf::Color MenuServerBrowser::ITEM_BASE_COLOR = sf::Color::Black;
const sf::Color MenuServerBrowser::ITEM_SECOND_COLOR = sf::Color::White;
const float MenuServerBrowser::ITEMS_HEIGHT = 30.f;
const float MenuServerBrowser::ITEMS_SPACING = 0.f;
const uint32_t MenuServerBrowser::FONT_CHAR_SIZE = 13;
const float MenuServerBrowser::TEXT_TOP_PADDING = 2.f;
const float MenuServerBrowser::TEXT_LEFT_PADDING = 2.f;

MenuServerBrowser::MenuServerBrowser() : _selected(0) {
	_frame.setFillColor(sf::Color::Black);
	_frame.setOutlineColor(sf::Color::White);
	_frame.setOutlineThickness(FRAME_OUTLINE_THICKNESS);
}

MenuServerBrowser::~MenuServerBrowser() {
	_content.clear();
}

void MenuServerBrowser::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(_frame, states);
	if (!_content.empty()) {
		sf::Vector2f itemSize(_frame.getSize().x, ITEMS_HEIGHT);
		sf::Vector2f itemPos(_frame.getPosition().x, _frame.getPosition().y);
		sf::RectangleShape itemBackground;
		sf::Text itemLabel;
		size_t firstItemDisplayed = 0;

		if (_selected > static_cast<int>(getDisplayedItemsMax() - 1)) {
			firstItemDisplayed = _selected - (getDisplayedItemsMax() - 1);
		}

		itemLabel.setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));
		itemLabel.setCharacterSize(FONT_CHAR_SIZE);
		itemBackground.setSize(itemSize);

		for (size_t i = firstItemDisplayed; i < (firstItemDisplayed + getDisplayedItemsCount()); i++) {
			if (i == static_cast<size_t>(_selected)) {
				itemBackground.setFillColor(ITEM_SECOND_COLOR);
				itemLabel.setFillColor(ITEM_BASE_COLOR);
			}
			else {
				itemBackground.setFillColor(ITEM_BASE_COLOR);
				itemLabel.setFillColor(ITEM_SECOND_COLOR);
			}

			itemBackground.setPosition(itemPos);

			target.draw(itemBackground, states);

			itemLabel.setString(_content.at(i));
			itemLabel.setPosition(sf::Vector2f(itemPos.x + TEXT_LEFT_PADDING, itemPos.y + TEXT_TOP_PADDING));

			target.draw(itemLabel, states);

			itemPos.y += itemBackground.getSize().y;
		}
	}
}

bool MenuServerBrowser::input(InputHandler &input) {
	if (input.isKeyDown(sf::Keyboard::Up)) {
		_selected--;
		if (_selected < 0)
			_selected = (_content.size() ? _content.size() - 1 : 0);
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::Down)) {
		_selected++;
		if (static_cast<size_t>(_selected) >= _content.size())
			_selected = 0;
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::PageDown)) {
		_selected = _content.empty() ? 0 : _content.size() - 1;
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::PageUp)) {
		_selected = 0;
		return true;
	}
	return false;
}

void MenuServerBrowser::setSize(sf::Vector2f const &size) {
	_frame.setSize(size);
}

void MenuServerBrowser::setPosition(sf::Vector2f const &pos) {
	_frame.setPosition(pos);
}

void MenuServerBrowser::clearContent(void) {
	_content.clear();
}

void MenuServerBrowser::setContent(std::vector<std::string> const &content) {
	_content = content;
}

void MenuServerBrowser::setSelected(const int selected) {
	_selected = selected;
}

sf::Vector2f const &MenuServerBrowser::getSize(void) const {
	return _frame.getSize();
}

sf::Vector2f const &MenuServerBrowser::getPosition(void) const {
	return _frame.getPosition();
}

std::vector<std::string> const &MenuServerBrowser::getContent(void) const {
	return _content;
}

int MenuServerBrowser::getSelected(void) const {
	return _selected;
}

size_t MenuServerBrowser::getDisplayedItemsMax(void) const {
	return static_cast<size_t>(_frame.getSize().y / (ITEMS_HEIGHT + ITEMS_SPACING));
}

size_t MenuServerBrowser::getDisplayedItemsCount(void) const {
	size_t itemsDisplayMax = getDisplayedItemsMax();

	return (itemsDisplayMax < _content.size() ? itemsDisplayMax : _content.size());
}

float MenuServerBrowser::getHeightForItems(const size_t items) {
	return items * (ITEMS_HEIGHT + ITEMS_SPACING);
}