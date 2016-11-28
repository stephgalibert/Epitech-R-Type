#pragma once

#include <string>
#include <string.h>

class Buffer
{
public:
	Buffer(void);
	virtual ~Buffer(void);

	void prepare(size_t len);
	void reallocate(char *data, size_t size);

	void setSize(size_t value);

	char *getData(void) const;
	size_t getSize(void) const;

private:
	char *_data;
	size_t _size;
};

