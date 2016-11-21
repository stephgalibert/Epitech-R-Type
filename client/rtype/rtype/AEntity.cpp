#include "AEntity.hpp"

AEntity::AEntity(ProjectResource &resource)
	: ADrawable(resource),
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