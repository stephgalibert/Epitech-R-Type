#pragma once

#include "AEntity.hpp"

class AStatic : public AEntity
{
public:
	AStatic(void);
	virtual ~AStatic(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;
};

