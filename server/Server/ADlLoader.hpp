#pragma once

#include <string>

template <typename T>
class ADlLoader
{
public:
	ADlLoader(std::string const& entryName = "entry", std::string const& entryType = "type");
	virtual ~ADlLoader(void);

	virtual void load(std::string const& dlpath, std::string const& dlname) = 0;
	virtual T *getInstance(void) const = 0;
	virtual std::string getType(void) const = 0;

protected:
	std::string _dlname;
	std::string _entryName;
	std::string _entryType;
};

template <typename T>
ADlLoader<T>::ADlLoader(std::string const& entryName, std::string const& entryType)
	: _entryName(entryName),
	  _entryType(entryType)
{
}

template <typename T>
ADlLoader<T>::~ADlLoader(void)
{
}