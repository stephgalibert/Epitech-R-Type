#pragma once

#include <string>
#include <stdexcept>
#include <string>

#include <Windows.h>

#include "ADlLoader.hpp"

template <typename T>
class WinDlLoader : public ADlLoader<T>
{
public:
	WinDlLoader(void);
	virtual ~WinDlLoader(void);

	virtual void load(std::string const& dlpath, std::string const& dlname);
	virtual T *getInstance(void) const;
	virtual std::string getType(void) const;

private:
	HMODULE _dll;
};

/*** Implementation ***/

template <typename T>
WinDlLoader<T>::WinDlLoader(void)
{
	_dll = NULL;
}

template <typename T>
WinDlLoader<T>::~WinDlLoader(void)
{
	if (_dll) {
		FreeLibrary(_dll);
	}
}

template <typename T>
void WinDlLoader<T>::load(std::string const& dlpath, std::string const& dlname)
{
	std::string path = dlpath + dlname;
	std::cout << "loading '" << path << "'" << std::endl;
	_dll = LoadLibrary(path.c_str());
	if (!_dll) {
		throw (std::runtime_error("can not load " + dlname));
	}
	_dlname = dlname;
}

template<typename T>
T *WinDlLoader<T>::getInstance(void) const
{
	if (_entryName.empty()) {
		throw (std::runtime_error("Entry name not defined"));
	} else if (_dll) {
		FARPROC addr = GetProcAddress(_dll, _entryName.c_str());
		if (!addr) {
			throw (std::runtime_error("entry name function not defined in " + _dlname));
		}
		return (((T *(*)(void))(addr))());
	}
	throw (std::runtime_error("no .dll loaded"));
}

template<typename T>
std::string WinDlLoader<T>::getType(void) const
{
	if (_entryType.empty()) {
		throw (std::runtime_error("Entry type not defined"));
	}
	else if (_dll) {
		FARPROC addr = GetProcAddress(_dll, _entryType.c_str());
		if (!addr) {
			throw (std::runtime_error("entry type function not defined in " + _dlname));
		}
		return (((const char *(*)(void))(addr))());
	}
	throw (std::runtime_error("no .dll loaded"));
}
