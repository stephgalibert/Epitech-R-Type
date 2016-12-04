#include "Player.hpp"
#include "IClient.hpp"

Player::Player()
	: _delta(0.f),
	_client(NULL)
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

void Player::update(float delta)
{
	APC::update(delta);
}

void Player::destroy(void)
{
}

void Player::setIClient(IClient *client)
{
	_client = client;
}

void Player::input(InputHandler &input)
{
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
	uint8_t direction = 0;

	if (input.isKeyDown(sf::Keyboard::Key::Up)) {
		direction |= NORTH;
		setTargetFrame(4);
	}
	else if (input.isKeyDown(sf::Keyboard::Key::Down)) {
		direction |= SOUTH;
		setTargetFrame(0);
	}

	if (input.isKeyDown(sf::Keyboard::Key::Right)) {
		direction |= EAST;
	}
	else if (input.isKeyDown(sf::Keyboard::Key::Left)) {
		direction |= WEAST;
	}

	if (getDirection() != direction) {
		_client->write(std::make_shared<CMDMove>(getID(), direction, (uint8_t)getVelocity()));
	}
	setDirection(direction);

	if (input.isKeyDown(sf::Keyboard::Space)) {
		shoot();
	}
}

void Player::joystick(InputHandler &input)
{
	uint8_t direction = 0;

	if (input.getJoystickAxis(0, sf::Joystick::Y) < -InputHandler::JOYSTICK_DEAD_ZONE) {
		direction |= NORTH;
		setTargetFrame(4);
	}
	else if (input.getJoystickAxis(0, sf::Joystick::Y) > InputHandler::JOYSTICK_DEAD_ZONE)
	{
		direction |= SOUTH;
		setTargetFrame(0);
	}

	if (input.getJoystickAxis(0, sf::Joystick::X) < -InputHandler::JOYSTICK_DEAD_ZONE) {
		direction |= EAST;
	}
	else if (input.getJoystickAxis(0, sf::Joystick::X) > InputHandler::JOYSTICK_DEAD_ZONE) {
		direction |= WEAST;
	}

	if (input.isJoystickButtonDown(0)) {
		shoot();
	}
}