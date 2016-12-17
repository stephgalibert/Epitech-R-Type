#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#ifdef _WIN32
# include "WinDlLoader.hpp"
# include "WinDirectoryParser.hpp"
#else
# include "UnixDlLoader.hpp"
# include "UnixDirectoryParser.hpp"
#endif

template <typename T>
class DLManager {
public:
	DLManager(void);
	~DLManager(void);

	void addLibrary(std::string const& path);
	void parseDirectory(std::string const& dirpath);

	std::vector<T *> const& retrieveObject(void);
	void deleteObjects(void);

private:
	std::vector<ADlLoader<T> *> _dls;
	std::vector<T *> _instances;
};


/*** Implementation ***/

template <typename T>
DLManager<T>::DLManager(void)
{
}

template <typename T>
DLManager<T>::~DLManager(void)
{
	for (auto it : _dls) {
		delete (it);
	}
}

template <typename T>
void DLManager<T>::addLibrary(std::string const& path)
{
#ifdef WIN32
	ADlLoader<T> *loader = new WinDlLoader<T>;
#else
	ADlLoader<T> *loader = new UnixDlLoader<T>;
#endif
	try {
		loader->load(path);
	} catch (std::exception const& e) {
		if (loader) {
			delete (loader);
		}
		throw (e);
	}
	_dls.push_back(loader);
}

template <typename T>
void DLManager<T>::parseDirectory(std::string const& dirpath)
{
#ifdef WIN32
	ADirectoryParser *parser = new WinDirectoryParser(dirpath);
#else
	ADirectoryParser *parser = new UnixDirectoryParser(dirpath);
#endif

	try {
		parser->parse();
		for (auto &it : parser->getFiles()) {
			addLibrary(it);
		}
	} catch (std::exception const& e) {
		throw (e);
	}
	delete (parser);
}

template <typename T>
std::vector<T *> const& DLManager<T>::retrieveObject(void)
{
	for (auto &it : _dls) {
		_instances.push_back(it->getInstance());
	}
	return (_instances);
}

template <typename T>
void DLManager<T>::deleteObjects(void)
{
	for (auto &it : _instances) {
		delete (it);
	}
	_instances.clear();
}
