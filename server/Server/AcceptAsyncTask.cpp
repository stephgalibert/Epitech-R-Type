#include "AcceptAsyncTask.hpp"

AcceptAsyncTask::AcceptAsyncTask(std::shared_ptr<IServerSocket> ss, std::function<void(std::shared_ptr<ISocket>)> function)
	: _ss(ss),
	  _callback(function),
	  _canceled(false)
{
}

AcceptAsyncTask::~AcceptAsyncTask(void)
{
}

void AcceptAsyncTask::doInBackground(void)
{
	_callback(_ss->accept());
}

void AcceptAsyncTask::cancel(void)
{
	_canceled = true;
}