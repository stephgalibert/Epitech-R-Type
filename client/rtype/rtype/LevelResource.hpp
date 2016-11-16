#pragma once

#include "IResourceManager.hpp"

class LevelResource : public IResourceManager
{
public:
	LevelResource(void);
	virtual ~LevelResource(void);

	virtual void load(void);
};

