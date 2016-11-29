#pragma once

#include <Windows.h>
#include <strsafe.h>

#include "ADirectoryParser.hpp"

class WinDirectoryParser : public ADirectoryParser
{
public:
	WinDirectoryParser(std::string const& path);
	virtual ~WinDirectoryParser(void);

	virtual void parse(void);
};

