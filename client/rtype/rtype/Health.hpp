#pragma once

#include "APowerUp.hpp"

class Health : public APowerUp
{
public:
	Health(void);
	virtual ~Health(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual std::string getType(void) const;
	virtual void attachToEntity(AEntity *entity);
	virtual bool fire(IClient *client, uint16_t playerID, sf::Vector2i const& pos,
		uint8_t velocity, float angle, uint8_t level);

	virtual bool canBeCumulated(void) const;
	virtual void upgrade(void);

private:
	float _delta;
	size_t _currentFrame;
	uint16_t _ownerID;
};

