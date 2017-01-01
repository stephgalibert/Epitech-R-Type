#include "Health.hpp"

Health::Health(void)
{
	_delta = 0;
	_currentFrame = 0;
	_ownerID = 0;
}

Health::~Health(void)
{
}

void Health::init(void)
{
	sf::RectangleShape *shape = new sf::RectangleShape;
	shape->setSize(sf::Vector2f(29, 24));

	try {sf::Texture *texture = ProjectResource::TheProjectResource.getTextureByKey("health");
		texture->setSmooth(true);

		setShape(shape);
		setTexture(texture);
	}
	catch (std::exception const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void Health::update(float delta)
{
	(void)delta;
}

void Health::destroy(IClient &client)
{
	if (_ownerID > 0) {
		client.write(std::make_shared<CMDEffect>(EffectType::AddLife, _ownerID, true));
	}
}

std::string Health::getType(void) const
{
	return ("health");
}

void Health::attachToEntity(AEntity *entity)
{
	if (entity->getHealth() > 0 && entity->getHealth() < 3) {
		entity->setHealth(entity->getHealth() + 1);
		_ownerID = entity->getID();
		recycle();
	}
	else {
		setCollisionType(COLLISION_PUP);
		setCollisioned(false);
	}
}

bool Health::fire(IClient *client, uint16_t playerID, sf::Vector2i const& pos, uint8_t velocity, float angle, uint8_t level)
{
  (void)client;
  (void)playerID;
  (void)pos;
  (void)velocity;
  (void)angle;
  (void)level;
	return (false);
}

bool Health::canBeCumulated(void) const
{
	return (true);
}

void Health::upgrade(void)
{
}
