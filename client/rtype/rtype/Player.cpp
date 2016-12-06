#include "Player.hpp"
#include "IClient.hpp"

Player::Player()
	: _delta(0.f),
	_deltaLastShoot(0),
	_client(NULL),
	_decrease(false)
{
	_targetFrame = 0;
	_currentFrame = FRAME_MID;
	//_currentSmoke = 2;
	setVelocity(150.f);
	_resolution = StaticTools::GetResolution();
}

Player::~Player(void)
{
}

void Player::init(void)
{
	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(65, 38));
	setOrigin(32.5f, 19);

	try {
		initFrame();

		sf::Texture *texture = LevelResource::TheLevelResource.getTextureByKey("players");
		texture->setSmooth(true);

		setShape(shape);
		setTexture(texture);

		sf::IntRect const& rect = _frames.at(FRAME_MID);
		getShape()->setTextureRect(rect);
	}
	catch (std::exception const& e) {
		throw (std::runtime_error(e.what()));
	}
}

void Player::update(float delta)
{
	if (isDead()) {
		return;
	}

	_delta += delta;
	_deltaLastShoot += delta;

	updateFrame();
	APC::update(delta);
}

void Player::destroy(void)
{
}

void Player::setIClient(IClient *client)
{
	_client = client;
}

void Player::collision(IClient *client, ACollidable *other)
{
  (void)client;
	if (getCollisionType() != COLLISION_NONE
		&& other->getCollisionType() == COLLISION_FATAL
		&& _currentDirection != FRAME_EXP) {

		Explosion *explosion = World::TheWorld.spawnEntity<Explosion>();
		explosion->setPosition(getPosition());
		explosion->setReadyForInit(true);

		_currentDirection = FRAME_EXP;
		_currentFrame = 0;
		_targetFrame = 5;

		setAngle(-1);
		setVelocity(0);

		other->collision(client, this);
		setCollisionType(COLLISION_NONE);
	}
}

void Player::input(InputHandler &input)
{
	if (isDead() || _currentDirection == FRAME_EXP) {
		return;
	}

	_targetFrame = 0;
	if (input.isJoystickPresent()) {
		joystick(input);
	}
	else {
		keyboard(input);
	}
}

void Player::move(float delta)
{
	if (getAngle() != -1) {
		sf::Vector2f const& pos = getPosition();

		float x = std::cos(getRadians()) * getVelocity() * delta;
		float y = std::sin(getRadians()) * getVelocity() * delta;

		if (pos.x + x < 0 || pos.x + x > _resolution.first) {
			x = 0;
		}
		if (pos.y + y < 0 || pos.y + y > _resolution.second) {
			y = 0;
		}

		ADrawable::move(x, y);
	}
}

void Player::shoot(void)
{
	if (_deltaLastShoot > 0.25f) {
		LevelResource::TheLevelResource.getSoundByKey("shot")->play();
		sf::Vector2f const& pos = getPosition();

		Laser *shot = World::TheWorld.spawnEntity<Laser>();
		shot->setPosition(pos.x + 50, pos.y);
		shot->setAngle(0);
		shot->setColor(getID());
		shot->setOwnerID(getID());
		shot->setReadyForInit(true);
		//_currentSmoke = 0;
		_deltaLastShoot = 0.f;

		if (_client) {
			_client->write(std::make_shared<CMDFire>(MissileType::MT_FriendFire_Lv1, getID(),
				(int)pos.x + 50, (int)pos.y, (int)shot->getVelocity(), (int)shot->getAngle(), 0));
		}
	}
}

void Player::initFrame(void)
{
	switch (getID())
	{
	case 1:
		_frames[FRAME_TOP] = sf::IntRect(0, 302, 64, 38);
		_frames[FRAME_MID] = sf::IntRect(0, 340, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 377, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 415, 64, 38);
		break;
	case 2:
		_frames[FRAME_TOP] = sf::IntRect(0, 152, 64, 37);
		_frames[FRAME_MID] = sf::IntRect(0, 189, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 226, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 264, 64, 38);
		break;
	case 3:
		_frames[FRAME_TOP] = sf::IntRect(0, 2, 64, 37);
		_frames[FRAME_MID] = sf::IntRect(0, 39, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 76, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 114, 64, 38);
		break;
	case 4:
		_frames[FRAME_TOP] = sf::IntRect(0, 453, 64, 37);
		_frames[FRAME_MID] = sf::IntRect(0, 490, 64, 37);
		_frames[FRAME_BOT] = sf::IntRect(0, 527, 64, 38);
		_frames[FRAME_EXP] = sf::IntRect(0, 565, 64, 38);
		break;
	default:
		break;
	}

	//_smoke[0] = sf::IntRect(233, 86, 12, 12);
	//_smoke[1] = sf::IntRect(215, 84, 16, 14);
}

void Player::updateFrame(void)
{
	if (_delta > 0.08f) {

		if (_currentDirection == FRAME_EXP) {
			if (_currentFrame == 5) {
				setDead(true);
				setVisiblity(VISIBILITY_GONE);
				return;
			}
		}

		if (_currentFrame != _targetFrame) {
			if (_currentFrame < _targetFrame) {
				++_currentFrame;
			}
			else if (_currentFrame > _targetFrame) {
				--_currentFrame;
			}
		}
		if (_currentDirection != FRAME_EXP && _currentFrame == 3) {
			if (_decrease) {
				--_currentFrame;
				_decrease = false;
			}
			else {
				_decrease = true;
			}
		}
		else if (_currentDirection != FRAME_EXP &&  _currentFrame == 0) {
			if (_decrease) {
				++_currentFrame;
				_decrease = false;
			}
			else {
				_decrease = true;
			}
		}

		sf::IntRect const& r = _frames.at(_currentDirection);
		getShape()->setTextureRect(sf::IntRect(_currentFrame * r.width, r.top, r.width, r.height));
		_delta = 0.f;
	}
}

void Player::keyboard(InputHandler &input)
{
	_currentDirection = FRAME_MID;
	uint8_t direction = 0;

	if (input.isKeyDown(sf::Keyboard::Key::Up)) {
		direction |= NORTH;
	}
	else if (input.isKeyDown(sf::Keyboard::Key::Down)) {
		direction |= SOUTH;
	}

	if (input.isKeyDown(sf::Keyboard::Key::Right)) {
		direction |= EAST;
		_targetFrame = 3;
	}
	else if (input.isKeyDown(sf::Keyboard::Key::Left)) {
		direction |= WEAST;
	}

	if (getDirection() != direction) {
		sf::Vector2f const& pos = getPosition();
		_client->write(std::make_shared<CMDMove>(getID(), (uint16_t)pos.x, (uint16_t)pos.y,
			(uint16_t)getVelocity(), direction));
		setDirection(direction);
	}

	if (direction & NORTH && direction & EAST) {
		_currentDirection = FRAME_TOP;
	}
	else if (direction & SOUTH && direction & EAST) {
		_currentDirection = FRAME_BOT;
	}
	else if (direction == NORTH) {
		_currentDirection = FRAME_TOP;
	}
	else if (direction == SOUTH) {
		_currentDirection = FRAME_BOT;
	}

	if (input.isKeyDown(sf::Keyboard::Space)) {
		shoot();
	}
}

void Player::joystick(InputHandler &input)
{
	// to update
	//uint8_t direction = 0;

	//if (input.getJoystickAxis(0, sf::Joystick::Y) < -InputHandler::JOYSTICK_DEAD_ZONE) {
	//	direction |= NORTH;
	//	_targetFrame = 4; // !
	//}
	//else if (input.getJoystickAxis(0, sf::Joystick::Y) > InputHandler::JOYSTICK_DEAD_ZONE)
	//{
	//	direction |= SOUTH;
	//	_targetFrame = 0; // !
	//}

	//if (input.getJoystickAxis(0, sf::Joystick::X) < -InputHandler::JOYSTICK_DEAD_ZONE) {
	//	direction |= EAST;
	//}
	//else if (input.getJoystickAxis(0, sf::Joystick::X) > InputHandler::JOYSTICK_DEAD_ZONE) {
	//	direction |= WEAST;
	//}

	//if (input.isJoystickButtonDown(0)) {
	//	shoot();
	//}
}