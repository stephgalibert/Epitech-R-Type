#pragma once

#include "APC.hpp"

class Player : public APC
{
public:
	Player();
	virtual ~Player(void);

	virtual void input(InputHandler &input);

private:

};

