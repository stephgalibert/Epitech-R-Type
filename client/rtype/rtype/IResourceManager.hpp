#pragma once

struct IResourceManager
{
	virtual ~IResourceManager(void) {}
	virtual void load(void) = 0;
};