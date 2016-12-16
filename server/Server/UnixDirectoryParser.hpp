#pragma once

#include "ADirectoryParser.hpp"

class UnixDirectoryParser : public ADirectoryParser
{
public:
	UnixDirectoryParser(std::string const& path);
	virtual ~UnixDirectoryParser(void);

	virtual void parse(void);
};

