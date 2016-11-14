#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>

struct MemoryFile
{
	MemoryFile(void);
	MemoryFile(std::string const& filename);
	~MemoryFile(void);

	void load(void);

	char *data;
	std::size_t size;
	std::string filename;
};
