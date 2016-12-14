#include "LoadingController.hpp"

LoadingController::LoadingController(void)
{
	_delta = 0;
	_resolution = StaticTools::GetResolution();
	_point = ".";
}

LoadingController::~LoadingController(void)
{
}

void LoadingController::init(void)
{
	try {
		_text.setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));

		setTextSize(22);
		setTextColor(sf::Color::Red);
		setText(_string + " " + _point);
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

bool LoadingController::input(InputHandler &input)
{
	(void)input;
	return (false);
}

void LoadingController::update(float delta)
{
	_delta += delta;

	if (_delta > 1.f) {
		_point = std::string(_point.size() + 1, '.');
		setText(_string + " " + _point);
		if (_point.size() > 2) {
			_point.clear();
		}
		_delta = 0;
	}
}

void LoadingController::draw(sf::RenderWindow &window)
{
	window.draw(_text);
}

void LoadingController::recycle(void)
{
}

void LoadingController::setTextColor(sf::Color const& color)
{
	_text.setFillColor(color);
}

void LoadingController::setTextSize(size_t size)
{
	_text.setCharacterSize(size);
	updateTextSize();
}

void LoadingController::setText(std::string const& text)
{
	_text.setString(text);
	updateTextSize();
}

void LoadingController::setBaseText(std::string const& text)
{
	_string = text;
	_text.setString(_string + " .");
	updateTextSize();
}

void LoadingController::updateTextSize(void)
{
	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	_text.setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f));
}
