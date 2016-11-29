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

	std::vector<T *> const& retrieveObject(std::string const& type);
	void deleteObject(std::string const& type);
private:
	std::vector<ADlLoader<T> *> _dls;
	std::unordered_map<std::string, std::vector<T *> > _instances;
};


/*** Implementation ***/

template <typename T>
DLManager<T>::DLManager(void) {}

template <typename T>
DLManager<T>::~DLManager(void) {
	for (auto it : _dls) {
		delete (it);
	}
}

template <typename T>
void DLManager<T>::addLibrary(std::string const& path) {
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
void DLManager<T>::parseDirectory(std::string const& dirpath) {
#ifdef WIN32
	ADirectoryParser *parser = new WinDirectoryParser(dirpath);
#else
	ADirectoryParser *parser = new UnixDirectoryParser(dirpath);
#endif

	try {
		parser->parse();
		try {
			for (auto &it : parser->getFiles()) {
#ifdef WIN32
				if (parser->extension(it, "dll")) {
#else
				if (parser->extension(it, ".so")) {
#endif
					addLibrary(it);
				}
				}
			} catch (std::exception const& e) {
				throw (e);
			}
		} catch (std::exception const& e) {
			throw (e);
		}

		delete (parser);
	}

template <typename T>
std::vector<T *> const& DLManager<T>::retrieveObject(std::string const& type) {
	if (_instances.find(type) == _instances.cend()) {
		for (auto &it : _dls) {
			if (it->getType() == type) {
				T *object = it->getInstance();
				_instances[type].push_back(object);
			}
		}
	}
	if (_instances.find(type) != _instances.cend()) {
		return (_instances.at(type));
	}
	throw (std::runtime_error("an error has occured while retrieving an object"));
}

template <typename T>
void DLManager<T>::deleteObject(std::string const& type) {
	if (_instances.find(type) == _instances.cend()) {
		throw (std::runtime_error("can not find the dl " + type));
	}
	for (auto &it : _instances[type]) {
		delete (it);
	}
	_instances.erase(type);
}