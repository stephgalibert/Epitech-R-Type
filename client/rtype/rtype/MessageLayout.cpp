#include "MessageLayout.hpp"

MessageLayout::MessageLayout(void)
{
	_delta = 0;
	_resolution.x = StaticTools::GetResolution().first;
	_resolution.y = StaticTools::GetResolution().second;
}

MessageLayout::~MessageLayout(void)
{
}

void MessageLayout::init(void)
{
	try {

	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

bool MessageLayout::input(InputHandler &input)
{
	(void)input;
	return (false);
}

void MessageLayout::update(float delta)
{
	_delta += delta;

	if (!_texts.empty() && _delta > 2.f) {
		pop();
		_delta = 0;
	}
}

void MessageLayout::recycle(void)
{
}

void MessageLayout::addMessage(std::string const& msg)
{
	std::list<sf::Text>::iterator it = _texts.emplace<sf::Text>(_texts.begin(), {});

	if (it != std::end(_texts)) {
		it->setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));
		it->setCharacterSize(10);
		it->setFillColor(sf::Color::Red);
		it->setString(msg);
	}

	if (_texts.size() > 5) {
		_texts.pop_back();
	}

	size_t i = 0;
	for (auto &it : _texts) {
		it.setPosition(sf::Vector2f(20.f, 170.f + (30.f * ((float)i - 5.f))));
		++i;
	}

	_delta = 0;
}

void MessageLayout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (auto &it : _texts) {
		target.draw(it);
	}
}

void MessageLayout::pop(void)
{
	_texts.pop_back();
}