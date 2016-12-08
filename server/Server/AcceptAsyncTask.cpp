#include "AcceptAsyncTask.hpp"

AcceptAsyncTask::AcceptAsyncTask(std::shared_ptr<IServerSocket> ss,
									std::function<void(std::shared_ptr<ITCPSocket>)> callback)
	: _ss(ss),
	  _callback(callback),
	  _canceled(false)
{
}

AcceptAsyncTask::~AcceptAsyncTask(void)
{
}

void AcceptAsyncTask::doInBackground(void)
{
	std::lock_guard<std::mutex> lock(_mutex);

	_callback(_ss->accept());
}

void AcceptAsyncTask::cancel(void)
{
	_canceled = true;
}