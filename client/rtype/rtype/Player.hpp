#pragma once

#include <string>

#include "APC.hpp"
#include "LevelResource.hpp"

class IClient;

class Player : public APC
{
public:
	Player();
	virtual ~Player(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);
	virtual void input(InputHandler &input);

	void setIClient(IClient *client);

private:
	void keyboard(InputHandler &input);
	void joystick(InputHandler &input);

	float _delta;
	IClient *_client;
};

