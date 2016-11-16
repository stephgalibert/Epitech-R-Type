#pragma once

#include <istream>
#include <string>

#include <boost/noncopyable.hpp>

struct IReader : private boost::noncopyable
{
	virtual ~IReader(void) {}
	virtual void readFromString(std::string const& data) = 0;
	virtual void readFromFile(std::string const& filename) = 0;
	virtual void readFromStream(std::istream &is) = 0;
};
