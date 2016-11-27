#pragma once

#include <string>

class Buffer
{
public:
	Buffer(void);
	Buffer(char *data, size_t size);
	virtual ~Buffer(void);

	void reallocate(char *data, size_t size);

	char *getData(void) const;
	size_t getSize(void) const;

private:
	char *_data;
	size_t _size;
	bool _allocated;
};

