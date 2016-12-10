#include "Player.hpp"
#include "IClient.hpp"

Player::Player()
	: _delta(0.f),
	_deltaLastShoot(0),
	_client(NULL),
	_decrease(false),
	_powder(NULL),
	_loadedPowder(NULL)
{
	_targetFrame = 0;
	_currentFrame = FRAME_MID;
	setVelocity(150.f);
	_resolution = StaticTools::GetResolution();
	_loadedShot = false;
	_deltaLoadedShot = 0;
}

Player::~Player(void)
{
	if (_powder) {
		_powder->recycle();
	}
	if (_loadedPowder) {
		_loadedPowder->recycle();
	}
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

	if (_loadedShot) {
		_deltaLoadedShot += delta;
	}

	if (_powder && _powder->isAnimationFinished()) {
		_powder->recycle();
		_powder = NULL;
	}

	updateFrame();
	APC::update(delta);
}

void Player::destroy(void)
{
	Explosion *explosion = World::spawnEntity<Explosion>();
	explosion->setPosition(getPosition());
	explosion->setReadyForInit(true);

	_currentDirection = FRAME_EXP;
	_currentFrame = 0;
	_targetFrame = 5;

	setAngle(-1);
	setVelocity(0);

	if (_loadedPowder) {
		_loadedPowder->recycle();
		_loadedPowder = NULL;
	}
}

void Player::setIClient(IClient *client)
{
	_client = client;
}

void Player::collision(IClient *client, AEntity *other)
{
  (void)client;
  if (getCollisionType() != COLLISION_NONE
	  && other->getCollisionType() == COLLISION_FATAL
	  && !hasCollisioned()) {

		setCollisioned(true);

		//if (!other->hasCollisioned() && _client) {
		//	other->collision(client, this);
			_client->write(std::make_shared<CMDCollision>(CollisionType::Destruction, getID(), other->getID()));
		//}

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
		if (_powder) {
			_powder->setPosition(pos.x + 35, pos.y + 2);
		}
		if (_loadedPowder) {
			_loadedPowder->setPosition(getPosition().x + 48, getPosition().y + 3);
		}
	}
}

void Player::shoot(Fire const& param)
{
	if (_loadedPowder) {
		_loadedPowder->recycle();
		_loadedPowder = NULL;
	}

	std::cout << "spawning shot with id " << (int)param.id << std::endl;

	LevelResource::TheLevelResource.getSoundByKey("shot")->play();

	MissileType type = param.type;
	uint8_t id = param.id;
	uint8_t id_launcher = param.id_launcher;
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t velocity = param.velocity;
	uint8_t angle = param.angle;
	uint8_t effect = param.effect;

	StaticTools::DeserializePosition(param.position, x, y);

	Laser *laser = World::spawnEntity<Laser>();
	//Laser *laser = new Laser;
	laser->setID(id);
	laser->setLevel(param.level);
	laser->setPosition(x, y);
	laser->setOwnerID(id_launcher);
	laser->setAngle(angle);
	laser->setVelocity(velocity);
	laser->setColor(id_launcher);
	laser->setReadyForInit(true);

	//World::pushEntity(laser);

	if (!_powder) {
		_powder = World::spawnEntity<Powdered>();
		_powder->setPosition(getPosition().x + 35, y + 2.f);
		_powder->setColor(getID());
		_powder->setReadyForInit(true);
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

	if (_deltaLoadedShot > 0.2f && !_loadedPowder) {
		_loadedPowder = World::spawnEntity<LoadedPowdered>();
		_loadedPowder->setPosition(getPosition().x + 48, getPosition().y + 3);
		_loadedPowder->setColor(getID());
		_loadedPowder->setReadyForInit(true);
		if (_client) {
			_client->write(std::make_shared<CMDPowder>(getID(), PowderType::LoadedPowder));
		}
	}

	if (!_loadedShot && input.isKeyDown(sf::Keyboard::Space)) {
		_deltaLoadedShot = 0;
		_loadedShot = true;
	}
	else if (_loadedShot && !input.isKeyDown(sf::Keyboard::Space)) {
		if (_loadedPowder) {
			_loadedPowder->recycle();
			_loadedPowder = NULL;
		}

		//Fire fire;
		//fire.type = MissileType::MT_FriendFire_Lv1;
		//shoot(fire);
		prepareShot();
		_loadedShot = false;
		_deltaLoadedShot = 0;
	}
}

void Player::joystick(InputHandler &input)
{
	_currentDirection = FRAME_MID;
	uint8_t direction = 0;

	if (input.getJoystickAxis(0, sf::Joystick::Y) < -InputHandler::JOYSTICK_DEAD_ZONE) {
		direction |= NORTH;
	}
	else if (input.getJoystickAxis(0, sf::Joystick::Y) > InputHandler::JOYSTICK_DEAD_ZONE)
	{
		direction |= SOUTH;
	}

	if (input.getJoystickAxis(0, sf::Joystick::X) < -InputHandler::JOYSTICK_DEAD_ZONE) {
		direction |= EAST;
		_targetFrame = 3;
	}
	else if (input.getJoystickAxis(0, sf::Joystick::X) > InputHandler::JOYSTICK_DEAD_ZONE) {
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

	if (input.isJoystickButtonDown(0)) {
		/*Fire fire;
		fire.type = MissileType::MT_FriendFire_Lv1;
		shoot(fire);*/
		prepareShot();
	}
}


void Player::prepareShot(void)
{
	if (_deltaLastShoot > 0.25f) {
		sf::Vector2f size;
		sf::Vector2f pos = getPosition();

		//Laser *shot = World::spawnEntity<Laser>();
		Laser *shot = new Laser;
		shot->setLoadedTiming(_deltaLoadedShot);
		shot->setAngle(0);
		shot->setColor(getID());
		shot->setOwnerID(getID());

		size = shot->getSpriteSize();
		shot->setPosition(pos.x + 45 + size.x / 2.f, pos.y);

		shot->setReadyForInit(true);

		if (_client) {
			_client->write(std::make_shared<CMDFire>(MissileType::MT_FriendFire_Lv1, 0, getID(),
				(int)shot->getPosition().x, (int)pos.y, (int)shot->getVelocity(), (int)shot->getAngle(), 0, shot->getLevel()));
		}
		delete (shot);

		if (!_powder) {
			_powder = World::spawnEntity<Powdered>();
			_powder->setPosition(pos.x + 35.f, pos.y + 2.f);
			_powder->setColor(getID());
			_powder->setReadyForInit(true);
		}

		_deltaLastShoot = 0.f;
	}
}