#include "WinDirectoryParser.hpp"

WinDirectoryParser::WinDirectoryParser(std::string const& path)
	: ADirectoryParser(path)
{
}

WinDirectoryParser::~WinDirectoryParser(void)
{
}

void WinDirectoryParser::parse(void)
{
	std::string filename;
	size_t pos = 0;
	WIN32_FIND_DATA ffd;
	char dir[MAX_PATH];
	HANDLE find = INVALID_HANDLE_VALUE;

	StringCchCopy(dir, MAX_PATH, getDirPath().c_str());
	StringCchCat(dir, MAX_PATH, TEXT("\\*"));

	find = FindFirstFile(dir, &ffd);
	if (find == INVALID_HANDLE_VALUE) {
		throw (std::runtime_error("can not find " + getDirPath()));
	}

	do {
		if ((ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
			filename = ffd.cFileName;
			pos = filename.find_last_of('.');
			if (pos != std::string::npos && filename.substr(pos) == ".dll") {
				addFile(ffd.cFileName);
			}
		}
	} while (FindNextFile(find, &ffd));

	FindClose(find);
}