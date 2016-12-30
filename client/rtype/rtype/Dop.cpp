#include "Dop.hpp"

const float Dop::COEF_RESIZE = 1.3f;

Dop::Dop(void)
{
	_delta = 0;
	_currentFrame = 0;
	_deltaInvincibleAnim = 0.f;
	_invincibleAnimState = false;
	initFrame();
}

Dop::~Dop(void)
{
}

void Dop::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(65 * COEF_RESIZE, 50 * COEF_RESIZE));
	setOrigin((65 * COEF_RESIZE) / 2.f, (50 * COEF_RESIZE) / 2.f);

	try {
		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("dop");
		texture->setSmooth(true);

		setShape(_shape);
		setTexture(texture);

		sf::IntRect const& rect = _frames.at(0);
		getShape()->setTextureRect(rect);
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void Dop::update(float delta)
{
	_delta += delta;

	updateFrame();
	refreshInvincibility(delta);
	ANPC::update(delta);
}

void Dop::destroy(IClient &client)
{
	client.write(std::make_shared<CMDDestroyed>(getID()));
}

void Dop::collision(IClient *client, AEntity *other)
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

void Dop::applyCollision(CollisionType type, AEntity *other)
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

void Dop::move(float delta)
{
	if (getAngle() != -1) {
		float x = std::cos(getRadians()) * getVelocity() * delta;
		float y = std::sin(getRadians()) * getVelocity() * delta;

		ADrawable::move(x, y);
	}
}

void Dop::shoot(Fire const& param)
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

void Dop::respawn(void)
{
}

sf::IntRect const& Dop::getFrame(size_t idx) const
{
	return (_frames.at(idx));
}

void Dop::setPowder(PowderType powderType)
{
	(void)powderType;
}

void Dop::initFrame(void)
{
	_frames.emplace_back(0, 0, 65, 50);
	_frames.emplace_back(65, 0, 65, 50);
	_frames.emplace_back(130, 0, 65, 50);
}

void Dop::updateFrame(void)
{
	if (_delta > 0.15f) {

		++_currentFrame;
		if (_currentFrame == _frames.size()) {
			_currentFrame = 0;
		}

		sf::IntRect const& r = _frames.at(_currentFrame);
		_shape->setSize(sf::Vector2f(r.width * COEF_RESIZE, r.height * COEF_RESIZE));
		setOrigin((r.width * COEF_RESIZE) / 2.f, (r.height * COEF_RESIZE) / 2.f);
		getShape()->setTextureRect(sf::IntRect(r.left, r.top, r.width, r.height));
		_delta = 0.f;
	}
}

void Dop::collisionDestruction(void)
{
	setCollisioned(true);
	setCollisionType(COLLISION_NONE);

	Explosion *explosion = World::spawnEntity<Explosion>();
	explosion->setPosition(getPosition());
	explosion->setReadyForInit(true);

	if (getHealth() == 1) {
		recycle();
	}
	else {
		setHealth(getHealth() - 1);
		setCollisioned(false);
		setCollisionType(COLLISION_FATAL);
		_invincibleDelay = 2;
	}
}

void Dop::refreshInvincibility(float delta)
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