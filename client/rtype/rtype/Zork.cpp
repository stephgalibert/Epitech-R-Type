#include "Zork.hpp"
#include "Laser.hpp"

const float Zork::COEF_RESIZE = 1.5f;

Zork::Zork(void)
{
	_delta = 0;
	_currentFrame = 4;
}

Zork::~Zork(void)
{
	std::cout << "destroy zork" << std::endl;
}

void Zork::init(void)
{
	_shape = new sf::RectangleShape;
	_shape->setSize(sf::Vector2f(23 * COEF_RESIZE, 26 * COEF_RESIZE));
	setOrigin((23 * COEF_RESIZE) / 2.f, (26 * COEF_RESIZE) / 2.f);

	try {
		initFrame();

		sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("ennemy1");
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

void Zork::update(float delta)
{
	_delta += delta;

	updateFrame();
	ANPC::update(delta);
}

void Zork::destroy(IClient &client)
{
	client.write(std::make_shared<CMDDestroyed>(getID()));
}

void Zork::collision(IClient *client, AEntity *other)
{
	(void)client;
	if (!hasCollisioned() && !other->isInvincible()) {
		if (getCollisionType() != COLLISION_NONE
			&& other->getCollisionType() == COLLISION_FATAL) {

			setCollisioned(true);
			other->collision(client, this);
			setCollisionType(COLLISION_NONE);
		}
	}
}

void Zork::applyCollision(CollisionType type, AEntity *other)
{
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

void Zork::move(float delta)
{
	if (getAngle() != -1) {
		sf::Vector2f const& pos = getPosition();

		float x = std::cos(getRadians()) * getVelocity() * delta;
		float y = std::sin(getRadians()) * getVelocity() * delta;

		ADrawable::move(x, y);
	}
}

void Zork::shoot(Fire const& param)
{
	//ProjectResource::TheProjectResource.getSoundByKey("shot")->play();

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
}

void Zork::respawn(void)
{
}

void Zork::setPowder(PowderType powderType)
{
	(void)powderType;
}

void Zork::initFrame(void)
{
	_frames.emplace_back(4, 5, 23, 26);
	_frames.emplace_back(37, 11, 23, 16);
	_frames.emplace_back(70, 15, 23, 9);
	_frames.emplace_back(103, 9, 23, 16);
	_frames.emplace_back(136, 5, 23, 26);
	_frames.emplace_back(169, 10, 23, 16);
	_frames.emplace_back(202, 12, 23, 9);
	_frames.emplace_back(235, 9, 23, 16);
}

void Zork::updateFrame(void)
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

void Zork::collisionDestruction(void)
{
	setCollisioned(true);
	setCollisionType(COLLISION_NONE);

	Explosion *explosion = World::spawnEntity<Explosion>();
	explosion->setPosition(getPosition());
	explosion->setReadyForInit(true);

	recycle();
}