#include "UnixDirectoryParser.hpp"

UnixDirectoryParser::UnixDirectoryParser(std::string const& path)
	: ADirectoryParser(path)
{
}

UnixDirectoryParser::~UnixDirectoryParser(void)
{
}


void UnixDirectoryParser::parse(void)
{
  size_t pos;
  DIR *dir;
  struct dirent *ent;

  if ((dir = opendir(this->getDirPath().c_str())) != NULL) {
    while ((ent = readdir(dir)) != NULL)
      if (ent->d_name[0] != '.') { // ?
	std::string path(ent->d_name);
        pos = path.find_last_of(".");
	if (pos != std::string::npos && path.substr(pos) == ".so") {
	  addFile(path);
	}
      }
    closedir(dir);
  }
}
