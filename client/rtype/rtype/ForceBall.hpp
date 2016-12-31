#pragma once

#include "AStatic.hpp"

class ForceBall : public AStatic
{
private:
	static const float COEF_RESIZE;

public:
	ForceBall(void);
	virtual ~ForceBall(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);

private:
	void initFrame(void);
	void updateFrame(void);

private:
	float _delta;
	size_t _currentFrame;
	std::vector<sf::IntRect> _frames;

	sf::RectangleShape *_shape;
};

