#pragma once

#include "ADrawable.hpp"

class ALayer : public ADrawable
{
public:
	ALayer(ProjectResource &resource);
	virtual ~ALayer(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;
};

