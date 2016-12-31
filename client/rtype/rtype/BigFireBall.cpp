#include "BigFireBall.hpp"

BigFireBall::BigFireBall(void)
{
	setCollisionType(COLLISION_MISSILE);
	setVelocity(230.f);
	initFrame();
	_delta = 0;
}

BigFireBall::~BigFireBall(void)
{
}

void BigFireBall::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(18, 18));
	setOrigin(9, 9);

	try {
		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("powerups1");
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		getShape()->setTextureRect(_frames.at(_currentFrame));
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void BigFireBall::update(float delta)
{
	_delta += delta;

	updateFrame();
	AProjectile::update(delta);
}

void BigFireBall::destroy(IClient &client)
{
	client.write(std::make_shared<CMDDestroyed>(getID()));
}

void BigFireBall::collision(IClient *client, AEntity *other)
{
	(void)client;
	if (!other->isInvincible() && !hasCollisioned()
		&& other->getID() > 0 && other->getID() < 29999
		&& other->getCollisionType() == COLLISION_FATAL) {

		setCollisioned(true);
		recycle();
	}
}

void BigFireBall::applyCollision(CollisionType type, AEntity *other)
{
	(void)other;
	switch (type)
	{
	case CollisionType::None:
		break;
	case CollisionType::Destruction:
		recycle();
		break;
	case CollisionType::PowerUP:
		break;
	default:
		break;
	}
}

void BigFireBall::updateFrame(void)
{
	if (_shape && _delta > 0.08f) {

		++_currentFrame;
		if (_currentFrame == _frames.size()) {
			_currentFrame = 0;
		}

		sf::IntRect const& rect = _frames.at(_currentFrame);
		setOrigin(rect.width / 2.f, rect.height / 2.f);
		_shape->setSize(sf::Vector2f((float)rect.width, (float)rect.height));
		_shape->setTextureRect(rect);

		_delta = 0;
	}
}

void BigFireBall::initFrame(void)
{
	_frames.emplace_back(228, 451, 18, 18);
	_frames.emplace_back(246, 451, 18, 18);
	_frames.emplace_back(264, 451, 18, 18);
	_frames.emplace_back(282, 451, 18, 18);

	_currentFrame = 0;
}
