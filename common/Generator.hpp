#pragma once

#include <random>

class Generator
{
public:
	Generator(void);
	~Generator(void);
	int operator()(unsigned int min, unsigned int max);

private:
	std::default_random_engine *_generator;
	std::random_device _rd;
};
