#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>

#include <boost/noncopyable.hpp>

struct MemoryFile : private boost::noncopyable
{
	MemoryFile(void);
	MemoryFile(std::string const& filename);
	~MemoryFile(void);

	void load(void);

	char *data;
	std::size_t size;
	std::string filename;
};
