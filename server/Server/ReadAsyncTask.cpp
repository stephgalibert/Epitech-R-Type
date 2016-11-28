#include "ReadAsyncTask.hpp"

ReadAsyncTask::ReadAsyncTask(std::shared_ptr<ITCPSocket> socket, size_t transferAtLeast,
	std::function<void(char *, size_t)> callback)
	: _socket(socket),
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
	Buffer buffer;

	_socket->recv(buffer, _transferAtLeast);
	_callback(buffer.getData(), buffer.getSize());
}

void ReadAsyncTask::cancel(void)
{
	_canceled = true;
}