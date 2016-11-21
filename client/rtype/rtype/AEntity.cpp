#include "AEntity.hpp"

AEntity::AEntity(World &world, ProjectResource &resource)
	: ADrawable(resource),
	  _world(world),
	  _waitingForRecycle(false)
{
}

AEntity::~AEntity(void)
{
}

void AEntity::recycle(void)
{
	_waitingForRecycle = true;
}

bool AEntity::isWaitingForRecycle(void) const
{
	return (_waitingForRecycle);
}