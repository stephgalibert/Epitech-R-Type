#pragma once

#include "APowerUp.hpp"

class IncreaseNumberOfCanon : public APowerUp
{
public:
	IncreaseNumberOfCanon(void);
	virtual ~IncreaseNumberOfCanon(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual void attachToEntity(AEntity *entity);

	virtual bool fire(IClient *client, uint16_t playerID, sf::Vector2i const& pos, uint8_t velocity, uint8_t angle, uint8_t level);

private:
	void initFrame(void);

	void updateFrame();

private:
	float _delta;
	size_t _currentFrame;
	std::vector<sf::IntRect> _frames;
};

