#pragma once

#include "ANPC.hpp"

class Mate : public ANPC
{
public:
	Mate(void);
	virtual ~Mate(void);

	virtual void init(void);
	virtual void destroy(void);
};

