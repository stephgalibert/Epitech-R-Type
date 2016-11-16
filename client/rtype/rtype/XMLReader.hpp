#pragma once

#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "IReader.hpp"

class XMLReader :  public IReader
{
public:
	XMLReader(void);
	virtual ~XMLReader(void);

	virtual void readFromString(std::string const& json);
	virtual void readFromFile(std::string const& filename);
	virtual void readFromStream(std::istream &is);

	template <typename T>
	T getValue(std::string const& rootName, std::string const& nodeName) const
	{
		return (_root.get<T>(rootName + "." + nodeName));
	}

private:
  boost::property_tree::ptree _root;
};
