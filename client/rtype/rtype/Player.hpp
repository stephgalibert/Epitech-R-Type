#pragma once

#include <string>

#include "APC.hpp"
#include "LevelResource.hpp"

class IClient;

class Player : public APC
{
private:
	static const uint8_t FRAME_TOP = 0;
	static const uint8_t FRAME_MID = 1;
	static const uint8_t FRAME_BOT = 2;

public:
	Player();
	virtual ~Player(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);
	virtual void input(InputHandler &input);

	void setIClient(IClient *client);

private:
	void initFrame(void);
	void updateFrame(void);

	void keyboard(InputHandler &input);
	void joystick(InputHandler &input);

	float _delta;
	IClient *_client;
	bool _decrease;
	uint8_t _targetFrame;
	uint8_t _currentFrame;

	std::unordered_map<uint8_t, sf::IntRect> _frames;
	uint8_t _currentDirection;
};

