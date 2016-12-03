#include "Player.hpp"

Player::Player()
{
	setTargetFrame(2);
	setCurrentFrame(2);
	setVelocity(150.f);
}

Player::~Player(void)
{
}

void Player::init(void)
{
	_init = true;
	setOrigin(17, 8);
	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(34, 16));
	setPosition(20, 80);

	try {
		sf::Texture *texture = LevelResource::TheLevelResource.getTextureByKey("players");

		texture->setSmooth(true);
		shape->setTextureRect(sf::IntRect(1, (getID() - 1) * 18, 33, 16));

		setShape(shape);
		setTexture(texture);
	}
	catch (std::exception const& e) {
		delete (shape);
		StaticTools::Log << e.what() << std::endl;
	}
}

void Player::destroy(void)
{
}

void Player::input(InputHandler &input)
{
	setAngle(-1);
	setTargetFrame(2);

	if (input.isJoystickPresent()) {
		joystick(input);
	}
	else {
		keyboard(input);
	}
}

void Player::keyboard(InputHandler &input)
{
	if (input.isKeyDown(sf::Keyboard::Key::Up)) {
		setAngle(-90.f);
		setTargetFrame(4);
	}
	else if (input.isKeyDown(sf::Keyboard::Key::Down)) {
		setAngle(90.f);
		setTargetFrame(0);
	}

	if (input.isKeyDown(sf::Keyboard::Key::Right)) {
		setAngle(getAngle() / 2.f);
	}
	else if (input.isKeyDown(sf::Keyboard::Key::Left)) {
		setAngle(-180.f - getAngle() / 2.f);
	}

	if (input.isKeyDown(sf::Keyboard::Space)) {
		shoot();
	}
}

void Player::joystick(InputHandler &input)
{
	if (input.getJoystickAxis(0, sf::Joystick::Y) < -InputHandler::JOYSTICK_DEAD_ZONE) {
		setAngle(-90.f);
		setTargetFrame(4);
	}
	else if (input.getJoystickAxis(0, sf::Joystick::Y) > InputHandler::JOYSTICK_DEAD_ZONE)
	{
		setAngle(90.f);
		setTargetFrame(0);
	}

	if (input.getJoystickAxis(0, sf::Joystick::X) < -InputHandler::JOYSTICK_DEAD_ZONE) {
		setAngle(-180.f - getAngle() / 2.f);
	}
	else if (input.getJoystickAxis(0, sf::Joystick::X) > InputHandler::JOYSTICK_DEAD_ZONE) {
		setAngle(getAngle() / 2.f);
	}

	if (input.isJoystickButtonDown(0)) {
		shoot();
	}
}