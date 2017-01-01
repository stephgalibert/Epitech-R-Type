#include "Generator.hpp"

Generator::Generator(void)
{
	_generator = new std::default_random_engine(_rd());
}

Generator::~Generator(void)
{
	if (_generator) {
		delete (_generator);
	}
}

int Generator::operator()(unsigned int min, unsigned int max)
{
	std::uniform_int_distribution<unsigned int> distrib(min, max);
	return (distrib(*_generator));
}
