#include "Ravid.hpp"

const float Ravid::COEF_RESIZE = 1.3f;

Ravid::Ravid(void)
{
	_delta = 0;
	_currentFrame = 0;
	_deltaInvincibleAnim = 0.f;
	_invincibleAnimState = false;
	initFrame();
	_animState = AnimationState::Forward;
}

Ravid::~Ravid(void)
{
}

void Ravid::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(66 * COEF_RESIZE, 98 * COEF_RESIZE));
	setOrigin((66 * COEF_RESIZE) / 2.f, (98 * COEF_RESIZE) / 2.f);

	try {
		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("ravid");
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		sf::IntRect const& rect = _frames.at(0);
		getShape()->setTextureRect(rect);
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
		std::cout << e.what() << std::endl;
	}
}

void Ravid::update(float delta)
{
	_delta += delta;

	updateFrame();
	refreshInvincibility(delta);
	ANPC::update(delta);
}

void Ravid::destroy(IClient &client)
{
	client.write(std::make_shared<CMDDestroyed>(getID()));
}

void Ravid::collision(IClient *client, AEntity *other)
{
	(void)client;
	if (!isInvincible() && !hasCollisioned() && !other->isInvincible()
		&& other->getID() < 29999) {

		if (getCollisionType() != COLLISION_NONE
			&& (other->getCollisionType() == COLLISION_FATAL || other->getCollisionType() == COLLISION_MISSILE)) {

			setCollisioned(true);
			other->collision(client, this);
			setCollisionType(COLLISION_NONE);
		}
	}
}

void Ravid::applyCollision(CollisionType type, AEntity *other)
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

void Ravid::move(float delta)
{
	if (getAngle() != -1) {
		float x = std::cos(getRadians()) * getVelocity() * delta;
		float y = std::sin(getRadians()) * getVelocity() * delta;

		ADrawable::move(x, y);
	}
}

void Ravid::shoot(Fire const& param)
{
	ProjectResource::TheProjectResource.getSoundByKey("shot")->setVolume(StaticTools::soundVolume);
	ProjectResource::TheProjectResource.getSoundByKey("shot")->play();

	uint16_t id = param.id;
	uint16_t id_launcher = param.id_launcher;
	uint16_t x = 0;
	uint16_t y = 0;
	uint8_t velocity = param.velocity;
	float angle = param.angle;

	StaticTools::DeserializePosition(param.position, x, y);

	FireBall *laser = World::spawnEntity<FireBall>();
	laser->setID(id);
	laser->setLevel(param.level);
	laser->setPosition(x, y);
	laser->setOwnerID(id_launcher);
	laser->setAngle(angle);
	laser->setVelocity(velocity);
	laser->setReadyForInit(true);
}

void Ravid::respawn(void)
{
}

sf::IntRect const& Ravid::getFrame(size_t idx) const
{
	return (_frames.at(idx));
}

void Ravid::setPowder(PowderType powderType)
{
	(void)powderType;
}

void Ravid::initFrame(void)
{
	_frames.emplace_back(0, 17, 66, 98);
	_frames.emplace_back(69, 10, 58, 112);
	_frames.emplace_back(136, 3, 54, 126);
	_frames.emplace_back(195, 0, 66, 132);
}

void Ravid::updateFrame(void)
{
	if (_delta > 0.1f) {

		if (_animState == AnimationState::Forward) {
			++_currentFrame;
			if (_currentFrame == _frames.size()) {
				_currentFrame = _frames.size() - 2;
				_animState = AnimationState::Backward;
			}
		}
		else {
			if (_currentFrame > 0) {
				--_currentFrame;
			}
			else {
				_currentFrame = 1;
				_animState = AnimationState::Forward;
			}
		}

		sf::IntRect const& r = _frames.at(_currentFrame);
		_shape->setSize(sf::Vector2f(r.width * COEF_RESIZE, r.height * COEF_RESIZE));
		setOrigin((r.width * COEF_RESIZE) / 2.f, (r.height * COEF_RESIZE) / 2.f);
		getShape()->setTextureRect(sf::IntRect(r.left, r.top, r.width, r.height));
		_delta = 0.f;
	}
}

void Ravid::collisionDestruction(void)
{
	sf::Vector2f const& pos = getPosition();

	setCollisioned(true);
	setCollisionType(COLLISION_NONE);

	if (getHealth() == 1) {

		Explosion *explosion0 = World::spawnEntity<Explosion>();
		explosion0->setPosition(pos.x - 10, pos.y - 20);
		explosion0->setReadyForInit(true);

		Explosion *explosion1 = World::spawnEntity<Explosion>();
		explosion1->setPosition(pos.x + 5, pos.y);
		explosion1->setReadyForInit(true);

		Explosion *explosion2 = World::spawnEntity<Explosion>();
		explosion2->setPosition(pos.x, pos.y + 20);
		explosion2->setReadyForInit(true);

		recycle();
	}
	else {
		Explosion *explosion = World::spawnEntity<Explosion>();
		explosion->setPosition(pos);
		explosion->setReadyForInit(true);

		setHealth(getHealth() - 1);
		setCollisioned(false);
		setCollisionType(COLLISION_FATAL);
		_invincibleDelay = 2;
	}
}

void Ravid::refreshInvincibility(float delta)
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