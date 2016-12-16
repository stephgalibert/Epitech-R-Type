#pragma once

#include <string>
#include <vector>

class ADirectoryParser
{
public:
	ADirectoryParser(std::string const& path);
	virtual ~ADirectoryParser(void);

	virtual void parse(void) = 0;

	bool extension(std::string const& filename, std::string const& ext);

	std::string const& getDirPath(void) const;
	std::vector<std::string> const& getFiles(void) const;

protected:
	void addFile(std::string const& filename);

private:
	std::vector<std::string> _files;
	std::string _path;
};