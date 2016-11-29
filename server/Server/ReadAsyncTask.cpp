#include "ReadAsyncTask.hpp"

ReadAsyncTask::ReadAsyncTask(std::shared_ptr<ITCPSocket> socket, Buffer &buffer,
	size_t transferAtLeast, std::function<void(bool)> callback)
	: _socket(socket),
	  _buffer(buffer),
	  _transferAtLeast(transferAtLeast),
	  _callback(callback),
	  _canceled(false)
{

}

ReadAsyncTask::~ReadAsyncTask(void)
{

}

void ReadAsyncTask::doInBackground(void)
{
	_callback(_socket->recv(_buffer, _transferAtLeast));
}

void ReadAsyncTask::cancel(void)
{
	_canceled = true;
}