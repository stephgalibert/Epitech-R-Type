#include "MenuCredits.hpp"

const uint32_t MenuCredits::FONT_CHAR_SIZE = 22u;
const float MenuCredits::LINES_SPACING = 10.f;

MenuCredits::MenuCredits() {

}

MenuCredits::~MenuCredits() {

}

void MenuCredits::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for (auto const &text : _text) {
		target.draw(text);
	}
}

void MenuCredits::setPosition(sf::Vector2f const &position) {
	_position = position;

	sf::Vector2f pos(_position);
	for (auto &text : _text) {
		text.setPosition(pos);
		if (text.getString().isEmpty())
			pos.y += LINES_SPACING * 2.5f;
		else
			pos.y += text.getGlobalBounds().height + LINES_SPACING;
	}
}

void MenuCredits::addLine(std::string const &line, const uint32_t fontSize) {
	_text.push_back(sf::Text(line, *_font, fontSize));
}

void MenuCredits::init(sf::Font const *font) {
	_text.clear();
	_font = font;
	addLine("CREDITS", 30u);
	addLine();
	addLine("\tStéphane Galibert");
	addLine("\tJordan Aveline");
	addLine("\tQuentin Fernandez");
	addLine("\tClément Oliva");
	addLine();
	addLine("github.com/Stephouuu/R-Type", 18u);
	setPosition(getPosition());
}

sf::Vector2f const &MenuCredits::getPosition(void) const {
	return _position;
}
