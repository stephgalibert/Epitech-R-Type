#include "AActor.hpp"

AActor::AActor()
{
}

AActor::~AActor()
{
}

void AActor::setID(uint8_t id)
{
	_id = id;
}

uint8_t AActor::getID(void) const
{
	return (_id);
}