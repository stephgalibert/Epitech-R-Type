#include "GameOverController.hpp"

GameOverController::GameOverController(void)
{
	_delta = 0;
	_resolution = StaticTools::GetResolution();
	_string = "Game Over !";
	_stringRestartingIn = "Restarting in ... ";
	_chronoRestarting = 0;
}

GameOverController::~GameOverController(void)
{
}

void GameOverController::init(void)
{
	try {
		_text.setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));
		_restartingIn.setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));

		_text.setCharacterSize(22);
		_text.setFillColor(sf::Color::Red);
		_text.setString(_string);


		_restartingIn.setCharacterSize(20);
		_restartingIn.setFillColor(sf::Color::Red);
		_restartingIn.setString(_stringRestartingIn + std::to_string(DELAY_RESTARTING));

		sf::FloatRect textRect = _text.getLocalBounds();
		_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		_text.setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f));

		sf::FloatRect restartingInRect = _restartingIn.getLocalBounds();
		_restartingIn.setOrigin(restartingInRect.left + restartingInRect.width / 2.0f, restartingInRect.top + restartingInRect.height / 2.0f);
		_restartingIn.setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f + textRect.height + 5));

	}
	catch (std::exception const& e) {
		StaticTools::Log << "GameOverController: " << e.what() << std::endl;
	}
}

bool GameOverController::input(InputHandler &input)
{
	(void)input;
	return (false);
}

void GameOverController::update(float delta)
{
	_delta += delta;
	if (_delta > 1.f) {
		++_chronoRestarting;
		_restartingIn.setString(_stringRestartingIn + std::to_string(DELAY_RESTARTING - _chronoRestarting));
		_delta = 0;
	}
	if (_chronoRestarting == 10) {
		_chronoRestarting = 0;
	}
}

void GameOverController::draw(sf::RenderWindow &window)
{
	window.draw(_text);
	window.draw(_restartingIn);
}

void GameOverController::recycle(void)
{
}
