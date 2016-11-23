#pragma once

#include <string>

#include "APC.hpp"
#include "LevelResource.hpp"

class Player : public APC
{
public:
	Player();
	virtual ~Player(void);

	virtual void init(void);
	virtual void destroy(void);
	virtual void input(InputHandler &input);

private:
	void keyboard(InputHandler &input);
	void joystick(InputHandler &input);

	float _delta;
};

