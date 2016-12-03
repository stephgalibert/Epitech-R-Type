#pragma once

#include "ADrawable.hpp"

class AEntity : public ADrawable
{
public:
	AEntity(void);
	virtual ~AEntity(void);

	virtual void init(void) = 0;
	virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	void recycle(void);
	bool isWaitingForRecycle(void) const;
	bool isInitialized(void) const;

	void setID(uint8_t id);
	uint8_t getID(void) const;

protected:
	bool _init;

private:
	bool _waitingForRecycle;
	uint8_t _id;
};