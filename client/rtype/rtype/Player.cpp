#include "Player.hpp"
#include "IClient.hpp"
#include "APowerUp.hpp"

const uint8_t Player::FRAME_TOP = 0;
const uint8_t Player::FRAME_MID = 1;
const uint8_t Player::FRAME_BOT = 2;
const uint8_t Player::FRAME_EXP = 3;

#include "Zork.hpp"

Player::Player()
	: _delta(0.f),
	_deltaLastShoot(0),
	_client(NULL),
	_hud(NULL),
	_decrease(false),
	_powder(NULL),
	_loadedPowder(NULL)
{
	_targetFrame = 0;
	_currentFrame = FRAME_MID;
	setVelocity(150.f);
	_resolution = StaticTools::GetResolution();
	_loadedShot = false;
	_deltaLoadedShot = 0.f;
	_deltaInvincibleAnim = 0.f;
	_invincibleAnimState = false;
}

Player::~Player(void)
{
	if (_powder) {
		_powder->recycle();
	}
	if (_loadedPowder) {
		_loadedPowder->recycle();
	}
	for (auto it : _drawablePowerUps) {
		it->recycle();
	}
}

void Player::init(void)
{
	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(65, 38));
	setOrigin(32.5f, 19);

	try {
		initFrame();

		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("players");
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

	refreshInvincibility(delta);

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

void Player::destroy(IClient &client)
{
	(void)client;
}

void Player::setIClient(IClient *client)
{
	_client = client;
}

void Player::setHUD(HUDController *hud)
{
	_hud = hud;
	_hud->setHealth(getHealth());
}

void Player::collision(IClient *client, AEntity *other)
{
	if (!hasCollisioned()) {
	  if (other->getCollisionType() == COLLISION_PUP) {
		  other->setCollisionType(COLLISION_NONE);
		  client->write(std::make_shared<CMDCollision>(CollisionType::PowerUP, getID(), other->getID()));
	  }
	  else if (!isInvincible() && !other->isInvincible() && other->getID() > 29999) {
		  if (getCollisionType() != COLLISION_NONE
			  && other->getCollisionType() == COLLISION_FATAL) {

			sf::FloatRect const& r0 = getBoundingBox();
			sf::FloatRect const& r1 = other->getBoundingBox();

			setCollisioned(true);
			client->write(std::make_shared<CMDCollision>(CollisionType::Destruction, getID(), other->getID()));
			setCollisionType(COLLISION_NONE);
		  }
	  }
  }
}

void Player::applyCollision(CollisionType type, AEntity *other)
{
	switch (type)
	{
	case CollisionType::None:
		break;
	case CollisionType::Destruction:
		collisionDestruction();
		break;
	case CollisionType::PowerUP:
		collisionPowerUp(other);
		break;
	default:
		break;
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

		for (auto it : _drawablePowerUps) {
			it->attachToEntity(this);
		}
	}
}

void Player::shoot(Fire const& param)
{
	if (_loadedPowder) {
		_loadedPowder->recycle();
		_loadedPowder = NULL;
	}

	ProjectResource::TheProjectResource.getSoundByKey("shot")->play();

	//MissileType type = param.type;
	uint16_t id = param.id;
	uint16_t id_launcher = param.id_launcher;
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t velocity = param.velocity;
	uint8_t angle = param.angle;
	//uint8_t effect = param.effect;

	StaticTools::DeserializePosition(param.position, x, y);

	Laser *laser = World::spawnEntity<Laser>();
	laser->setID(id);
	laser->setLevel(param.level);
	laser->setPosition(x, y);
	laser->setOwnerID(id_launcher);
	laser->setAngle(angle);
	laser->setVelocity(velocity);
	laser->setColor(id_launcher);
	laser->setReadyForInit(true);

	if (!_powder) {
		_powder = World::spawnEntity<Powdered>();
		_powder->setPosition(getPosition().x + 35, y + 2.f);
		_powder->setColor(getID());
		_powder->setReadyForInit(true);
	}
}

void Player::respawn(void)
{
	setCollisioned(false);
	setCollisionType(COLLISION_FATAL);
	_invincibleDelay = 3.;
	_currentDirection = FRAME_MID;
	_currentFrame = 0;
	_targetFrame = 0;
	setVisiblity(VISIBILITY_VISIBLE);
	setDead(false);
	setVelocity(150);
	_delta = 0;
	_deltaLastShoot = 0;
	_deltaLoadedShot = 0;
	_deltaInvincibleAnim = 0.f;
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
				sendRespawnRequest();
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
		setOrigin(r.width / 2.f, r.height / 2.f);
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

	if (_hud) {
		_hud->setLoaded(_deltaLoadedShot);
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

		prepareShot();
		_loadedShot = false;
		_deltaLoadedShot = 0;
	}

	//static bool t = false;
	//if (input.isKeyDown(sf::Keyboard::A) && !t) {
	//	t = true;
	//	Zork *zork = World::spawnEntity<Zork>();
	//	zork->setPosition(getPosition());
	//	zork->setVelocity(150);
	//	zork->setAngle(180);
	//	zork->setReadyForInit(true);
	//}
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
		direction |= WEAST;

	}
	else if (input.getJoystickAxis(0, sf::Joystick::X) > InputHandler::JOYSTICK_DEAD_ZONE) {
		direction |= EAST;
		_targetFrame = 3;
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

	if (_hud) {
		_hud->setLoaded(_deltaLoadedShot);
	}

	if (!_loadedShot && input.isJoystickButtonDown(0)) {
		_deltaLoadedShot = 0;
		_loadedShot = true;
	}
	else if (_loadedShot && !input.isJoystickButtonDown(0)) {
		if (_loadedPowder) {
			_loadedPowder->recycle();
			_loadedPowder = NULL;
		}

		prepareShot();
		_loadedShot = false;
		_deltaLoadedShot = 0;
	}
}


void Player::prepareShot(void)
{
	if (_deltaLastShoot > 0.25f) {
		sf::Vector2f size;
		sf::Vector2f pos = getPosition();

		Laser *shot = new Laser;
		shot->setLoadedTiming(_deltaLoadedShot);
		shot->setAngle(0);
		shot->setColor(getID());
		shot->setOwnerID(getID());

		size = shot->getSpriteSize();
		shot->setPosition(pos.x + 45 + size.x / 2.f, pos.y);

		shot->setReadyForInit(true);

		if (_client) {
			bool fired = false;
			for (auto it : _drawablePowerUps) {
				fired = it->fire(_client, getID(), sf::Vector2i((int)shot->getPosition().x, (int)pos.y), (int)shot->getVelocity(), (int)shot->getAngle(), shot->getLevel());
			}
			if (!fired) {
				_client->write(std::make_shared<CMDFire>(MissileType::MT_FriendFire_Lv1, 0, getID(),
					(int)shot->getPosition().x, (int)pos.y, (int)shot->getVelocity(), (int)shot->getAngle(), 0, shot->getLevel()));
			}
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

void Player::collisionDestruction(void)
{
	setCollisioned(true);
	setCollisionType(COLLISION_NONE);

	Explosion *explosion = World::spawnEntity<Explosion>();
	explosion->setPosition(getPosition());
	explosion->setReadyForInit(true);

	_currentDirection = FRAME_EXP;
	_currentFrame = 0;
	_targetFrame = 5;

	setAngle(-1);
	setVelocity(0);

	for (auto it : _drawablePowerUps) {
		it->recycle();
	}
	_drawablePowerUps.clear();

	if (_loadedPowder) {
		_loadedPowder->recycle();
		_loadedPowder = NULL;
	}

	setHealth(getHealth() - 1);
	_hud->setHealth(getHealth());
}

void Player::collisionPowerUp(AEntity *other)
{
	APowerUp *powerUp = dynamic_cast<APowerUp *>(other);
	if (other) {
		other->setCollisionType(COLLISION_NONE);
		powerUp->attachToEntity(this);
		_drawablePowerUps.push_back(powerUp);
	}
}

void Player::sendRespawnRequest(void)
{
	if (_client) {
		_client->write(std::make_shared<CMDDestroyed>(getID()));
	}
}


void Player::refreshInvincibility(float delta)
{
	sf::Color const& color = getShape()->getFillColor();

	if (isInvincible()) {
		_invincibleDelay -= delta;
		_deltaInvincibleAnim += delta;
		if (_deltaInvincibleAnim > 0.1f) {
			if (_invincibleAnimState) {
				getShape()->setFillColor(sf::Color(color.r, color.g, color.b, 255));
				_invincibleAnimState = false;
			}
			else {
				getShape()->setFillColor(sf::Color(color.r, color.g, color.b, 64));
				_invincibleAnimState = true;
			}
			_deltaInvincibleAnim = 0.f;
		}
	}
	else {
		getShape()->setFillColor(sf::Color(color.r, color.g, color.b, 255));
	}
}