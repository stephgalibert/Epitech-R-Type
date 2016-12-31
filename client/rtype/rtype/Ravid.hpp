#pragma once

#include "ANPC.hpp"
#include "FireBall.hpp"
#include "Explosion.hpp"
#include "Generator.hpp"

class Ravid : public ANPC
{
private:
	static const float COEF_RESIZE;

	enum class AnimationState
	{
		Forward = 0,
		Backward = 1
	};

public:
	Ravid(void);
	virtual ~Ravid(void);

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
	size_t _currentFrame;
	sf::RectangleShape *_shape;
	std::vector<sf::IntRect> _frames;
	float _deltaInvincibleAnim;
	bool _invincibleAnimState;
	AnimationState _animState;
	int _nbExplosion;
	Generator _generator;
};

