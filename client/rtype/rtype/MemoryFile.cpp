#include "MemoryFile.hpp"

MemoryFile::MemoryFile(void)
{
  data = NULL;
  size = 0;
  filename = "";
}

MemoryFile::MemoryFile(std::string const& filename)
{
  this->filename = filename;
  data = NULL;
  size = 0;
}

MemoryFile::~MemoryFile(void)
{
	if (data != NULL) {
		delete[] (data);
	}
}

void MemoryFile::load(void)
{
	std::ifstream ifs(filename, std::ios::binary);

	if (ifs) {
		ifs.seekg(0, ifs.end);
		size = static_cast<int>(ifs.tellg());
		ifs.seekg(0, ifs.beg);
		data = new char[size];
		ifs.read(data, size);
		ifs.close();
	}
	else {
		throw (std::runtime_error("Error: unable to open " + filename));
	}
}
