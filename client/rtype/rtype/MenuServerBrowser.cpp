#include "ProjectResource.hpp"
#include "MainMenuResource.hpp"

#include "MenuServerBrowser.hpp"

const float MenuServerBrowser::FRAME_OUTLINE_THICKNESS = 2.f;
const sf::Color MenuServerBrowser::ITEM_BASE_COLOR = sf::Color::Black;
const sf::Color MenuServerBrowser::ITEM_SECOND_COLOR = sf::Color::White;
const float MenuServerBrowser::ITEMS_HEIGHT = 30.f;
const float MenuServerBrowser::ITEMS_SPACING = 0.f;
const uint32_t MenuServerBrowser::FONT_CHAR_SIZE = 16u;
const float MenuServerBrowser::TEXT_TOP_PADDING = 2.f;
const float MenuServerBrowser::TEXT_LEFT_PADDING = 2.f;
const std::string MenuServerBrowser::EMPTY_MESSAGE = "No games found";

MenuServerBrowser::MenuServerBrowser() : _selected(0) {
	_frame.setFillColor(sf::Color::Black);
	_frame.setOutlineColor(sf::Color::White);
	_frame.setOutlineThickness(FRAME_OUTLINE_THICKNESS);

	_emptyMessage.setString(EMPTY_MESSAGE);
	_emptyMessage.setCharacterSize(30u);
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
		sf::Text itemLabel, itemPlayers;
		sf::Sprite locked;
		size_t firstItemDisplayed = 0;

		if (_selected > static_cast<int>(getDisplayedItemsMax() - 1)) {
			firstItemDisplayed = _selected - (getDisplayedItemsMax() - 1);
		}

		try {
			locked.setTexture(*MainMenuResource::menuResourceManager.getTextureByKey(MainMenuResource::LOCKED_SERVER));
		}
		catch (std::runtime_error const &) {

		}

		itemLabel.setFont(*_font);
		itemLabel.setCharacterSize(FONT_CHAR_SIZE);
		itemPlayers.setFont(*_font);
		itemPlayers.setCharacterSize(FONT_CHAR_SIZE);
		itemBackground.setSize(itemSize);

		for (size_t i = firstItemDisplayed; i < (firstItemDisplayed + getDisplayedItemsCount()); i++) {
			if (i == static_cast<size_t>(_selected)) {
				itemBackground.setFillColor(ITEM_SECOND_COLOR);
				itemLabel.setFillColor(ITEM_BASE_COLOR);
				itemPlayers.setFillColor(ITEM_BASE_COLOR);
				locked.setColor(ITEM_BASE_COLOR);
			}
			else {
				itemBackground.setFillColor(ITEM_BASE_COLOR);
				itemLabel.setFillColor(ITEM_SECOND_COLOR);
				locked.setColor(ITEM_SECOND_COLOR);
				itemPlayers.setFillColor(ITEM_SECOND_COLOR);
			}

			itemBackground.setPosition(itemPos);

			target.draw(itemBackground, states);

			itemLabel.setString(_content.at(i).name);
			itemLabel.setPosition(sf::Vector2f(itemPos.x + TEXT_LEFT_PADDING, itemPos.y + TEXT_TOP_PADDING));
			locked.setPosition(sf::Vector2f(itemLabel.getPosition().x + itemLabel.getGlobalBounds().width + TEXT_LEFT_PADDING, itemLabel.getPosition().y + 2.f));
			itemPlayers.setString(std::to_string(_content.at(i).playersCount) + " / 4");
			itemPlayers.setPosition(sf::Vector2f(getPosition().x + getSize().x - itemPlayers.getGlobalBounds().width - TEXT_LEFT_PADDING - 2.f, itemLabel.getPosition().y));

			target.draw(itemLabel, states);
			if (_content.at(i).hasPassword)
				target.draw(locked);
			target.draw(itemPlayers, states);

			itemPos.y += itemBackground.getSize().y;
		}
	}
	else {
		target.draw(_emptyMessage);
	}
}

bool MenuServerBrowser::input(InputHandler &input) {
	if (input.isKeyDown(sf::Keyboard::Up)) {
		_selected--;
		if (_selected < 0)
			_selected = (_content.size() ? _content.size() - 1 : 0);
		if (!_content.empty())
			MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_3);
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::Down)) {
		_selected++;
		if (static_cast<size_t>(_selected) >= _content.size())
			_selected = 0;
		if (!_content.empty())
			MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_3);
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::PageDown)) {
		_selected = _content.empty() ? 0 : _content.size() - 1;
		MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_3);
		return true;
	}
	else if (input.isKeyDown(sf::Keyboard::PageUp)) {
		_selected = 0;
		MainMenuResource::menuResourceManager.playSound(MainMenuResource::NAV_SOUND_3);
		return true;
	}
	return false;
}

void MenuServerBrowser::setSize(sf::Vector2f const &size) {
	_frame.setSize(size);
	_emptyMessage.setPosition(getPosition().x + getSize().x / 2 - _emptyMessage.getGlobalBounds().width / 2, getPosition().y + getSize().y / 2 - _emptyMessage.getGlobalBounds().height / 2);
}

void MenuServerBrowser::setPosition(sf::Vector2f const &pos) {
	_frame.setPosition(pos);
	_emptyMessage.setPosition(getPosition().x + getSize().x / 2 - _emptyMessage.getGlobalBounds().width / 2, getPosition().y + getSize().y / 2 - _emptyMessage.getGlobalBounds().height / 2);
}

void MenuServerBrowser::setFont(sf::Font const *font) {
	_font = font;
	_emptyMessage.setFont(*font);
	_emptyMessage.setPosition(getPosition().x + getSize().x / 2 - _emptyMessage.getGlobalBounds().width / 2, getPosition().y + getSize().y / 2 - _emptyMessage.getGlobalBounds().height / 2);
}

void MenuServerBrowser::clearContent(void) {
	_content.clear();
}

void MenuServerBrowser::setContent(std::vector<MenuServerBrowser::PartyData> const &content) {
	_content = content;
}

void MenuServerBrowser::setSelected(const int selected) {
	_selected = selected;
}

void MenuServerBrowser::addEntry(MenuServerBrowser::PartyData const &entry) {
	_content.push_back(entry);
}

void MenuServerBrowser::addEntry(GetParty const &entry) {
	PartyData data;

	data.hasPassword = entry.pwdPresent;
	data.name = std::string(entry.data, entry.size);
	data.playersCount = entry.nbPlayer;
	data.running = entry.running;

	_content.push_back(data);
}

sf::Vector2f const &MenuServerBrowser::getSize(void) const {
	return _frame.getSize();
}

sf::Vector2f const &MenuServerBrowser::getPosition(void) const {
	return _frame.getPosition();
}

std::vector<MenuServerBrowser::PartyData> const &MenuServerBrowser::getContent(void) const {
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