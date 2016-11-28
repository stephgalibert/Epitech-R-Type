#include "WriteAsyncTask.hpp"

WriteAsyncTask::WriteAsyncTask(std::shared_ptr<ITCPSocket> socket, char *buffer, size_t size,
							   std::function<void(void)> callback)
	: _socket(socket),
	  _buffer(buffer),
	  _size(size),
	  _callback(callback),
	  _canceled(false)
{
}

WriteAsyncTask::~WriteAsyncTask(void)
{
}

void WriteAsyncTask::doInBackground(void)
{
	_socket->send(_buffer, _size);
	_callback();
}

void WriteAsyncTask::cancel(void)
{
	_canceled = true;
}