#pragma once

#include <string>
#include <stdexcept>
#include <dlfcn.h>

#include "ADlLoader.hpp"

template <typename T>
class UnixDlLoader : public ADlLoader<T>
{
public:
	UnixDlLoader(void);
	virtual ~UnixDlLoader(void);

	virtual void load(std::string const& dlname);

	virtual T *getInstance(void) const;
	virtual std::string getType(void) const;

private:
	void *_handle;
};


/*** Implementation ***/

template <typename T>
UnixDlLoader<T>::UnixDlLoader(void)
{
	_handle = NULL;
}

template <typename T>
UnixDlLoader<T>::~UnixDlLoader(void)
{
	if (_handle) {
		dlclose(_handle);
	}
}

template <typename T>
void UnixDlLoader<T>::load(std::string const& dlname)
{
	_handle = dlopen(dlname.c_str(), RTLD_NOW);
	if (!_handle) {
		throw (std::runtime_error("can not load " + dlname));
	}
	this->_dlname = dlname;
}

template<typename T>
T *UnixDlLoader<T>::getInstance(void) const
{
	if (this->_entryName.empty()) {
		throw (std::runtime_error("Entry name not defined"));
	}
	else if (_handle) {
		void *addr = dlsym(_handle, this->_entryName.c_str());
		if (!addr) {
			throw (std::runtime_error("entry name function not defined in " + this->_dlname));
		}
		return (((T *(*)(void))(addr))());
	}
	throw (std::runtime_error("no .so loaded"));
}

template<typename T>
std::string UnixDlLoader<T>::getType(void) const
{
	if (this->_entryType.empty()) {
		throw (std::runtime_error("Entry type not defined"));
	}
	else if (_handle) {
		void *addr = dlsym(_handle, this->_entryType.c_str());
		if (!addr) {
			throw (std::runtime_error("entry type function not defined in " + this->_dlname));
		}
		return (((const char *(*)(void))(addr))());
	}
	throw (std::runtime_error("no .so loaded"));
}
