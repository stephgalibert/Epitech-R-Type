#include "Player.hpp"

Player::Player()
{
	_delta = 0.f;	
	_targetFrame = 2;
	_currentFrame = 2;

	setVelocity(3.f);
}

Player::~Player(void)
{
}

void Player::init(void)
{
	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(34, 16));
	shape->setPosition(sf::Vector2f(20, 80));

	try {
		sf::Texture *texture = LevelResource::TheLevelResource.getTextureByKey("players");

		texture->setSmooth(true);
		shape->setTextureRect(sf::IntRect(1, 0, 33, 16));

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
	_delta += delta;

	updateFrame();
	move();
}

void Player::destroy(void)
{
}

void Player::updateFrame(void)
{
	if (_delta > 0.1) {
		if (_currentFrame != _targetFrame) {
			if (_currentFrame < _targetFrame) {
				++_currentFrame;
			}
			else if (_currentFrame > _targetFrame) {
				--_currentFrame;
			}
		}
		getShape()->setTextureRect(sf::IntRect(_currentFrame * 33 + 1, 0, 33, 16));
		_delta = 0;
	}
}

void Player::input(InputHandler &input)
{
	setAngle(-1);

	_targetFrame = 2;

	if (input.isKeyDown(sf::Keyboard::Key::Up)) {
		setAngle(-90.f);
		_targetFrame = 4;
	}
	else if (input.isKeyDown(sf::Keyboard::Key::Down)) {
		setAngle(90.f);
		_targetFrame = 0;
	}

	if (input.isKeyDown(sf::Keyboard::Key::Right)) {
		setAngle(getAngle() / 2.f);
	}
	else if (input.isKeyDown(sf::Keyboard::Key::Left)) {
		setAngle(-180.f - getAngle() / 2.f);
	}
}