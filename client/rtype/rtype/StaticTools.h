#pragma once

#include <iostream>
#include <string>
#include <fstream>

class StaticTools
{
public:
	StaticTools(void);
	~StaticTools(void);

	static std::ofstream Log;
};

