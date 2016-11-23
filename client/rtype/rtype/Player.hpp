#pragma once

#include <string>

#include "APC.hpp"

#include "LevelResource.hpp"
#include "World.hpp"

class Player : public APC
{
public:
	Player();
	virtual ~Player(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);
	virtual void input(InputHandler &input);

private:
	void updateFrame(void);
	void keyboard(InputHandler &input);
	void joystick(InputHandler &input);

	float _delta;
	uint8_t _targetFrame;
	uint8_t _currentFrame;
};

