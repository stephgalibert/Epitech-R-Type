#pragma once

#include "ANPC.hpp"
#include "FireBall.hpp"
#include "Generator.hpp"

class Gomander : public ANPC
{
public:
	static const float COEF_RESIZE;

public:
	Gomander(void);
	virtual ~Gomander(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(IClient &client);

	virtual void collision(IClient *client, AEntity *other);
	virtual void applyCollision(CollisionType type, AEntity *other);
	virtual void move(float delta);

	virtual void shoot(Fire const& param);
	virtual void setPowder(PowderType powderType);

	virtual void respawn(void);

	sf::IntRect const& getFrame(size_t idx) const;

private:
	void initFrame(void);
	void updateFrame(void);

	void collisionDestruction(void);

	void refreshInvincibility(float delta);
	void refreshExplosion(float delta);

private:
	float _delta;
	float _deltaExplosing;
	uint8_t _currentFrame;
	sf::RectangleShape *_shape;
	std::vector<sf::IntRect> _frames;
	float _deltaInvincibleAnim;
	bool _invincibleAnimState;
	int _nbExplosion;
	Generator _generator;
};

