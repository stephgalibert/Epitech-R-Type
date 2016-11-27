#include "ReadAsyncTask.hpp"

ReadAsyncTask::ReadAsyncTask(std::shared_ptr<ISocket> socket, std::function<void(char *, size_t)> callback)
	: _socket(socket),
	  _callback(callback),
	  _canceled(false)
{

}

ReadAsyncTask::~ReadAsyncTask(void)
{

}

void ReadAsyncTask::doInBackground(void)
{

}

void ReadAsyncTask::cancel(void)
{
	_canceled = true;
}