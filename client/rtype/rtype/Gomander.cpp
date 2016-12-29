#include "Gomander.hpp"
#include "World.hpp"
#include "Explosion.hpp"

const float Gomander::COEF_RESIZE = 2.f;

Gomander::Gomander(void)
{
	_delta = 0;
	_deltaExplosing = 0;
	_currentFrame = 0;
	_deltaInvincibleAnim = 0.f;
	_invincibleAnimState = false;
	initFrame();
	_nbExplosion = 0;
}

Gomander::~Gomander(void)
{
}

void Gomander::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(258 * COEF_RESIZE, 142 * COEF_RESIZE));
	setOrigin((258 * COEF_RESIZE) / 2.f, (142 * COEF_RESIZE) / 2.f);

	try {
		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("gomander");
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

void Gomander::update(float delta)
{
	_delta += delta;

	if (isExploding()) {
		refreshExplosion(delta);
	}
	else {
		if (getPosition().x < 200) {
			setAngle(0);
		}
		else if (getPosition().x > StaticTools::GetResolution().first - 200) {
			setAngle(180);
		}

		updateFrame();
		refreshInvincibility(delta);
		ANPC::update(delta);
	}
}

void Gomander::destroy(IClient &client)
{
	client.write(std::make_shared<CMDDestroyed>(getID()));
}

void Gomander::collision(IClient *client, AEntity *other)
{
	(void)client;
	if (!isInvincible() && !hasCollisioned() && !other->isInvincible() && other->getID() > 0
		&& other->getID() < 29999) {

		if (getCollisionType() != COLLISION_NONE
			&& (other->getCollisionType() == COLLISION_FATAL || other->getCollisionType() == COLLISION_MISSILE)) {

			setCollisioned(true);
			other->collision(client, this);
			setCollisionType(COLLISION_NONE);
		}
	}
}

void Gomander::applyCollision(CollisionType type, AEntity *other)
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

void Gomander::move(float delta)
{
	if (getAngle() != -1 && !isExploding()) {
		float x = std::cos(getRadians()) * getVelocity() * delta;
		float y = std::sin(getRadians()) * getVelocity() * delta;

		ADrawable::move(x, y);
	}
}

void Gomander::shoot(Fire const& param)
{
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

void Gomander::respawn(void)
{
}

sf::IntRect const& Gomander::getFrame(size_t idx) const
{
	return (_frames.at(idx));
}

void Gomander::setPowder(PowderType powderType)
{
	(void)powderType;
}

void Gomander::initFrame(void)
{
	_frames.emplace_back(261, 1, 258, 142);
	_frames.emplace_back(1, 1, 258, 142);
	_frames.emplace_back(261, 144, 258, 142);
	_frames.emplace_back(1, 144, 258, 142);
	_frames.emplace_back(261, 287, 258, 142);
	_frames.emplace_back(1, 287, 258, 142);
	_frames.emplace_back(261, 430, 258, 142);
	_frames.emplace_back(1, 430, 258, 142);
}

void Gomander::updateFrame(void)
{
	if (_delta > 0.5f) {

		++_currentFrame;
		if (_currentFrame == _frames.size()) {
			_currentFrame = 0;
		}

		sf::IntRect const& r = _frames.at(_currentFrame);
		getShape()->setTextureRect(sf::IntRect(r.left, r.top, r.width, r.height));
		_delta = 0.f;
	}
}

void Gomander::collisionDestruction(void)
{
	setCollisioned(true);
	setCollisionType(COLLISION_NONE);

	if (getHealth() == 1) {
		setExplode(true);

		//Explosion *explosion = World::spawnEntity<Explosion>();
		//explosion->setPosition(getPosition());
		//explosion->setReadyForInit(true);

		//recycle();
	}
	else {
		setHealth(getHealth() - 1);
		setCollisioned(false);
		setCollisionType(COLLISION_FATAL);
		_invincibleDelay = 2.f;
	}
}

void Gomander::refreshInvincibility(float delta)
{
	sf::Color const& color = getShape()->getFillColor();

	if (isInvincible()) {
		_invincibleDelay -= delta;
		_deltaInvincibleAnim += delta;
		if (_deltaInvincibleAnim > 0.08f) {
			if (_invincibleAnimState) {
				getShape()->setFillColor(sf::Color(color.r, color.g, color.b, 255));
				_invincibleAnimState = false;
			}
			else {
				getShape()->setFillColor(sf::Color(color.r, color.g, color.b, 0));
				_invincibleAnimState = true;
			}
			_deltaInvincibleAnim = 0.f;
		}
	}
	else {
		getShape()->setFillColor(sf::Color(color.r, color.g, color.b, 255));
	}
}

void Gomander::refreshExplosion(float delta)
{
	_deltaExplosing += delta;
	if (_deltaExplosing > 0.3f) {

		sf::Color const& color = getShape()->getFillColor();
		getShape()->setFillColor(sf::Color(color.r, color.g, color.b, 255));

		++_nbExplosion;
		if (_nbExplosion < 18) {
			sf::Vector2f const& pos = getPosition();

			uint16_t x = _generator(0, 300);
			uint16_t y = _generator(0, 300);
			float size = static_cast<float>(_generator(40, 140));

			Explosion *explosion = World::spawnEntity<Explosion>();
			explosion->setPosition(pos.x - 150 + x, pos.y - 150 + y);
			explosion->setSize(size, size);
			explosion->setReadyForInit(true);
		}
		else if (_nbExplosion == 18) {
			Explosion *explosion = World::spawnEntity<Explosion>();
			explosion->setPosition(getPosition());
			explosion->setSize(450.f, 450.f);
			explosion->setReadyForInit(true);
		}
		else {
			recycle();
		}
		_deltaExplosing = 0;
	}
}