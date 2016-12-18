#include "EscapeLayout.hpp"

EscapeLayout::EscapeLayout(void)
{
	_resolution = StaticTools::GetResolution();
	_visible = false;
	_exit = false;
	_delta = 0;
	_deltaLastAction = 0;
	_selected = 0;
}

EscapeLayout::~EscapeLayout(void)
{
}

void EscapeLayout::init(void)
{
	try {
		initBackground();
		initResumeButton();
		initQuitButton();

		up();
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

bool EscapeLayout::input(InputHandler &input)
{
	if (_deltaLastAction > 0.5f && input.isKeyDown(sf::Keyboard::Escape)) {
		_visible = !_visible;
		_deltaLastAction = 0;
	}
	if (isVisible() && _deltaLastAction > 0.2f) {
		if (input.isKeyDown(sf::Keyboard::Up)) {
			up();
			_deltaLastAction = 0;
		}
		else if (input.isKeyDown(sf::Keyboard::Down)) {
			down();
			_deltaLastAction = 0;
		}
		else if (input.isKeyDown(sf::Keyboard::Return)) {
			enter();
			_deltaLastAction = 0;
		}
	}
	return (false);
}

void EscapeLayout::update(float delta)
{
	_deltaLastAction += delta;
	if (_visible) {
		_delta += delta;
	}
}

void EscapeLayout::recycle(void)
{
}

bool EscapeLayout::isVisible(void) const
{
	return (_visible);
}

bool EscapeLayout::exit(void) const
{
	return (_exit);
}

void EscapeLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_visible) {
		states.transform *= getTransform();

		target.draw(_background);
		for (auto &it : _buttons) {
			target.draw(it);
		}
		for (auto &it : _texts) {
			target.draw(it);
		}
	}
}

void EscapeLayout::initQuitButton(void)
{
	try {
		std::vector<sf::Text>::iterator text = _texts.emplace<sf::Text>(_texts.end(), {});
		sf::RectangleShape button;

		if (text != _texts.end()) {
			(*text).setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));

			(*text).setCharacterSize(22);
			(*text).setFillColor(sf::Color::Black);
			(*text).setString("Exit");

			sf::FloatRect textRect = (*text).getLocalBounds();
			(*text).setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			(*text).setPosition(_resolution.first / 2.0f, _resolution.second / 2.0f + 30);
		}

		button.setFillColor(sf::Color(224, 224, 224, 128));
		button.setOutlineThickness(2);
		button.setOutlineColor(sf::Color(224, 224, 224, 176));
		button.setPosition(sf::Vector2f(575, 309));
		button.setSize(sf::Vector2f(130, 45));
		_buttons.push_back(button);

	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

void EscapeLayout::initResumeButton(void)
{
	try {
		std::vector<sf::Text>::iterator text = _texts.emplace<sf::Text>(_texts.end(), {});
		sf::RectangleShape button;

		if (text != _texts.end()) {
			(*text).setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));

			(*text).setCharacterSize(22);
			(*text).setFillColor(sf::Color::Black);
			(*text).setString("Resume");

			sf::FloatRect textRect = (*text).getLocalBounds();
			(*text).setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			(*text).setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f - 30));
		}

		button.setFillColor(sf::Color(224, 224, 224, 128));
		button.setOutlineThickness(2);
		button.setOutlineColor(sf::Color(224, 224, 224, 176));
		button.setPosition(sf::Vector2f(575, 367));
		button.setSize(sf::Vector2f(130, 45));
		_buttons.push_back(button);
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

void EscapeLayout::initBackground(void)
{
	try {
		_background.setFillColor(sf::Color(224, 224, 224, 128));
		_background.setOutlineThickness(4);
		_background.setOutlineColor(sf::Color(224, 224, 224, 192));
		_background.setSize(sf::Vector2f(300, 200));
		_background.setPosition(_resolution.first / 2.f - 150.f, _resolution.second / 2.f - 100.f);
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

void EscapeLayout::up(void)
{
	if (_selected < _buttons.size()) {
		sf::Color const& c = _buttons[_selected].getFillColor();
		_buttons[_selected].setFillColor(sf::Color(c.r, c.g, c.b, 128));

		++_selected;
		if (_selected >= _buttons.size()) {
			_selected = 0;
		}

		_buttons[_selected].setFillColor(sf::Color(c.r, c.g, c.b, 192));
	}
}

void EscapeLayout::down(void)
{
	if (_selected < _buttons.size()) {
		sf::Color const& c = _buttons[_selected].getFillColor();
		_buttons[_selected].setFillColor(sf::Color(c.r, c.g, c.b, 128));

		if (_selected == 0) {
			_selected = _buttons.size() - 1;
		}
		else {
			--_selected;
		}

		_buttons[_selected].setFillColor(sf::Color(c.r, c.g, c.b, 192));
	}
}

void EscapeLayout::enter(void)
{
	switch (_selected)
	{
	case 0:
		_exit = true;
		break;
	case 1:
		_visible = false;
		break;
	default:
		break;
	};
}