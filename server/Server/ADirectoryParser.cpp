#include "ADirectoryParser.hpp"

ADirectoryParser::ADirectoryParser(std::string const& path)
	: _path(path)
{

}

ADirectoryParser::~ADirectoryParser(void)
{
}

//bool ADirectoryParser::extension(std::string const& filename, std::string const& ext)
//{
//	size_t pos = std::string::npos;
//
//	pos = filename.find_last_of(".");
//	return (pos != std::string::npos && filename.substr(pos + 1) == ext);
//}

std::string const& ADirectoryParser::getDirPath(void) const
{
	return (_path);
}

std::vector<std::string> const& ADirectoryParser::getFiles(void) const
{
	return (_files);
}

void ADirectoryParser::addFile(std::string const& filename)
{
	//_files.push_back(filename);
	StaticTools::Log << "adding plugins " << filename << std::endl;
	_files.emplace_back<std::string>(filename.c_str());
}