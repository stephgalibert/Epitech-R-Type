#include "XMLReader.hpp"

XMLReader::XMLReader(void)
{
}

XMLReader::~XMLReader(void)
{
}

void XMLReader::readFromString(std::string const& xml)
{
	try {
		std::istringstream is(xml);
		boost::property_tree::read_xml(is, _root);
	} catch (std::exception const& e) {
		throw (e);
	}
}

void XMLReader::readFromFile(std::string const& filename)
{
	try {
		std::ifstream ifs(filename, std::ios::in);
		if (ifs) {
			boost::property_tree::read_xml(ifs, _root);
		}
	} catch (std::exception const& e) {
		throw (e);
	}
}

void XMLReader::readFromStream(std::istream &is)
{
	try {
		boost::property_tree::read_xml(is, _root);
	} catch (std::exception const& e) {
		throw (e);
	}
}
