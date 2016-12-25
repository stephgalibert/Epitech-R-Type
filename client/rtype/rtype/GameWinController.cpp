#include "GameWinController.hpp"

GameWinController::GameWinController(void)
{
	_delta = 0;
	_resolution = StaticTools::GetResolution();
	_string = "Game Win !";
	_color = sf::Color(0, 0, 0, 0);
	_finished = false;
	_started = false;
}

GameWinController::~GameWinController(void)
{
	ProjectResource::TheProjectResource.getMusicByKey("game_win").stop();
}

void GameWinController::init(void)
{
	try {
		_text.setFont(ProjectResource::TheProjectResource.getFontByKey("font_state"));

		_text.setCharacterSize(26);
		_text.setFillColor(sf::Color::Yellow);
		_text.setString(_string);

		_shape.setSize(sf::Vector2f(_resolution.first, _resolution.second));
		_shape.setPosition(0, 0);
		_shape.setFillColor(_color);

		sf::FloatRect textRect = _text.getLocalBounds();
		_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		_text.setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f));
	}
	catch (std::exception const& e) {
		StaticTools::Log << "GameWinController: " << e.what() << std::endl;
	}
}

bool GameWinController::input(InputHandler &input)
{
	(void)input;
	return (false);
}

void GameWinController::update(float delta)
{
	_delta += delta;

	if (!_started) {
		ProjectResource::TheProjectResource.getMusicByKey("game_win").play();
		_started = true;
	}
	if (_delta < DELAY_RESTARTING) {
		if (_delta < DELAY_RESTARTING - 2) {
			_color.a = static_cast<uint8_t>((_delta / (DELAY_RESTARTING - 2)) * 255.f);
			_shape.setFillColor(_color);
		}
	}
	else {
		_finished = true;
	}
}

void GameWinController::draw(sf::RenderWindow &window)
{
	window.draw(_shape);
	window.draw(_text);
}

void GameWinController::recycle(void)
{
}

bool GameWinController::hasFinished(void) const
{
	return (_finished);
}