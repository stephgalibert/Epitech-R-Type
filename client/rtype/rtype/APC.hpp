#pragma once

#include "AShip.hpp"

#include "InputHandler.hpp"

class APC : public AShip
{
public:
	APC();
	virtual ~APC(void);

	virtual void init(void) = 0;
	//virtual void update(float delta) = 0;
	virtual void destroy(void) = 0;

	virtual void input(InputHandler &input) = 0;
};