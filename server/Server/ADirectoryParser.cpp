#include "ADirectoryParser.hpp"

ADirectoryParser::ADirectoryParser(std::string const& path)
	: _path(path)
{

}

ADirectoryParser::~ADirectoryParser(void)
{
}

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
	bool found = false;

	for (auto &it : _files) {
		if (it == filename) {
			found = true;
		}
	}

	if (!found) {
		StaticTools::Log << "adding plugins " << filename << std::endl;
		_files.emplace_back<std::string>(filename.c_str());
	}
}