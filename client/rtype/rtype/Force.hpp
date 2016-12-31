#pragma once

#include <unordered_map>

#include "APowerUp.hpp"
#include "ForceBall.hpp"

class Force : public APowerUp
{
private:
	enum class Position : uint8_t
	{
		Forward = 0,
		Backward = 1
	};

public:
	Force(void);
	virtual ~Force(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual std::string getType(void) const;
	virtual void attachToEntity(AEntity *entity);
	virtual bool fire(IClient *client, uint16_t playerID, sf::Vector2i const& pos,
					  uint8_t velocity, float angle, uint8_t level);

	virtual bool canBeCumulated(void) const;
	virtual void upgrade(void);

	void inversePosition(void);

private:
	void initFrame(void);
	void updateFrame(void);

private:
	float _delta;
	size_t _level;
	size_t _currentFrame;
	Position _pos;
	std::unordered_map<size_t, std::vector<sf::IntRect> > _frames;

	// ici les différentes AEntity
	ForceBall *_ball;
	uint16_t _ownerID;
};

