#pragma once

#include "ANPC.hpp"
#include "RedMissile.hpp"
#include "Explosion.hpp"

class Dop : public ANPC
{
public:
	static const float COEF_RESIZE;

public:
	Dop(void);
	virtual ~Dop(void);

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

private:
	float _delta;
	uint8_t _currentFrame;
	sf::RectangleShape *_shape;
	std::vector<sf::IntRect> _frames;
	float _deltaInvincibleAnim;
	bool _invincibleAnimState;
};

