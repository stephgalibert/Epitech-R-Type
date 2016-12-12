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

void Buffer::prepare(size_t len)
{
	if (_data) {
		delete (_data);
	}
	_data = new char[len];
	memset(_data, 0, len);
	_size = len;
}

void Buffer::addData(char *data, size_t len)
{
	memcpy(_data, data, len);
	_size = len;
}

void Buffer::consume(size_t len)
{
	if (len > _size) {
		return;
	}
	if (_size - len == 0) {
		delete (_data);
		_data = NULL;
		_size = 0;
		return;
	}

	_size = _size - len;
	char *tmp = new char[_size];
	memset(tmp, 0, _size);
	memcpy(tmp, &_data[len], _size);
	delete (_data);
	_data = tmp;
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

void Buffer::setSize(size_t value)
{
	_size = value;
}

char *Buffer::getData(void) const
{
	return (_data);
}

size_t Buffer::getSize(void) const
{
	return (_size);
}
