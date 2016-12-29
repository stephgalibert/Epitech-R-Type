#include "DoubleLaser.hpp"
#include "Player.hpp"

const float DoubleLaser::COEF_RESIZE = 1.3f;

DoubleLaser::DoubleLaser(void)
	: _shape(NULL),
	_delta(0),
	_currentFrame(0)
{
	setCollisionType(COLLISION_MISSILE);
	setVelocity(230.f);
	initFrame();
}

DoubleLaser::~DoubleLaser(void)
{
}

void DoubleLaser::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(14 * COEF_RESIZE, 38 * COEF_RESIZE));
	setOrigin(7 * COEF_RESIZE, 19 * COEF_RESIZE);

	try {
		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("powerups1");
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		getShape()->setTextureRect(_frames.at(0));
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void DoubleLaser::update(float delta)
{
	_delta += delta;

	updateFrame();
	AProjectile::update(delta);
}

void DoubleLaser::destroy(IClient &client)
{
	client.write(std::make_shared<CMDDestroyed>(getID()));
}

void DoubleLaser::collision(IClient *client, AEntity *other)
{
	if (!other->isInvincible() && !hasCollisioned() && other->getID() > 4
		&& other->getCollisionType() == COLLISION_FATAL) {
		setCollisioned(true);

		if (getOwnerID() == World::GetPlayer()->getID()) {
			client->write(std::make_shared<CMDCollision>(CollisionType::Destruction, getID(), other->getID()));
		}
	}
}

void DoubleLaser::applyCollision(CollisionType type, AEntity *other)
{
	(void)other;
	if (!hasCollisioned())
		return;

	switch (type)
	{
	case CollisionType::None:
		break;
	case CollisionType::Destruction:
		setCollisioned(false);
		break;
	case CollisionType::PowerUP:
		break;
	default:
		break;
	}
}

void DoubleLaser::updateFrame(void)
{
	if (_shape && _delta > 0.03f) {
		++_currentFrame;
		if (_currentFrame == _frames.size()) {
			_currentFrame = 10;
		}

		sf::IntRect const& rect = _frames.at(_currentFrame);
		_shape->setSize(sf::Vector2f(rect.width * COEF_RESIZE, rect.height* COEF_RESIZE));
		_shape->setTextureRect(rect);
		setOrigin((rect.width * COEF_RESIZE) / 2.f, (rect.height * COEF_RESIZE) / 2.f);

		_delta = 0;
	}
}

void DoubleLaser::initFrame(void)
{
	// 53 551 - 14 38
	// 70 546 - 20 48
	// 103 542 - 29 56
	// 136 541 - 39 58
	// 185 541 - 49 58
	// 234 541 - 57 58
	// 39 607 - 63 58
	// 104 607 - 66 58
	// 171 607 - 62 58
	// 234 607 - 66 58
	_frames.emplace_back(53, 551, 14, 38);
	_frames.emplace_back(70, 546, 20, 48);
	_frames.emplace_back(103, 542, 29, 56);
	_frames.emplace_back(136, 541, 39, 58);
	_frames.emplace_back(185, 541, 49, 58);
	_frames.emplace_back(234, 541, 57, 58);
	_frames.emplace_back(39, 607, 63, 58);
	_frames.emplace_back(104, 607, 66, 58);
	_frames.emplace_back(171, 607, 62, 58);
	_frames.emplace_back(234, 607, 66, 58);

	_frames.emplace_back(36, 469, 66, 34);
	_frames.emplace_back(102, 469, 61, 34);
	_frames.emplace_back(168, 469, 61, 34);
	_frames.emplace_back(236, 469, 64, 34);
	_frames.emplace_back(36, 503, 66, 34);
	_frames.emplace_back(102, 503, 61, 34);
	_frames.emplace_back(168, 503, 61, 34);
	_frames.emplace_back(236, 503, 64, 34);

	_currentFrame = 0;
}