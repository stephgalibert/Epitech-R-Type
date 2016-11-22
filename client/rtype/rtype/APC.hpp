#pragma once

#include "AShip.hpp"

#include "InputHandler.hpp"

class APC : public AShip
{
public:
	APC();
	virtual ~APC(void);

	virtual void input(InputHandler &input) = 0;
};