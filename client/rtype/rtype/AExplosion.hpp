#pragma once

#include "AStatic.hpp"

class AExplosion : public AStatic
{
public:
	AExplosion();
	virtual ~AExplosion();

	virtual void init(void) = 0;
	virtual void update(float delta);
	virtual void destroy(IClient &client) = 0;

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);

	virtual void move(float delta);

	void setTextureSize(sf::Vector2i const& size);
	void setMatrixSize(sf::Vector2i const& size);
	void computeCellSize(void);

private:
	sf::Vector2i _textureSize;
	sf::Vector2i _matrixSize;
	sf::Vector2i _cellSize;

	float _delta;
	int _currentFrame;
	int _maxFrame;
};

