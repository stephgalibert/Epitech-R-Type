#include "Buffer.hpp"

Buffer::Buffer(void)
	: _data(NULL),
	  _size(0)
{
}

Buffer::~Buffer(void)
{
	if (_data != NULL) {
		delete (_data);
	}
}

void Buffer::reallocate(char *data, size_t size)
{
	char *tmp = new char[_size + size];

	if (!_data) {
		memcpy(tmp, data, size);
	}
	else {
		memcpy(tmp, _data, _size);
		memcpy(&tmp[_size], data, size);
		delete (_data);
	}
	_size += size;
	_data = tmp;
}

char *Buffer::getData(void) const
{
	return (_data);
}

size_t Buffer::getSize(void) const
{
	return (_size);
}