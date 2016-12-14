#include "ScoreController.hpp"

ScoreController::ScoreController(Player **player, Mate **mates)
{
	_delta = 0;
	_resolution = StaticTools::GetResolution();
	_player = player;
	_mates = mates;
}

ScoreController::~ScoreController(void)
{
}

void ScoreController::init(void)
{
	try {
		_text[0].setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));
		_text[1].setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));
		_text[2].setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));
		_text[3].setFont(ProjectResource::TheProjectResource.getFontByKey(ProjectResource::MAIN_FONT));

		_text[0].setCharacterSize(16);
		_text[1].setCharacterSize(16);
		_text[2].setCharacterSize(16);
		_text[3].setCharacterSize(16);

		_text[0].setFillColor(sf::Color::Red);
		_text[1].setFillColor(sf::Color::Red);
		_text[2].setFillColor(sf::Color::Red);
		_text[3].setFillColor(sf::Color::Red);

	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

bool ScoreController::input(InputHandler &input)
{
	if (input.isKeyDown(sf::Keyboard::Tab)) {
		_visible = true;
	}
	else {
		_visible = false;
	}
	return (false);
}

void ScoreController::update(float delta)
{
	if (_visible) {
		_delta += delta;
		if (_delta > 0.2f) {
			if (_player && *_player) {
				std::cout << "player" << std::endl;
				_text[0].setString("Player: " + std::to_string((*_player)->getScore()));
			}
			for (size_t i = 1; i < 4; ++i) {
				if ((_mates)[i - 1]) {
					std::cout << "mate" << std::endl;
					_text[i].setString("Mate" + std::to_string(i) + ": " + std::to_string((_mates)[i - 1]->getScore()));
				}
			}

			sf::FloatRect textRect0 = _text[0].getLocalBounds();
			_text[0].setOrigin(textRect0.left + textRect0.width / 2.0f, textRect0.top + textRect0.height / 2.0f);
			_text[0].setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f));

			sf::FloatRect textRect1 = _text[1].getLocalBounds();
			_text[1].setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
			_text[1].setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f + 30));

			sf::FloatRect textRect2 = _text[2].getLocalBounds();
			_text[2].setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
			_text[2].setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f + 60));

			sf::FloatRect textRect3 = _text[3].getLocalBounds();
			_text[3].setOrigin(textRect3.left + textRect3.width / 2.0f, textRect3.top + textRect3.height / 2.0f);
			_text[3].setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f + 90));

			_delta = 0;
		}
	}
}

void ScoreController::draw(sf::RenderWindow &window)
{
	if (_visible) {
		window.draw(_text[0]);
		window.draw(_text[1]);
		window.draw(_text[2]);
		window.draw(_text[3]);
	}
}

void ScoreController::recycle(void)
{

}

void ScoreController::setVisible(bool value)
{
	_visible = value;
}