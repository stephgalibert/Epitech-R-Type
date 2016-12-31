#include "RedMissile.hpp"
#include "World.hpp"

const float RedMissile::COEF_RESIZE = 1.f;

RedMissile::RedMissile(void)
{
	setCollisionType(COLLISION_FATAL);
	initFrame();
	_delta = 0;
	_deltaFall = 0;
}

RedMissile::~RedMissile(void)
{
}

void RedMissile::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(20 * COEF_RESIZE, 71 * COEF_RESIZE));
	setOrigin((20 * COEF_RESIZE) / 2, 0);

	try {
		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("missile1");
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		getShape()->setTextureRect(_frames.at(_currentFrame));
		setRotation(-90);
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void RedMissile::update(float delta)
{
	_delta += delta;

	updateFrame();
	AProjectile::update(delta);

	if (_currentFrame == _frames.size() - 1) {
		if (_deltaFall <= 3.f) {
			float angle = 180 - (_deltaFall / 3.f) * 90.f;
			setAngle(angle);
			setRotation(angle + 90.f);
		}
		_deltaFall += delta;
	}
}

void RedMissile::destroy(IClient &client)
{
	client.write(std::make_shared<CMDDestroyed>(getID()));
}

void RedMissile::collision(IClient *client, AEntity *other)
{
	(void)client;
	if (!other->isInvincible() && !hasCollisioned()
		&& other->getID() > 0 && other->getID() < 29999
		&& (other->getCollisionType() == COLLISION_FATAL || other->getCollisionType() == COLLISION_MISSILE)) {

		setCollisioned(true);

		Explosion *explosion = World::spawnEntity<Explosion>();
		explosion->setPosition(getPosition());
		explosion->setReadyForInit(true);
		recycle();
	}
}

void RedMissile::applyCollision(CollisionType type, AEntity *other)
{
	(void)other;
	switch (type)
	{
	case CollisionType::None:
		break;
	case CollisionType::Destruction:
		collisionDestruction();
		break;
	case CollisionType::PowerUP:
		break;
	default:
		break;
	}
}

void RedMissile::updateFrame(void)
{
	if (_shape && _delta > 0.08f) {

		if (_currentFrame < _frames.size() - 1) {
			++_currentFrame;
		}

		sf::IntRect const& rect = _frames.at(_currentFrame);
		setOrigin((rect.width * COEF_RESIZE) / 2.f, 0);
		_shape->setSize(sf::Vector2f((float)rect.width, (float)rect.height));
		_shape->setTextureRect(rect);

		_delta = 0;
	}
}

void RedMissile::initFrame(void)
{
	_frames.emplace_back(378, 0, 20, 71);
	_frames.emplace_back(355, 0, 20, 88);
	_frames.emplace_back(331, 0, 20, 88);
	_frames.emplace_back(308, 0, 20, 89);
	_frames.emplace_back(285, 0, 19, 89);
	_frames.emplace_back(260, 0, 21, 95);
	_frames.emplace_back(237, 0, 20, 96);
	_frames.emplace_back(213, 0, 21, 95);
	_frames.emplace_back(189, 0, 22, 96);
	_frames.emplace_back(165, 0, 22, 94);
	_frames.emplace_back(142, 0, 21, 92);
	_frames.emplace_back(120, 0, 20, 89);
	_frames.emplace_back(96, 0, 20, 88);
	_frames.emplace_back(73, 0, 20, 88);
	_frames.emplace_back(49, 0, 20, 88);
	_frames.emplace_back(26, 0, 20, 73);
	_frames.emplace_back(2, 0, 20, 45);

	_currentFrame = 0;
}

void RedMissile::collisionDestruction(void)
{
	
	recycle();
}