#pragma once

#include "AMoveable.hpp"
#include "IClient.hpp"

class APowerUp : public AMoveable
{
public:
	APowerUp(void);
	virtual ~APowerUp(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(IClient &client) = 0;

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);

	virtual void attachToEntity(AEntity *entity) = 0;

	virtual bool fire(IClient *client, uint16_t playerID, sf::Vector2i const& pos, uint8_t velocity, uint8_t angle, uint8_t level) = 0;

private:
	PowerUPsType _type;
};

