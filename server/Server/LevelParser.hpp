#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <stdint.h>
#include <vector>

#include "StaticTools.hpp"

class LevelParser
{
public:
	LevelParser(void);
	~LevelParser(void);

	void parse(uint8_t level);
	std::vector<std::vector<std::string> > const& getData(void) const;

private:
	void retrieveData(std::ifstream &ifs);

private:
	std::vector<std::vector<std::string> > _data;
};

