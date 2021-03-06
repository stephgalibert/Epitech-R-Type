#include "Laser.hpp"
#include "Player.hpp"

Laser::Laser(void)
	: _shape(NULL),
	_delta(0),
	_currentFrame(0),
	_color(1)
{
	setCollisionType(COLLISION_MISSILE);
	setVelocity(230.f);
	initFrame();
	_toRecycle = false;
}

Laser::~Laser(void)
{
}

void Laser::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(18, 14));
	_shape->setRotation(getAngle());
	setOrigin(9, 7);

	try {
		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("shots" + std::to_string(_color));
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		getShape()->setTextureRect(_frames.at(0)[0]);
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void Laser::update(float delta)
{
	_delta += delta;

	if (_toRecycle) {
		recycle();
	}

	updateFrame();
	AProjectile::update(delta);
}

void Laser::destroy(IClient &client)
{
	client.write(std::make_shared<CMDDestroyed>(getID()));
}

void Laser::collision(IClient *client, AEntity *other)
{
	if (!other->isInvincible() && !hasCollisioned() && other->getID() > 4
			&& other->getCollisionType() == COLLISION_FATAL) {
		setCollisioned(true);

		if (getOwnerID() == World::GetPlayer()->getID()) {
			client->write(std::make_shared<CMDCollision>(CollisionType::Destruction, getID(), other->getID()));
		}
	}
}

void Laser::applyCollision(CollisionType type, AEntity *other)
{
	(void)other;
	if (!hasCollisioned())
		return;

	switch (type)
	{
	case CollisionType::None:
		break;
	case CollisionType::Destruction:
		if (getLevel() > 0) {
			setLevel(getLevel() - 1);
			setCollisioned(false);
		}
		else {
			_toRecycle = true;
		}
		break;
	case CollisionType::PowerUP:
		break;
	default:
		break;
	}
}

void Laser::setColor(uint16_t color)
{
	_color = color;
}

void Laser::setLoadedTiming(float delta)
{
	setLevel(static_cast<uint8_t>(delta / 0.3f));
	if (getLevel() > 5) {
		setLevel(5);
	}
}

sf::Vector2f Laser::getSpriteSize(void) const
{
	sf::Vector2f size;

	sf::IntRect const& rect = _frames.at(getLevel())[0];
	size.x = (float)rect.width;
	size.y = (float)rect.height;

	return (size);
}

void Laser::updateFrame(void)
{
	if (_shape && _delta > 0.08f) {
		if (_currentFrame == 1) {
			_currentFrame = 0;
		}
		else {
			++_currentFrame;
		}

		sf::IntRect const& rect = _frames.at(getLevel())[_currentFrame];
		setOrigin(rect.width / 2.f, rect.height / 2.f);
		_shape->setSize(sf::Vector2f((float)rect.width, (float)rect.height));
		_shape->setTextureRect(rect);

		_delta = 0;
	}
}

void Laser::initFrame(void)
{
	if (_frames.size() == 0) {
		_frames[0][0] = sf::IntRect(248, 89, 15, 6);
		_frames[0][1] = sf::IntRect(248, 89, 15, 6);
		_frames[1][0] = sf::IntRect(231, 102, 18, 14);
		_frames[1][1] = sf::IntRect(249, 104, 18, 10);
		_frames[2][0] = sf::IntRect(199, 120, 34, 12);
		_frames[2][1] = sf::IntRect(232, 119, 34, 14);
		_frames[3][0] = sf::IntRect(167, 136, 50, 14);
		_frames[3][1] = sf::IntRect(216, 135, 50, 16);
		_frames[4][0] = sf::IntRect(135, 153, 66, 16);
		_frames[4][1] = sf::IntRect(200, 153, 66, 16);
		_frames[5][0] = sf::IntRect(103, 170, 82, 16);
		_frames[5][1] = sf::IntRect(184, 169, 82, 18);
	}
	_currentFrame = 0;
}