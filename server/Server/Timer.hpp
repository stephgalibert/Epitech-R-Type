#pragma once

#include <chrono>

class Timer
{
public:
	Timer(void);
	~Timer(void);
    
	float restart(void);
    
	void toggle(void);
	void start(void);
	void pause(void);
    
	float getElapsedTime(void);

private:
	std::chrono::steady_clock::time_point _begin;
	std::chrono::steady_clock::time_point _current;
	bool _running;
	float _value;
};
