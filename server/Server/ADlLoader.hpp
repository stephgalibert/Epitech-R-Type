#pragma once

#include <string>

template <typename T>
class ADlLoader
{
public:
	ADlLoader(std::string const& entryName = "entry");
	virtual ~ADlLoader(void);

	virtual void load(std::string const& dlname) = 0;
	virtual T *getInstance(void) const = 0;

protected:
	std::string _dlname;
	std::string _entryName;
};

template <typename T>
ADlLoader<T>::ADlLoader(std::string const& entryName)
	: _entryName(entryName)
{
}

template <typename T>
ADlLoader<T>::~ADlLoader(void)
{
}