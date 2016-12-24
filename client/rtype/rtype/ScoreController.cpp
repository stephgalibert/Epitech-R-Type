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

		_text[0].setCharacterSize(22);
		_text[1].setCharacterSize(22);
		_text[2].setCharacterSize(22);
		_text[3].setCharacterSize(22);

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
				_text[0].setString("(You) " + (*_player)->getName() + ": " + std::to_string((*_player)->getScore()));
			}
			std::string mate;
			for (size_t i = 1; i < 4; ++i) {
				if ((_mates)[i - 1]) {
					mate = (_mates)[i - 1]->getName() + ": ";
					mate += std::to_string((_mates)[i - 1]->getScore());
					_text[i].setString(mate);

					sf::FloatRect textRect = _text[i].getLocalBounds();
					_text[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
					_text[i].setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f + ((i - 1) * 30)));
				}
			}

			sf::FloatRect textRect0 = _text[0].getLocalBounds();
			_text[0].setOrigin(textRect0.left + textRect0.width / 2.0f, textRect0.top + textRect0.height / 2.0f);
			_text[0].setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f - 30));

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