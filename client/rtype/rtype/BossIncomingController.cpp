#include "BossIncomingController.hpp"

BossIncomingController::BossIncomingController(void)
{
	_delta = 0;
	_resolution = StaticTools::GetResolution();
	_string = "Boss incoming !!!";
	_finished = false;
	_started = false;
}

BossIncomingController::~BossIncomingController(void)
{
	ProjectResource::TheProjectResource.getMusicByKey("boss_incoming").setVolume(StaticTools::musicVolume);
	ProjectResource::TheProjectResource.getMusicByKey("boss_incoming").stop();
}

void BossIncomingController::init(void)
{
	try {
		_text.setFont(ProjectResource::TheProjectResource.getFontByKey("font_state"));

		_text.setCharacterSize(26);
		_color = sf::Color(255, 0, 0, 0);
		_text.setFillColor(_color);
		_text.setString(_string);

		sf::FloatRect textRect = _text.getLocalBounds();
		_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		_text.setPosition(sf::Vector2f(_resolution.first / 2.0f, _resolution.second / 2.0f));
	}
	catch (std::exception const& e) {
		StaticTools::Log << "GameOverController: " << e.what() << std::endl;
	}
}

bool BossIncomingController::input(InputHandler &input)
{
	(void)input;
	return (false);
}

void BossIncomingController::update(float delta)
{
	if (!_started) {
		ProjectResource::TheProjectResource.getMusicByKey("stage_01").stop();
		ProjectResource::TheProjectResource.getMusicByKey("boss_incoming").setVolume(StaticTools::musicVolume);
		ProjectResource::TheProjectResource.getMusicByKey("boss_incoming").setLoop(true);
		ProjectResource::TheProjectResource.getMusicByKey("boss_incoming").play();
		_started = true;
	}

	_delta += delta;

	if (_delta < DELAY_FINISHED) {
		if (_delta < DELAY_FINISHED - 1) {
			_color.a = static_cast<uint8_t>((_delta / (DELAY_FINISHED - 1)) * 255.f);
			_text.setFillColor(_color);
		}
	}
	else {
		_finished = true;
	}
}

void BossIncomingController::draw(sf::RenderWindow &window)
{
	window.draw(_text);
}

void BossIncomingController::recycle(void)
{
}

bool BossIncomingController::hasFinished(void) const
{
	return (_finished);
}