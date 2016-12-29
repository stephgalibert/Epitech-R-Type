#pragma once

#include "AExplosion.hpp"

class Explosion : public AExplosion
{
public:
	Explosion(void);
	virtual ~Explosion(void);

	virtual void init(void);
	virtual void destroy(IClient &client);

	void setSize(float w, float h);

private:
	sf::RectangleShape *_shape;
	float _w;
	float _h;
};

