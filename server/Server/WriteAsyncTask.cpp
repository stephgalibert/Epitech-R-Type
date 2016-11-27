#include "WriteAsyncTask.hpp"

WriteAsyncTask::WriteAsyncTask(std::shared_ptr<ISocket> socket, Buffer &buffer,
							   std::function<void(void)> callback)
	: _socket(socket),
	  _buffer(buffer),
	  _callback(callback),
	  _canceled(false)
{
}

WriteAsyncTask::~WriteAsyncTask(void)
{
}

void WriteAsyncTask::doInBackground(void)
{
	_socket->send(_buffer.getData(), _buffer.getSize());
	_callback();
}

void WriteAsyncTask::cancel(void)
{
	_canceled = true;
}