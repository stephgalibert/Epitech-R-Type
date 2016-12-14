#pragma once

#include <chrono>

class Timer
{
public:
	Timer(void);
	~Timer(void);
    
	double restart(void);
    
	void toggle(void);
	void start(void);
	void pause(void);
    
	double getElapsedTime(void);

private:
	std::chrono::high_resolution_clock::time_point _begin;
	std::chrono::high_resolution_clock::time_point _current;
	bool _running;
	double _value;
};
