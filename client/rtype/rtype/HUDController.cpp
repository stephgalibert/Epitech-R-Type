#include "HUDController.hpp"

HUDController::HUDController(void)
{
	_resolution = StaticTools::GetResolution();
}

HUDController::~HUDController(void)
{
}

void HUDController::init(void)
{
	try {
		_health.init();
		_shot.init();

		_shape.setSize(sf::Vector2f(400, 300));
		_shape.setPosition(20.f, _resolution.second - 320.f);

		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("hud1");
		texture->setSmooth(true);

		_shape.setTexture(texture);
		_colorShape.setRadius(24);
		_colorShape.setPosition(28, 643);


	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

bool HUDController::input(InputHandler &input)
{
	(void)input;
	return (false);
}

void HUDController::update(float delta)
{
	_delta += delta;
	_shot.update(delta);
}

void HUDController::draw(sf::RenderWindow &window)
{
	window.draw(_shape);
	window.draw(_health);
	window.draw(_colorShape);
	window.draw(_shot);
}

void HUDController::recycle(void)
{
	_health.recycle();
}

void HUDController::setHealth(uint8_t life)
{
	_health.setHealth(life);
}

void HUDController::setColor(uint16_t color)
{
	switch (color)
	{
	case 1:
		_colorShape.setFillColor(sf::Color(0, 0, 180, 150));
		break;
	case 2:
		_colorShape.setFillColor(sf::Color(180, 0, 0, 150));
		break;
	case 3:
		_colorShape.setFillColor(sf::Color(255, 255, 102, 150));
		break;
	case 4:
		_colorShape.setFillColor(sf::Color(0, 204, 0, 150));
		break;
	default:
		break;
	}
}

void HUDController::setLoaded(float deltaLoadedShot)
{
	_shot.setLoadedShot(deltaLoadedShot);
}