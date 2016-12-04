#pragma once

#include "ANPC.hpp"

class Mate : public ANPC
{
private:
	static const uint8_t FRAME_TOP = 0;
	static const uint8_t FRAME_MID = 1;
	static const uint8_t FRAME_BOT = 2;

public:
	Mate(void);
	virtual ~Mate(void);

	virtual void init(void);
	virtual void update(float delta);
	virtual void destroy(void);

	void updateFrame(void);

private:
	void initFrame(void);

	uint8_t _prevDirection;
	float _delta;
	bool _decrease;
	uint8_t _targetFrame;
	uint8_t _currentFrame;

	std::unordered_map<uint8_t, sf::IntRect> _frames;
	uint8_t _currentDirection;
};

