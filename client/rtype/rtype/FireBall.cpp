#include "FireBall.hpp"

FireBall::FireBall(void)
{
	setCollisionType(COLLISION_MISSILE);
	setVelocity(230.f);
	initFrame();
	_delta = 0;
}

FireBall::~FireBall(void)
{
}

void FireBall::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(18, 14));
	setOrigin(9, 7);

	try {
		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("e_shots1");
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		getShape()->setTextureRect(_frames.at(_currentFrame));
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void FireBall::update(float delta)
{
	_delta += delta;

	updateFrame();
	AProjectile::update(delta);
}

void FireBall::destroy(IClient &client)
{
	client.write(std::make_shared<CMDDestroyed>(getID()));
}

void FireBall::collision(IClient *client, AEntity *other)
{
  (void)client;
	if (!other->isInvincible() && !hasCollisioned()
		&& other->getID() > 0 && other->getID() < 29999
		&& other->getCollisionType() == COLLISION_FATAL) {

		setCollisioned(true);
		recycle();
	}
}

void FireBall::applyCollision(CollisionType type, AEntity *other)
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

void FireBall::updateFrame(void)
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

void FireBall::initFrame(void)
{
	if (_frames.size() == 0) {
		_frames.emplace_back(135, 5, 9, 8);
		_frames.emplace_back(152, 5, 9, 8);
		_frames.emplace_back(169, 5, 9, 8);
		_frames.emplace_back(187, 5, 9, 8);
	}
	_currentFrame = 0;
}
