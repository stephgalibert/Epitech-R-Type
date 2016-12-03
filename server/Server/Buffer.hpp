#pragma once

#include <iostream>
#include <string>
#include <string.h>
#include <mutex>

class Buffer
{
public:
	Buffer(void);
	virtual ~Buffer(void);

	void prepare(size_t len);
	void addData(char *data, size_t len);
	void consume(size_t len);
	void reallocate(char *data, size_t size);

	void setSize(size_t value);

	char *getData(void) const;
	size_t getSize(void) const;

private:
	char *_data;
	size_t _size;
	std::mutex _mutex;
};

