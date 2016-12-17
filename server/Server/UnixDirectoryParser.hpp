#pragma once

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>

#include "ADirectoryParser.hpp"

class UnixDirectoryParser : public ADirectoryParser
{
public:
	UnixDirectoryParser(std::string const& path);
	virtual ~UnixDirectoryParser(void);

	virtual void parse(void);
};
